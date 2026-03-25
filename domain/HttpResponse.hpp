#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include <map>
#include <ostream>
#include <string>

#include "HttpStatus.hpp"

class HttpResponse {
 private:
  std::string _version;
  HttpStatus _status;
  std::string _reason;
  std::map<std::string, std::string> _headers;
  std::string _body;
  size_t _body_size;

 public:
  HttpResponse();
  HttpResponse(const HttpResponse& other);
  HttpResponse& operator=(const HttpResponse& other);
  ~HttpResponse();

  const std::string& getVersion() const;
  HttpStatus getStatus() const;
  const std::string& getReason() const;
  const std::map<std::string, std::string>& getHeaders() const;
  const std::string& getHeader(const std::string& key) const;
  const std::string& getBody() const;
  size_t getBodySize() const;

  void setVersion(const std::string& version);
  void setStatus(HttpStatus status);
  void setReason(const std::string& reason);
  void setHeader(const std::string& key, const std::string& value);
  void setBody(const std::string& body);
  void setBodySize(size_t size);

  void reset();
};

std::ostream& operator<<(std::ostream& os, const HttpResponse& res);

#endif