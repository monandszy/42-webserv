#include "Root.hpp"

#include "Server.hpp"

Root::Root() { _body_size = "1m"; }

Root::Root(const Root& other) { *this = other; }

Root& Root::operator=(const Root& other) {
  if (this != &other) {
    _body_size = other._body_size;
    _servers = other._servers;
  }
  return *this;
}

Root::~Root() {}

const std::string& Root::getBodySize() const { return _body_size; }
const std::vector<Server>& Root::getServers() const { return _servers; }
void Root::setBodySize(const std::string& size) { _body_size = size; }
void Root::addServer(const Server& server) { _servers.push_back(server); }
