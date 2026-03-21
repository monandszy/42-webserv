#include <fstream>
#include <iostream>

#include "domain/domain.hpp"
#include "fixtures/provider.hpp"
#include "parser/parser.hpp"
#include "server/server.hpp"

int main(int argc, char *argv[]) {
  if (argc > 2) {
    return (std::cerr << "./webserv [configuration file]" << std::endl, 1);
  } else if (argc == 2) {
    std::ifstream in(argv[1]);
    if (!in.is_open()) {
      return (std::cerr << "Could not open configuration file" << std::endl, 1);
    }
  }
  // TODO actually parse the file
  Root root = createRootFixture();
  server::run(root);
}