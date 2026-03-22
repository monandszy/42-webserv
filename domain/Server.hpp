#ifndef SERVER_HPP
#define SERVER_HPP

#include <map>
#include <string>
#include <vector>

#include "../ConstConfig.hpp"

class Location;

class Server {
 private:
  const std::string _host;
  const std::string _port;
  const std::string _name;
  unsigned long _body_size;

  // status code, url
  std::map<int, std::string> _error_pages;
  std::vector<Location> _locations;

 public:
  Server();
  Server(const std::string& host, const std::string& port,
         const std::string& name);
  Server(const Server& other);
  Server& operator=(const Server& other);
  ~Server();

  const std::string& getHost() const;
  const std::string& getPort() const;
  const std::string& getName() const;
  const std::map<int, std::string>& getErrorPages() const;
  const std::vector<Location>& getLocations() const;
  unsigned long getBodySize() const;

  void addErrorPage(int code, const std::string& url);
  void addLocation(const Location& location);

  void setBodySize(unsigned long body_size);
};

#endif