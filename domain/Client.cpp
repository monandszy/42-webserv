#include "Client.hpp"

#include "../parser/parser.hpp"

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

void Client::buildRequest(size_t end_pos) {
  std::string head = _buffer.substr(0, end_pos);
  parser::parseHead(head, _request);
}

void Client::buildRequestBody() {
  _request.setBody(_buffer.substr(0, _request.getBodySize()));
}

void Client::setStatus(CLIENT_STATUS status) { _status = status; }

void Client::consume(size_t n) { _buffer.erase(0, n); }

void Client::append(const char* data, size_t len) { _buffer.append(data, len); }

void Client::reset() {
  _status = READING_HEADERS;
  _request.reset();
}

std::ostream& operator<<(std::ostream& os, const Client& client) {
  std::string statusStr;
  switch (client.getStatus()) {
    case READING_HEADERS:
      statusStr = "READING_HEADERS";
      break;
    case READING_BODY:
      statusStr = "READING_BODY";
      break;
    case READY_TO_RESPOND:
      statusStr = "READY_TO_RESPOND";
      break;
    default:
      statusStr = "UNKNOWN";
      break;
  }

  os << "Client {\n"
     << "  FD: " << client.getFd() << "\n"
     << "  Status: " << statusStr << "\n"
     << "  Buffer:\n[" << client.getBuffer() << "]\n"
     << "  Request: " << client.getRequest() << "\n"
     << "}";
  return os;
}