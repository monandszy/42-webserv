#include "Client.hpp"

Client::Client() {
  _fd = -1;
  _status = READING_HEADERS;
  _buffer = "";
}

Client::Client(int fd) {
  _fd = fd;
  _status = READING_HEADERS;
  _buffer = "";
}

Client::Client(const Client& other) { *this = other; }

Client& Client::operator=(const Client& other) {
  if (this != &other) {
    _fd = other._fd;
    _status = other._status;
    _buffer = other._buffer;
    _request = other._request;
  }
  return *this;
}

Client::~Client() {}

int Client::getFd() const { return _fd; }

CLIENT_STATUS Client::getStatus() const { return _status; }

const std::string& Client::getBuffer() const { return _buffer; }

const HttpRequest& Client::getRequest() const { return _request; }

void Client::setStatus(CLIENT_STATUS status) { _status = status; }

void Client::append(const char* buf, ssize_t len) {
  if (buf != NULL && len > 0) {
    _buffer.append(buf, len);
  }
}

void Client::clearBuffer() { _buffer.clear(); }