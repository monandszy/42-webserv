#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <sys/types.h>

#include <map>
#include <ostream>
#include <string>

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

enum CLIENT_STATUS {
  READING_HEAD,  // Waiting for \r\n\r\n HTTP_END
  READING_BODY,  // Waiting for body to match Content-Length
  READY_TO_RESPOND,
};

class Client {
 private:
  int _fd;
  CLIENT_STATUS _status;
  std::string _requestbuffer;
  std::string _responsebuffer;
  HttpRequest _request;
  HttpResponse _response;

 public:
  Client();
  Client(int fd);
  Client(const Client& other);
  Client& operator=(const Client& other);
  ~Client();
  int getFd() const;
  CLIENT_STATUS getStatus() const;
  const std::string& getRequestBuffer() const;
  const HttpRequest& getRequest() const;
  void consumeRequest(size_t n);
  void appendRequest(const char* data, size_t len);

  const std::string& getResponseBuffer() const;
  const HttpResponse& getResponse() const;

  void setRequest(const HttpRequest& request);
  void setResponse(const HttpResponse& response);

  void consumeResponse(size_t n);
  void appendResponse(const std::string& data);

  void setStatus(CLIENT_STATUS status);

  void reset();
};

std::ostream& operator<<(std::ostream& os, const Client& client);

#endif