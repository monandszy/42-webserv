#ifndef ROOT_HPP
#define ROOT_HPP

#include <string>
#include <vector>

class Server;

class Root {
 private:
  std::string _client_max_body_size;

  std::vector<Server> _servers;

 public:
  Root();
  Root(const std::string& client_max_body_size);
  Root(const Root& other);
  Root& operator=(const Root& other);
  ~Root();

  const std::string& getClientMaxBodySize() const;
  const std::vector<Server>& getServers() const;
};

#endif
