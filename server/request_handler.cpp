#include "server.hpp"

int request_handler::process_connect(int epoll_fd, int socket_fd) {
  struct sockaddr_in addr;
  socklen_t len = sizeof(addr);

  int client_fd = accept(socket_fd, (struct sockaddr*)&addr, &len);
  if (client_fd >= 0) {
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = client_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event);
  }
  return client_fd;
}

void process_headers(Client& client, size_t end_pos) {
  // TODO Parse Request Line and Headers from client._buffer
  // Set Body size if CONTENT_LENGTH found
  HttpRequest request = client.getRequest();
  request.setBodySize(0);
  request.setMethod(GET);
  client.consume(end_pos + HTTP_END.size());

  if (request.getMethod() == POST) {
    client.setStatus(READING_BODY);
  } else {
    client.setStatus(READY_TO_RESPOND);
  }
}

void process_body(Client& client) {
  HttpRequest request = client.getRequest();
  request.setBody(client.getBuffer().substr(0, request.getBodySize()));

  client.consume(request.getBodySize());

  client.setStatus(READY_TO_RESPOND);
}

/*
Read headers until HTTP_END detected
In case of POST do not close, read based on Content-Length
*/
int request_handler::process_request(Client& client) {
  char tmp_buffer[RECV_SIZE] = {0};
  ssize_t bytes = recv(client.getFd(), tmp_buffer, sizeof(tmp_buffer) - 1, 0);

  if (bytes <= 0) return 1;
  client.append(tmp_buffer, bytes);

  while (1) {
    if (client.getStatus() == READING_HEADERS) {
      size_t end_pos = client.getBuffer().find(HTTP_END);
      if (end_pos != std::string::npos) {
        process_headers(client, end_pos);
      }
    }

    if (client.getStatus() == READING_BODY) {
      if (client.getBuffer().size() >= client.getRequest().getBodySize()) {
        process_body(client);
      }
    }

    if (client.getStatus() == READY_TO_RESPOND) {
      std::cout << "Fully parsed " << client.getRequest().getMethod()
                << " request for " << client.getRequest().getUri() << "\n";

      const char* resp = "HTTP/1.1 200 OK\r\nContent-Length: 2\r\n\r\nOK";
      send(client.getFd(), resp, strlen(resp), 0);

      if (false) {  // TODO keep alive
        client.reset();
        continue;
      }  // there could be another request in the buffer waiting for processing
      return 1;
    }
    return 0;
  }
}