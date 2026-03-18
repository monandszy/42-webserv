#ifndef SERVER_HPP
#define SERVER_HPP

#include <map>
#include <string>
#include <vector>

class Location;

class Server {
 private:
  Server();
  const std::string _host;
  const int _port;
  const std::string _name;

  // status code, url
  std::map<int, std::string> _error_pages;
  std::vector<Location> _locations;

 public:
  Server(const std::string& host, int port, const std::string& name);
  Server(const Server& other);
  Server& operator=(const Server& other);
  ~Server();

  const std::string& getHost() const;
  int getPort() const;
  const std::string& getName() const;
  const std::map<int, std::string>& getErrorPages() const;
  const std::vector<Location>& getLocations() const;

  void addErrorPage(int code, const std::string& url);
  void addLocation(const Location& location);
};

#endif