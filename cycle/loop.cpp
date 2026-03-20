#include "loop.hpp"

void process_connect(int epoll_fd, int socket_fd) {
  struct sockaddr_in addr;
  socklen_t len = sizeof(addr);

  int client_fd = accept(socket_fd, (struct sockaddr*)&addr, &len);
  if (client_fd >= 0) {
    std::cout << "New client connected." << std::endl;

    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = client_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &event);
  }
}

void loop_epoll(int epoll_fd, int socket_fd) {
  const int limit = 10;
  struct epoll_event events[limit];
  while (true) {
    int num_ready = epoll_wait(epoll_fd, events, limit, -1);
    for (int i = 0; i < num_ready; i++) {
      int client_fd = events[i].data.fd;
      if (client_fd == socket_fd) {
        process_connect(epoll_fd, socket_fd);
      } else {
        process_request(client_fd);
        close(client_fd);
      }
    }
  }
}

int run() {
  int socket_fd = create_socket();
  bind_socket(socket_fd, INADDR_ANY, htons(8080));
  start_socket(socket_fd);

  int epoll_fd = init_epoll();
  register_socket(epoll_fd, socket_fd);

  std::cout << "Server running" << std::endl;
  loop_epoll(epoll_fd, socket_fd);

  close(socket_fd);
  close(epoll_fd);
  return 0;
}