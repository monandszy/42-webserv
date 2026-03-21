#include "Root.hpp"

#include "Server.hpp"

Root::Root() { _body_size = 1024; }

Root::Root(const Root& other) { *this = other; }

Root& Root::operator=(const Root& other) {
  if (this != &other) {
    _body_size = other._body_size;
    _servers = other._servers;
  }
  return *this;
}

Root::~Root() {}

unsigned long Root::getBodySize() const { return _body_size; }
const std::vector<Server>& Root::getServers() const { return _servers; }
void Root::setBodySize(unsigned long body_size) { _body_size = body_size; }
void Root::addServer(const Server& server) { _servers.push_back(server); }
