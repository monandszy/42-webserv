#include "Root.hpp"

#include "Server.hpp"

Root::Root() { _client_max_body_size = "1m"; }

Root::Root(const std::string& client_max_body_size) {
  _client_max_body_size = client_max_body_size;
}

Root::Root(const Root& other) { *this = other; }

Root& Root::operator=(const Root& other) {
  if (this != &other) {
    _client_max_body_size = other._client_max_body_size;
    _servers = other._servers;
  }
  return *this;
}

Root::~Root() {}

const std::string& Root::getClientMaxBodySize() const {
  return _client_max_body_size;
}
const std::vector<Server>& Root::getServers() const { return _servers; }
