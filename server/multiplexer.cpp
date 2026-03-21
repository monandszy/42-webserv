#include "server.hpp"

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

int multiplexer::init_epoll(std::map<int, Server>& sockets) {
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
  limit - ammount of events epoll will return at a time, unrelated to the num of
  clients connected
  -1 - sleep indefinitely unitl something happens
*/
void multiplexer::loop_epoll(int epoll_fd, std::map<int, Server>& sockets) {
  const int limit = 64;
  struct epoll_event events[limit];
  std::map<int, Client> clients;
  while (true) {
    int num_ready = epoll_wait(epoll_fd, events, limit, -1);
    for (int i = 0; i < num_ready; i++) {
      int client_fd = events[i].data.fd;
      if (sockets.find(client_fd) != sockets.end()) {
        request_handler::process_connect(epoll_fd, client_fd);
        Client c(client_fd);
        clients.insert(std::make_pair(client_fd, c));
        std::cout << "Client connected" << std::endl;
      } else {
        if (request_handler::process_request(clients[client_fd])) {
          std::cout << "Client disconnected" << std::endl;
          clients.erase(client_fd);
          close(client_fd);
        }
      }
    }
  }
}