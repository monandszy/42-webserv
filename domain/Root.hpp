#ifndef ROOT_HPP
#define ROOT_HPP

#include <string>
#include <vector>

class Server;

class Root{
private:
  std::string _client_max_body_size;

  std::vector<Server> _servers;

  Root();
};

#endif
