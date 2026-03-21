#ifndef ROOT_HPP
#define ROOT_HPP

#include <string>
#include <vector>

class Server;

class Root {
 private:
  std::string _body_size;  // TODO figure out the format for parsing, maybe it could just be the num of bytes instead of 1m etc, figure out how this will be used.

  std::vector<Server> _servers;

 public:
  Root();
  Root(const Root& other);
  Root& operator=(const Root& other);
  ~Root();

  const std::string& getBodySize() const;
  const std::vector<Server>& getServers() const;

  void setBodySize(const std::string& body_size);
  void addServer(const Server& server);
};

#endif
