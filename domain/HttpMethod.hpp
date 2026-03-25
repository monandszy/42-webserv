#ifndef HTTPMETHOD_HPP
#define HTTPMETHOD_HPP

#include <string>

enum HttpMethod { UNKNOWN, GET, POST, DELETE };

std::string http_method_to_str(HttpMethod method);

#endif