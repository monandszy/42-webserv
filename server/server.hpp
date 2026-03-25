#ifndef LOOP_HPP
#define LOOP_HPP

#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include "../ConstConfig.hpp"
#include "../domain/domain.hpp"

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

enum HandleResult { KEEP_CONNECTION, DROP_CONNECTION };

namespace request_handler {
int process_connect(int epoll_fd, int socket_fd);
HandleResult process_request(int epoll_fd, uint32_t events, Client& client,
                             Server& server);
}  // namespace request_handler

namespace response_serializer {
HandleResult process_response(Client& client, Server& server);
}

namespace router {
HttpResponse route_request(const HttpRequest& request, Server& server);
}

#endif