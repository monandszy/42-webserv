#include <fcntl.h>
#include <unistd.h>

#include "../parser/parser.hpp"
#include "server.hpp"

int request_handler::process_connect(int epoll_fd, int socket_fd) {
  struct sockaddr_in addr;
  socklen_t len = sizeof(addr);

  int client_fd = accept(socket_fd, (struct sockaddr*)&addr, &len);
  if (client_fd >= 0) {
    int flags = fcntl(client_fd, F_GETFL, 0);
    if (flags != -1) {
      fcntl(client_fd, F_SETFL, flags | O_NONBLOCK);
    }
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = client_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event);
  }
  return client_fd;
}

int process_head(Client& client, Server& server) {
  size_t end_pos = client.getRequestBuffer().find(HTTP_END);
  if (end_pos != std::string::npos) {
    std::string head = client.getRequestBuffer().substr(0, end_pos);
    client.setRequest(parser::parseHead(head));
    client.consumeRequest(end_pos + HTTP_END.size());

    size_t body_size = client.getRequest().getBodySize();
    if (client.getRequest().getMethod() == POST && body_size > 0 &&
        body_size <= server.getBodySize()) {
      client.setStatus(READING_BODY);
    } else {
      client.setStatus(READY_TO_RESPOND);
    }
    return 1;
  }
  return 0;
}

int process_body(Client& client) {
  if (client.getRequestBuffer().size() >= client.getRequest().getBodySize()) {
    HttpRequest req = client.getRequest();
    req.setBody(client.getRequestBuffer().substr(0, req.getBodySize()));
    client.setRequest(req);

    client.consumeRequest(client.getRequest().getBodySize());

    client.setStatus(READY_TO_RESPOND);
    return 1;
  }
  return 0;
}

HandleResult read_chunk(Client& client) {
  char recv_buffer[RECV_SIZE];
  ssize_t bytes = recv(client.getFd(), recv_buffer, sizeof(recv_buffer) - 1, 0);

  if (bytes <= 0) return DROP_CONNECTION;
  client.appendRequestBuffer(recv_buffer, bytes);
  return KEEP_CONNECTION;
}

void schedule_epollout(int epoll_fd, Client& client) {
  struct epoll_event event = {};
  event.events = EPOLLIN | EPOLLOUT;
  event.data.fd = client.getFd();
  epoll_ctl(epoll_fd, EPOLL_CTL_MOD, client.getFd(), &event);
}

void schedule_epollin(int epoll_fd, Client& client) {
  struct epoll_event event = {};
  event.events = EPOLLIN;
  event.data.fd = client.getFd();
  epoll_ctl(epoll_fd, EPOLL_CTL_MOD, client.getFd(), &event);
}

bool is_alive(Client& client) {
  std::string conn = client.getRequest().getHeader(Header::CONNECTION);
  return (conn == HeaderValue::KEEP_ALIVE || conn != HeaderValue::CLOSE);
}

HandleResult request_handler::process_request(int epoll_fd, uint32_t events,
                                              Client& client, Server& server) {
  if (events & EPOLLIN) {
    if (read_chunk(client) == DROP_CONNECTION) {
      return DROP_CONNECTION;
    }
  }

  bool progress;
  do {
    progress = false;
    switch (client.getStatus()) {
      case READING_HEAD: {
        if (process_head(client, server)) progress = true;
        break;
      }
      case READING_BODY: {
        if (process_body(client)) progress = true;
        break;
      }
      case READY_TO_RESPOND: {
        if (events & EPOLLOUT) {
          if (response_serializer::process_response(client, server) ==
              DROP_CONNECTION)
            return DROP_CONNECTION;

          if (client.getResponseBuffer().empty()) {
            if (is_alive(client)) {
              schedule_epollin(epoll_fd, client);
              client.reset();
              progress = true;
            } else {
              return DROP_CONNECTION;
            }
          }
        } else {
          schedule_epollout(epoll_fd, client);
        }
        break;
      }
    }
  } while (progress);

  return KEEP_CONNECTION;
}