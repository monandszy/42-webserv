#include "Root.hpp"

#include "Server.hpp"

Root::Root() { _body_size = "1m"; }

void Root::setBodySize(const std::string& body_size) { _body_size = body_size; }

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
void Root::setClientMaxBodySize(const std::string& size) {
  _client_max_body_size = size;
}
void Root::addServer(const Server& server) { _servers.push_back(server); }
