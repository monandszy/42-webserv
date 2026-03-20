#include "Server.hpp"

#include "Location.hpp"

Server::Server(const std::string& host, int port, const std::string& name)
    : _host(host), _port(port), _name(name) {}

Server::Server(const Server& other)
    : _host(other._host), _port(other._port), _name(other._name) {
  *this = other;
}

Server& Server::operator=(const Server& other) {
  if (this != &other) {
    _error_pages = other._error_pages;
    _locations = other._locations;
  }
  return *this;
}

Server::~Server() {}

const std::string& Server::getHost() const { return _host; }
int Server::getPort() const { return _port; }
const std::string& Server::getName() const { return _name; }
const std::map<int, std::string>& Server::getErrorPages() const {
  return _error_pages;
}
const std::vector<Location>& Server::getLocations() const { return _locations; }

void Server::addErrorPage(int code, const std::string& url) {
  _error_pages[code] = url;
}

void Server::addLocation(const Location& location) {
  _locations.push_back(location);
}
