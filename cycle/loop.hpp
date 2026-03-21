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

int create_socket();
void bind_socket(int socket_fd, uint32_t ip_addr, uint16_t host);
void start_socket(int socket_fd);
int init_epoll(std::map<int, Server>& sockets);
void register_socket(int epoll_fd, int socket_fd);
void process_request(int client_fd);
void run(const Root& root);
void init_sockets(const std::vector<Server>& servers,
                  std::map<int, Server>& sockets);

#endif