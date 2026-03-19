*This project has been created as part of the 42 curriculum by sandrzej, faikhan.*

### Description
A HTTP server in C++ 98

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
[RFC HTTP/1.0](https://datatracker.ietf.org/doc/html/rfc1945)
[Conf File Specs](https://nginx.org/en/docs/beginners_guide.html)
[Error Page Conf](https://serverfault.com/questions/481140/nginx-default-error-page)

## Configuration Specification (.conf)
### Global scope - http{} block
- `body_size <size>`: Sets the maximum allowed size for a client's request body (e.g., 10m, 1g, etc).
### Server scope - server{} block
- `listen <host>:<port>`: Specifies the IP address and port the server binds to (e.g., 127.0.0.1:8080).
- `name <name>`: The domain name or identifier for the virtual server (e.g., first.com).
- `error_page <code...> <path>`: Associates one or more HTTP error codes with a custom error HTML page (e.g., error_page 404 /404.html; or error_page 500 502 /50x.html;).
### Route scope - location{} block
- `accept <methods...>`: Specifies the allowed HTTP methods for the endpoint (e.g., GET POST).
- `root <directory>`: The base directory for file resolution. The requested URI is appended to this path (e.g., if root is /tmp/www, a request to /test/page resolves to /tmp/www/page).
- `index <files...>`: The default file(s) to serve when a directory is requested (e.g., index.html index.htm;).
- `autoindex <on|off>`: Enables or disables automatic directory listing (Generates an index.html, listing the structure. If off returns 403 Forbidden).
- `redirect <code> <url>`: Configures HTTP redirection, returning the specified status code and redirecting to the target URL (e.g., redirect 301 http://example.com/new-url;).
- `upload <on|off>`: Authorizes file uploads for the endpoint.
- `upload_store <directory>`: Specifies the directory where uploaded files will be to saved
- `cgi_pass <extension> <executable_path>`: Specifies an executable to process a given file extension

## TODO
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

setsockopt: int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
  for setting socket options
getsockname: int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
getprotobyname: truct protoent *getprotobyname(const char *name);

getaddrinfo: int getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res);
  translates domain names and services (like "google.com", "http") into IP addresses and port numbers.
freeaddrinfo: void freeaddrinfo(struct addrinfo *res);
gai_strerror: const char *gai_strerror(int errcode);

epoll (epoll_create, epoll_ctl, epoll_wait)
int epoll_create(int size);
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);




