#include "Client.hpp"

#include "../parser/parser.hpp"

Client::Client() {
  _fd = -1;
  _status = READING_HEAD;
  _responsebuffer = "";
  _requestbuffer = "";
}

Client::Client(int fd) {
  _fd = fd;
  _status = READING_HEAD;
  _responsebuffer = "";
  _requestbuffer = "";
}

Client::Client(const Client& other) { *this = other; }

Client& Client::operator=(const Client& other) {
  if (this != &other) {
    _fd = other._fd;
    _status = other._status;
    _requestbuffer = other._requestbuffer;
    _responsebuffer = other._responsebuffer;
    _request = other._request;
  }
  return *this;
}

Client::~Client() {}

int Client::getFd() const { return _fd; }

ClientStatus Client::getStatus() const { return _status; }

const std::string& Client::getRequestBuffer() const { return _requestbuffer; }

const std::string& Client::getResponseBuffer() const { return _responsebuffer; }

const HttpRequest& Client::getRequest() const { return _request; }
const HttpResponse& Client::getResponse() const { return _response; }

void Client::setRequest(const HttpRequest& request) { _request = request; }
void Client::setResponse(const HttpResponse& response) { _response = response; }

void Client::consumeRequest(size_t n) { _requestbuffer.erase(0, n); }

void Client::appendRequest(const char* data, size_t len) {
  _requestbuffer.append(data, len);
}

void Client::consumeResponse(size_t n) { _responsebuffer.erase(0, n); }

void Client::appendResponse(const std::string& data) {
  _responsebuffer.append(data);
}

void Client::setStatus(ClientStatus status) { _status = status; }

void Client::reset() {
  _status = READING_HEAD;
  _request.reset();
  _response.reset();
  _responsebuffer.clear();
}

std::string client_status_to_str(ClientStatus status) {
  switch (status) {
    case READING_HEAD:
      return ("READING_HEAD");
    case READING_BODY:
      return ("READING_BODY");
    case READY_TO_RESPOND:
      return ("READY_TO_RESPOND");
    default:
      return ("UNKNOWN");
  }
}

std::ostream& operator<<(std::ostream& os, const Client& client) {
  os << "Client {\n"
     << "  FD: " << client.getFd() << "\n"
     << "  Status: " << client_status_to_str(client.getStatus()) << "\n"
     << "  RequestBuffer:\n[" << client.getRequestBuffer() << "]\n"
     << "  ResponseBuffer:\n[" << client.getResponseBuffer() << "]\n"
     << "  Request: " << client.getRequest() << "\n"
     << "  Response: " << client.getResponse() << "\n"
     << "}";
  return os;
}