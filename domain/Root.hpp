#ifndef ROOT_HPP
#define ROOT_HPP

#include <string>
#include <vector>

class Server;

class Root {
 private:
  std::string _body_size;

  std::vector<Server> _servers;

 public:
  Root();
  Root(const Root& other);
  Root& operator=(const Root& other);
  ~Root();

  const std::string& getBodySize() const;
  const std::vector<Server>& getServers() const;

  void setBodySize(const std::string& body_size);
};

#endif
