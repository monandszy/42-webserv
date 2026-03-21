#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include <sys/types.h>

#include <map>
#include <string>

class HttpRequest {
 private:
  std::string _method;
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

  const std::string& getMethod() const;
  const std::string& getUri() const;
  const std::string& getVersion() const;
  const std::map<std::string, std::string>& getHeaders() const;
  const std::string& getBody() const;
  size_t getBodySize() const;

  void setMethod(const std::string& method);
  void setUri(const std::string& uri);
  void setVersion(const std::string& version);
  void setHeaders(const std::map<std::string, std::string>& headers);
  void setBody(const std::string& body);
  void setBodySize(size_t size);
  void setHeader(const std::string& key, const std::string& value);

  void reset();
};

#endif