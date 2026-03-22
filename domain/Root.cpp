#include "Root.hpp"

#include "Server.hpp"

Root::Root() {}

Root::Root(const Root& other) { *this = other; }

Root& Root::operator=(const Root& other) {
  if (this != &other) {
    _servers = other._servers;
  }
  return *this;
}

Root::~Root() {}

const std::vector<Server>& Root::getServers() const { return _servers; }
void Root::addServer(const Server& server) { _servers.push_back(server); }
