#include "server.hpp"

void request_handler::process_connect(int epoll_fd, int socket_fd) {
  struct sockaddr_in addr;
  socklen_t len = sizeof(addr);

  int client_fd = accept(socket_fd, (struct sockaddr*)&addr, &len);
  if (client_fd >= 0) {
    std::cout << "New client connected." << std::endl;

    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = client_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event);
  }
}

std::string HTTP_END = "\r\n\r\n";

/*
Read headers until HTTP_END detected
In case of POST do not close, read based on Content-Length
*/
int request_handler::process_request(Client& client) {
  char buffer[10] = {0};
  ssize_t bytes_received = recv(client.getFd(), buffer, sizeof(buffer) - 1, 0);

  if (bytes_received == 0 || bytes_received == -1) {
    return 1;
  } else {
    client.append(buffer, bytes_received);
    if (client.getBuffer().find(HTTP_END) != std::string::npos) {
      std::cout << "!!! Full Request Received:\n"
                << client.getBuffer() << std::endl;
      const char* response =
          "HTTP/1.1 200 OK\r\nContent-Length: 17\r\n\r\nMessage received\n";
      send(client.getFd(), response, strlen(response), 0);
      return 1;
    } else {
      return 0;
    }
  }
}