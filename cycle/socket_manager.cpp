#include "loop.hpp"

/*
  Create a listening socket

  AF_INET = IPv4
  SOCK_STREAM = TCP

  Set SO_REUSEADDR to 1 (True) Allow Address Reuse
*/
int create_socket() {
  struct protoent* proto = getprotobyname("tcp");
  int protocol_num = proto ? proto->p_proto : 0;

  int socket_fd = socket(AF_INET, SOCK_STREAM, protocol_num);
  if (socket_fd == -1) {
    throw std::runtime_error("Failed to create socket.");
  }

  int o = 1;
  if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &o, sizeof(o)) == -1) {
    throw std::runtime_error("Failed to set socket options.");
  }
  return socket_fd;
}

/*
  Bind the socket to a given IP address and port
*/
void bind_socket(int socket_fd, uint32_t ip_addr, uint16_t host) {
  struct sockaddr_in addr;

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = ip_addr;
  addr.sin_port = host;

  if (bind(socket_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
    throw std::runtime_error("Failed to bind socket.");
  }

  struct sockaddr_in bound_addr;
  socklen_t bound_len = sizeof(bound_addr);
  if (getsockname(socket_fd, (struct sockaddr*)&bound_addr, &bound_len) != 0) {
    throw std::runtime_error("Failed to verify bind socket.");
  }
}

/*
  SOMAXCONN sets the maximum queue length for pending connections
*/
void start_socket(int socket_fd) {
  if (listen(socket_fd, SOMAXCONN) == -1) {
    throw std::runtime_error("Failed to listen on socket.");
  }
}

int init_epoll() {
  int epoll_fd = epoll_create(1);
  if (epoll_fd == -1) {
    throw std::runtime_error("Failed to create epoll file descriptor.");
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