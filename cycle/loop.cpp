#include "loop.hpp"

#include "../domain/domain.hpp"

void process_connect(int epoll_fd, int socket_fd) {
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

void loop_epoll(int epoll_fd, std::map<int, Server>& sockets) {
  const int limit = 10;
  struct epoll_event events[limit];
  while (true) {
    int num_ready = epoll_wait(epoll_fd, events, limit, -1);
    for (int i = 0; i < num_ready; i++) {
      int client_fd = events[i].data.fd;
      if (sockets.find(client_fd) != sockets.end()) {
        process_connect(epoll_fd, client_fd);
      } else {
        process_request(client_fd);
        close(client_fd);
      }
    }
  }
}

void run(const Root& root) {
  std::map<int, Server> sockets;
  init_sockets(root.getServers(), sockets);
  int epoll_fd = init_epoll(sockets);

  std::cout << "Server running" << std::endl;
  loop_epoll(epoll_fd, sockets);

  for (std::map<int, Server>::iterator it = sockets.begin();
       it != sockets.end(); ++it) {
    close(it->first);
  }
  close(epoll_fd);
}