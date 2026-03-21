#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <sys/types.h>

#include <map>
#include <string>

#include "HttpRequest.hpp"

enum CLIENT_STATUS {
  READING_HEADERS,  // Waiting for \r\n\r\n HTTP_END
  READING_BODY,     // Waiting for body to match Content-Length
};

class Client {
 private:
  int _fd;
  CLIENT_STATUS _status;
  std::string _buffer;
  HttpRequest _request;

 public:
  Client();
  Client(int fd);
  Client(const Client& other);
  Client& operator=(const Client& other);
  ~Client();
  int getFd() const;
  CLIENT_STATUS getStatus() const;
  const std::string& getBuffer() const;
  const HttpRequest& getRequest() const;

  void setStatus(CLIENT_STATUS status);

  void append(const char* buf, ssize_t len);
  void clearBuffer();
};

#endif