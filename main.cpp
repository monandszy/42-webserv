#include <fstream>
#include <iostream>

#include "domain/Domain.hpp"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    return (std::cerr << "./webserv [configuration file]", 1);
  }
  std::ifstream in(argv[1]);
  if (!in.is_open()) {
    return (std::cerr << "Could not open configuration file", 1);
  }
  // parse the file
  Root root;
}