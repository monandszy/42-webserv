#include <fcntl.h>
#include <unistd.h>

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

int process_head(Client& client) {
  size_t end_pos = client.getBuffer().find(HTTP_END);
  if (end_pos != std::string::npos) {
    client.buildRequest(end_pos);
    client.consume(end_pos + HTTP_END.size());

    if (client.getRequest().getMethod() == POST &&
        client.getRequest().getBodySize() > 0) {
      client.setStatus(READING_BODY);
    } else {
      client.setStatus(READY_TO_RESPOND);
    }
    return 1;
  }
  return 0;
}

int process_body(Client& client) {
  if (client.getBuffer().size() >= client.getRequest().getBodySize()) {
    client.buildRequestBody();

    client.consume(client.getRequest().getBodySize());

    client.setStatus(READY_TO_RESPOND);
    return 1;
  }
  return 0;
}

HandleResult read_chunk(Client& client) {
  char tmp_buffer[RECV_SIZE];
  ssize_t bytes = recv(client.getFd(), tmp_buffer, sizeof(tmp_buffer) - 1, 0);

  if (bytes <= 0) return DROP_CONNECTION;
  client.append(tmp_buffer, bytes);
  return KEEP_CONNECTION;
}

HandleResult process_response(Client& client) {
  if (client.getResponseBuffer().empty()) {
    std::cout << "Fully parsed " << client << "\n";
    const char* resp = "HTTP/1.1 200 OK\r\nContent-Length: 2\r\n\r\nOK";
    client.appendResponse(resp);
  }

  const std::string& buf = client.getResponseBuffer();
  ssize_t sent = send(client.getFd(), buf.c_str(), buf.size(), 0);

  if (sent <= 0) {
    return DROP_CONNECTION;
  }

  client.consumeResponse(sent);
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
                                              Client& client) {
  if (events & EPOLLIN) {
    if (read_chunk(client) == DROP_CONNECTION) {
      return DROP_CONNECTION;
    }
  }

  bool progress = true;
  while (progress) {
    progress = false;

    switch (client.getStatus()) {
      case READING_HEADERS: {
        if (process_head(client)) progress = true;
        break;
      }
      case READING_BODY: {
        if (process_body(client)) progress = true;
        break;
      }
      case READY_TO_RESPOND: {
        if (events & EPOLLOUT) {
          if (process_response(client) == DROP_CONNECTION)
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
  }
  return KEEP_CONNECTION;
}