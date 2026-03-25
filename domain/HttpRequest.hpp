#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include <sys/types.h>

#include <map>
#include <ostream>
#include <string>

#include "HttpMethod.hpp"

class HttpRequest {
 private:
  HttpMethod _method;
  std::string _uri;
  std::string _version;
  std::map<std::string, std::string> _headers;
  std::string _body;
  size_t _body_size;

 public:
  HttpRequest();
  HttpRequest(const HttpRequest& other);
  HttpRequest& operator=(const HttpRequest& other);
  ~HttpRequest();
  const std::string& getHeader(const std::string& key) const;

  const HttpMethod& getMethod() const;
  const std::string& getUri() const;
  const std::string& getVersion() const;
  const std::map<std::string, std::string>& getHeaders() const;
  const std::string& getBody() const;
  size_t getBodySize() const;

  void setMethod(const HttpMethod& method);
  void setUri(const std::string& uri);
  void setVersion(const std::string& version);
  void setBody(const std::string& body);
  void setBodySize(size_t size);
  void setHeader(const std::string& key, const std::string& value);

  void reset();
};

std::ostream& operator<<(std::ostream& os, const HttpRequest& req);

#endif