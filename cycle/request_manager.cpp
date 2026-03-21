#include "loop.hpp"

/*
TODO parse Request and based on it create Response
*/
void process_request(int client_fd) {
  char buffer[1024] = {0};

  ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
  if (bytes_received == 0) {
    std::cout << "Client disconnected gracefully" << std::endl;
  } else if (bytes_received < 0) {
    std::cout << "Client disconnected" << std::endl;
  } else {
    std::cout << "!!!Received: " << buffer << std::endl;
    const char* response =
        "HTTP/1.1 200 OK\r\nContent-Length: 17\r\n\r\nMessage received\n";
    send(client_fd, response, strlen(response), 0);
  }
}