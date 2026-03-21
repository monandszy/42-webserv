#ifndef HTTPREQUEST_HPP
#define HTTPREQUEST_HPP

#include <map>
#include <string>

class HttpRequest {
 private:
  std::map<std::string, std::string> _headers;
  std::string _body;

 public:
  HttpRequest();
  HttpRequest(const HttpRequest& other);
  HttpRequest& operator=(const HttpRequest& other);
  ~HttpRequest();
};

#endif