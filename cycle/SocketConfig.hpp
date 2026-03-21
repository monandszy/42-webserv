#ifndef SOCKET_CONFIG_HPP
#define SOCKET_CONFIG_HPP

#include <string>
#include <vector>

/*
TODO Let's turn this into a static config file, with global configuration options for socket.
*/

struct SocketConfig {
  std::string host;
  int port;
  int backlog;
  int timeout;
  bool reuse_address;

  SocketConfig()
      : host("127.0.0.1"),
        port(8080),
        backlog(128),
        timeout(30),
        reuse_address(true) {}
};

#endif