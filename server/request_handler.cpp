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

/*
TODO parse Request and based on it create Response
*/
void request_handler::process_request(int client_fd) {
  char buffer[1024] = {0};

  ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
  if (bytes_received == 0) {
    std::cout << "Client disconnected gracefully" << std::endl;
  } else if (bytes_received < 0) {
    std::cout << "Client disconnected" << std::endl;
  } else {
    std::cout << "!!!Received: " << buffer << std::endl;
    const char* response =
        "HTTP/1.1 200 OK\r\nContent-Length: 17\r\n\r\nMessage received\n";
    send(client_fd, response, strlen(response), 0);
  }
}