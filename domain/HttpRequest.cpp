#include "HttpRequest.hpp"

HttpRequest::HttpRequest() {
  _method = NONE;
  _body_size = 0;
}

HttpRequest::HttpRequest(const HttpRequest& other) { *this = other; }

HttpRequest& HttpRequest::operator=(const HttpRequest& other) {
  if (this != &other) {
    _method = other._method;
    _uri = other._uri;
    _version = other._version;
    _headers = other._headers;
    _body = other._body;
    _body_size = other._body_size;
  }
  return *this;
}

HttpRequest::~HttpRequest() {}

const HttpMethod& HttpRequest::getMethod() const { return _method; }
const std::string& HttpRequest::getUri() const { return _uri; }
const std::string& HttpRequest::getVersion() const { return _version; }
const std::map<std::string, std::string>& HttpRequest::getHeaders() const {
  return _headers;
}
const std::string& HttpRequest::getBody() const { return _body; }
size_t HttpRequest::getBodySize() const { return _body_size; }

const std::string& HttpRequest::getHeader(const std::string& key) const {
  static const std::string empty = "";
  std::map<std::string, std::string>::const_iterator it = _headers.find(key);
  if (it != _headers.end()) {
    return it->second;
  }
  return empty;
}

void HttpRequest::setMethod(const HttpMethod& method) { _method = method; }
void HttpRequest::setUri(const std::string& uri) { _uri = uri; }
void HttpRequest::setVersion(const std::string& version) { _version = version; }
void HttpRequest::setHeaders(
    const std::map<std::string, std::string>& headers) {
  _headers = headers;
}
void HttpRequest::setBody(const std::string& body) { _body = body; }
void HttpRequest::setBodySize(size_t size) { _body_size = size; }

void HttpRequest::setHeader(const std::string& key, const std::string& value) {
  _headers[key] = value;
}

void HttpRequest::reset() {
  _method = NONE;
  _uri.clear();
  _version.clear();
  _headers.clear();
  _body.clear();
  _body_size = 0;
}