#include <fstream>
#include <iostream>

#include "cycle/loop.hpp"
#include "domain/domain.hpp"
#include "fixtures/provider.hpp"
#include "parser/parser.hpp"

int main(int argc, char *argv[]) {
  if (argc > 2) {
    return (std::cerr << "./webserv [configuration file]" << std::endl, 1);
  } else if (argc == 2) {
    std::ifstream in(argv[1]);
    if (!in.is_open()) {
      return (std::cerr << "Could not open configuration file" << std::endl, 1);
    }
  }
  // parse the file
  Root root = createRootFixture();
  run();
}