*This project has been created as part of the 42 curriculum by sandrzej, faikhan.*

### Description
A HTTP server in C++ 98, offering a subset of the HTTP 1.0 RFC.

### Instructions
#### Build the program:
```bash
  make
```
#### Run the executable with a configuration file:
```bash
./webserv [configuration file]
```

### Resources
- [RFC HTTP/1.0](https://datatracker.ietf.org/doc/html/rfc1945)
- [Conf File Specs](https://nginx.org/en/docs/beginners_guide.html)
- [Error Page Conf](https://serverfault.com/questions/481140/nginx-default-error-page)
- https://en.wikipedia.org/wiki/Transmission_Control_Protocol
- https://www.geeksforgeeks.org/cpp/socket-programming-in-cpp/
- https://unscriptedcoding.medium.com/multithreaded-server-in-c-using-epoll-baadad32224c
- http://dwise1.net/pgm/sockets/blocking.html

### Configuration Specification (.conf)
#### Global scope - http{} block
- `body_size <size>`: Sets the maximum allowed size for a client's request body (in bytes).
#### Server scope - server{} block
- `listen <host>:<port>`: Specifies the IP address and port the server binds to (e.g., 127.0.0.1:8080).
- `name <name>`: The domain name or identifier for the virtual server (e.g., first.com).
- `error_page <code...> <path>`: Associates one or more HTTP error codes with a custom error HTML page (e.g., error_page 404 /404.html; or error_page 500 502 /50x.html;).
#### Route scope - location{} block
- `accept <methods...>`: Specifies the allowed HTTP methods for the endpoint (e.g., GET POST).
- `root <directory>`: The base directory for file resolution. The requested URI is appended to this path (e.g., if root is /tmp/www, a request to /test/page resolves to /tmp/www/page).
- `index <files...>`: The default file(s) to serve when a directory is requested (e.g., index.html index.htm;).
- `autoindex <on|off>`: Enables or disables automatic directory listing (Generates an index.html, listing the structure. If off returns 403 Forbidden).
- `redirect <code> <url>`: Configures HTTP redirection, returning the specified status code and redirecting to the target URL (e.g., redirect 301 http://example.com/new-url;).
- `upload <on|off>`: Authorizes file uploads for the endpoint.
- `upload_store <directory>`: Specifies the directory where uploaded files will be to saved
- `cgi_pass <extension> <executable_path>`: Specifies an executable to process a given file extension

### Requirements

- [ ] Your program must use a configuration file, provided as an argument on the com-
mand line, or available in a default path.
- [ ] You cannot execve another web server.
- [ ] Your server must remain non-blocking at all times and properly handle client disconnections when necessary.
- [ ] It must be non-blocking and use only 1 poll() (or equivalent) for all the I/O
operations between the clients and the server (listen included).
- [ ] poll() (or equivalent) must monitor both reading and writing simultaneously.
- [ ] You must never do a read or a write operation without going through poll() (or equivalent).
- [ ] Checking the value of errno to adjust the server behaviour is strictly forbidden
after performing a read or write operation.
- [ ] You are not required to use poll() (or an equivalent function) for regular disk files;
read() and write() on them do not require readiness notifications.

I/O that can wait for data (sockets, pipes/FIFOs, etc.) must be
non-blocking and driven by a single poll() (or equivalent). Calling
read/recv or write/send on these descriptors without prior readiness
will result in a grade of 0. Regular disk files are exempt.

- [v] When using poll() or any equivalent call, you can use every associated macro or
helper function (e.g., FD_SET for select()).
- [ ] A request to your server should never hang indefinitely.
- [ ] Your server must be compatible with standard web browsers of your choice.
- [ ] NGINX may be used to compare headers and answer behaviours (pay attention to differences between HTTP versions).
- [ ] Your HTTP response status codes must be accurate.
- [ ] Your server must have default error pages if none are provided.
- [ ] You can’t use fork for anything other than CGI (like PHP, or Python, and so forth).
- [ ] You must be able to serve a fully static website.
- [ ] Clients must be able to upload files.
- [ ] You need at least the GET, POST, and DELETE methods.
- [ ] Stress test your server to ensure it remains available at all times.
- [ ] Your server must be able to listen to multiple ports to deliver different content (see
Configuration file).

###  Functions Research
<cerrno>
<cstring>
<sys/wait.h>
<signal.h>
<fcntl.h>
<unistd.h>
<sys/stat.h>
<dirent.h>
<arpa/inet.h>
<sys/socket.h>
<netdb.h>
<sys/select.h>
<poll.h>
<sys/epoll.h>

errno: extern int errno;
  macro representing the current error code
strerror: char *strerror(int errnum);
  returns string message of a given error code

fork: pid_t fork(void);
execve: int execve(const char *pathname, char *const argv[], char *const envp[]);
waitpid: pid_t waitpid(pid_t pid, int *status, int options);
  suspends parent process until child changes state

pipe: int pipe(int pipefd[2]);
dup: int dup(int oldfd);
dup2: int dup2(int oldfd, int newfd);

kill: int kill(pid_t pid, int sig);
  sends a signal
signal: void (*signal(int sig, void (*func)(int)))(int)
  takes a signal number and a function pointer, returns the previous handler

fcntl: int fcntl(int fd, int cmd, ...);
  manipulates file descriptors (setting non-blocking mode using O_NONBLOCK)
close: int close(int fd);
read: ssize_t read(int fd, void *buf, size_t count);
write: ssize_t write(int fd, const void *buf, size_t count);
open: int open(const char *pathname, int flags, ...);

access: int access(const char *pathname, int mode);
  checks path permissions
stat: int stat(const char *pathname, struct stat *statbuf);
  returns information about a file

chdir: int chdir(const char *path);
  changes working directory of the process
opendir: DIR *opendir(const char *name);
readdir: struct dirent *readdir(DIR *dirp);
closedir: int closedir(DIR *dirp);

uint16_t htons(uint16_t hostshort);
uint32_t htonl(uint32_t hostlong);
uint16_t ntohs(uint16_t netshort);
uint32_t ntohl(uint32_t netlong);

socket: int socket(int domain, int type, int protocol);
socketpair: int socketpair(int domain, int type, int protocol, int sv[2]);
bind: int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
listen: int listen(int sockfd, int backlog);
accept: int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
connect: int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

send: ssize_t send(int sockfd, const void *buf, size_t len, int flags);
recv: ssize_t recv(int sockfd, void *buf, size_t len, int flags);

epoll (epoll_create, epoll_ctl, epoll_wait)
int epoll_create(int size);
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);

setsockopt: int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
  for setting socket options
getsockname: int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
getprotobyname: truct protoent *getprotobyname(const char *name);

getaddrinfo: int getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res);
  translates domain names and services (like "google.com", "http") into IP addresses and port numbers.
freeaddrinfo: void freeaddrinfo(struct addrinfo *res);
gai_strerror: const char *gai_strerror(int errcode);


