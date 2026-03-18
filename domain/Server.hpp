#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <vector>
#include <map>

class Location;

class Server {
private:
  std::string _host; 
  int _port;

  std::string _name;

  // status code, url
  std::map<int, std::string> _error_pages;

  std::vector<Location> _locations;

  Server();
};

#endif