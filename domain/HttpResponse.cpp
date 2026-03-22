#include "HttpResponse.hpp"

HttpResponse::HttpResponse() {}

HttpResponse::HttpResponse(const HttpResponse& other) { *this = other; }

HttpResponse& HttpResponse::operator=(const HttpResponse& other) {
  if (this != &other) {
  }
  return *this;
}

HttpResponse::~HttpResponse() {}

void HttpResponse::reset() {}

std::ostream& operator<<(std::ostream& os, const HttpResponse& res) {
  (void)res;
  return os;
}