#include "loop.hpp"

int init_epol() {
  int epoll_fd = epoll_create(1);
  if (epoll_fd == -1) {
    throw std::runtime_error("Failed to create epoll file descriptor.");
  }
  return epoll_fd;
}

/*
  monitor INCOMING data (EPOLLIN)
*/
void register_socket(int epoll_fd, int server_fd) {
  struct epoll_event event;
  event.events = EPOLLIN;
  event.data.fd = server_fd;
  if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &event) == -1) {
    throw std::runtime_error("Failed to add server socket to epoll.");
  }
}

int run() {
  int server_fd = create_socket();
  bind_socket(server_fd, INADDR_ANY, htons(8080));
  start_socket(server_fd);

  int epoll_fd = init_epol();
  register_socket(epoll_fd, server_fd);

  std::cout << "Server running" << std::endl;

  close(server_fd);
  close(epoll_fd);
  return 0;
}