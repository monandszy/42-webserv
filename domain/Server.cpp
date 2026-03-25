#include "Server.hpp"

#include "Location.hpp"

Server::Server() : _host(""), _port(""), _name("") { _body_size = 0; }

Server::Server(const std::string& host, const std::string& port,
               const std::string& name)
    : _host(host), _port(port), _name(name) {
  _body_size = MAX_BODY_SIZE;
}

Server::Server(const Server& other)
    : _host(other._host), _port(other._port), _name(other._name) {
  *this = other;
}

Server& Server::operator=(const Server& other) {
  if (this != &other) {
    _error_pages = other._error_pages;
    _locations = other._locations;
    _body_size = other._body_size;
  }
  return *this;
}

Server::~Server() {}

const std::string& Server::getHost() const { return _host; }
const std::string& Server::getPort() const { return _port; }
const std::string& Server::getName() const { return _name; }
unsigned long Server::getBodySize() const { return _body_size; }
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

void Server::setBodySize(unsigned long body_size) { _body_size = body_size; }