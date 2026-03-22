#include <fcntl.h>
#include <unistd.h>

#include <iostream>

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
  struct epoll_event events[LIMIT];
  std::map<int, Client> clients;
  std::map<int, int> client_to_server;
  while (true) {
    int num_ready = epoll_wait(epoll_fd, events, LIMIT, TIMEOUT);
    for (int i = 0; i < num_ready; i++) {
      int event_fd = events[i].data.fd;
      if (sockets.find(event_fd) != sockets.end()) {
        int client_fd = request_handler::process_connect(epoll_fd, event_fd);
        if (client_fd >= 0) {
          Client c(client_fd);
          clients.insert(std::make_pair(client_fd, c));
          client_to_server[client_fd] = event_fd;
          std::cout << "Client connected" << std::endl;
        }
      } else if (clients.find(event_fd) != clients.end()) {
        int server_fd = client_to_server[event_fd];
        if (request_handler::process_request(
                epoll_fd, events[i].events, clients[event_fd],
                sockets[server_fd]) == DROP_CONNECTION) {
          std::cout << "Client disconnected" << std::endl;
          clients.erase(event_fd);
          client_to_server.erase(event_fd);
          close(event_fd);
        }
      }
    }
  }
}