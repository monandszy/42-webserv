#include "loop.hpp"

int init_epoll(std::map<int, Server>& sockets) {
  int epoll_fd = epoll_create(1);
  if (epoll_fd == -1) {
    throw std::runtime_error("Failed to create epoll file descriptor.");
  }

  for (std::map<int, Server>::iterator it = sockets.begin();
       it != sockets.end(); ++it) {
    register_socket(epoll_fd, it->first);
  }
  return epoll_fd;
}

/*
  monitor INCOMING data (EPOLLIN)
*/
void register_socket(int epoll_fd, int socket_fd) {
  struct epoll_event event;
  event.events = EPOLLIN;
  event.data.fd = socket_fd;
  if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &event) == -1) {
    throw std::runtime_error("Failed to add socket to epoll.");
  }
}