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
execve, pipe, errno, dup, dup2, fork, strerror, chdir 

htons, htonl, ntohs, ntohl, 

select
poll
epoll (epoll_create, epoll_ctl, epoll_wait)
kqueue (kqueue, kevent)

socket, socketpair

bind, listen, accept, connect

send, recv

getaddrinfo, freeaddrinfo, gai_strerror

setsockopt, getsockname, getprotobyname

waitpid, kill, signal,

fcntl, close, read, write

access, stat, open, opendir, readdir, closedir


