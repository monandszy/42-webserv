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

int create_socket();
void bind_socket(int socket_fd, uint32_t ip_addr, uint16_t host);
void start_socket(int socket_fd);
void process_request(int client_fd);
int init_epoll();
void register_socket(int epoll_fd, int socket_fd);
int run();

#endif