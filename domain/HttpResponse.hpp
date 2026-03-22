#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

#include <map>
#include <string>

class HttpResponse {
 public:
  HttpResponse();
  HttpResponse(const HttpResponse& other);
  HttpResponse& operator=(const HttpResponse& other);
  ~HttpResponse();
  void reset();
};

std::ostream& operator<<(std::ostream& os, const HttpResponse& res);

#endif