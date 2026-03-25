#include "HttpResponse.hpp"

HttpResponse::HttpResponse() {
  _status = OK;
  _body_size = 0;
}

HttpResponse::HttpResponse(const HttpResponse& other) { *this = other; }

HttpResponse& HttpResponse::operator=(const HttpResponse& other) {
  if (this != &other) {
    _version = other._version;
    _status = other._status;
    _reason = other._reason;
    _headers = other._headers;
    _body = other._body;
    _body_size = other._body_size;
  }
  return *this;
}

HttpResponse::~HttpResponse() {}

const std::string& HttpResponse::getVersion() const { return _version; }
HttpStatus HttpResponse::getStatus() const { return _status; }
const std::string& HttpResponse::getReason() const { return _reason; }
const std::map<std::string, std::string>& HttpResponse::getHeaders() const {
  return _headers;
}
const std::string& HttpResponse::getBody() const { return _body; }
size_t HttpResponse::getBodySize() const { return _body_size; }

const std::string& HttpResponse::getHeader(const std::string& key) const {
  static const std::string empty = "";
  std::map<std::string, std::string>::const_iterator it = _headers.find(key);
  if (it != _headers.end()) {
    return it->second;
  }
  return empty;
}

void HttpResponse::setVersion(const std::string& version) {
  _version = version;
}
void HttpResponse::setStatus(HttpStatus status) { _status = status; }
void HttpResponse::setReason(const std::string& reason) { _reason = reason; }
void HttpResponse::setHeader(const std::string& key, const std::string& value) {
  _headers[key] = value;
}
void HttpResponse::setBody(const std::string& body) { _body = body; }
void HttpResponse::setBodySize(size_t size) { _body_size = size; }

void HttpResponse::reset() {
  _version.clear();
  _status = OK;
  _reason.clear();
  _headers.clear();
  _body.clear();
  _body_size = 0;
}

std::ostream& operator<<(std::ostream& os, const HttpResponse& res) {
  os << "HttpResponse {\n"
     << "  Version: " << res.getVersion() << "\n"
     << "  Status: " << static_cast<int>(res.getStatus()) << "\n"
     << "  Reason: " << res.getReason() << "\n"
     << "  Headers: \n";

  std::map<std::string, std::string>::const_iterator it;
  for (it = res.getHeaders().begin(); it != res.getHeaders().end(); ++it) {
    os << "    " << it->first << ": " << it->second << "\n";
  }

  os << "  Body Size: " << res.getBodySize() << "\n"
     << "  Body: " << res.getBody() << "\n"
     << "}";
  return os;
}