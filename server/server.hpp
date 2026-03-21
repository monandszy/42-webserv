#ifndef LOOP_HPP
#define LOOP_HPP

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <map>
#include <vector>

#include "../domain/domain.hpp"

namespace server {
void run(const Root& root);
}
namespace listener {
void init_sockets(const std::vector<Server>& servers,
                  std::map<int, Server>& sockets);
}

namespace poller {
int init_epoll(std::map<int, Server>& sockets);
void loop_epoll(int epoll_fd, std::map<int, Server>& sockets);
}  // namespace poller

namespace request_handler {
void process_connect(int epoll_fd, int socket_fd);
void process_request(int client_fd);
}  // namespace request_handler

#endif