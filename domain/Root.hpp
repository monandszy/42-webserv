#ifndef ROOT_HPP
#define ROOT_HPP

#include <string>
#include <vector>

class Server;

class Root {
 private:
  unsigned long _body_size;

  std::vector<Server> _servers;

 public:
  Root();
  Root(const Root& other);
  Root& operator=(const Root& other);
  ~Root();

  unsigned long getBodySize() const;
  const std::vector<Server>& getServers() const;

  void setBodySize(unsigned long body_size);
  void addServer(const Server& server);
};

#endif
