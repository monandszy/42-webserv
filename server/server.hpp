#ifndef LOOP_HPP
#define LOOP_HPP

#include <arpa/inet.h>
#include <fcntl.h>
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
#include "ConstConfig.hpp"

namespace server {
void run(const Root& root);
}
namespace listener {
void init_sockets(const std::vector<Server>& servers,
                  std::map<int, Server>& sockets);
}

namespace multiplexer {
int init_epoll(std::map<int, Server>& sockets);
void loop_epoll(int epoll_fd, std::map<int, Server>& sockets);
}  // namespace multiplexer

namespace request_handler {
int process_connect(int epoll_fd, int socket_fd);
int process_request(Client& client);
}  // namespace request_handler

#endif