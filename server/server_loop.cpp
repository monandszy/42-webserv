#include "../domain/domain.hpp"
#include "server.hpp"

void server::run(const Root& root) {
  std::map<int, Server> sockets;
  listener::init_sockets(root.getServers(), sockets);
  int epoll_fd = poller::init_epoll(sockets);

  std::cout << "Server running" << std::endl;
  poller::loop_epoll(epoll_fd, sockets);

  for (std::map<int, Server>::iterator it = sockets.begin();
       it != sockets.end(); ++it) {
    close(it->first);
  }
  close(epoll_fd);
}