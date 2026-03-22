#ifndef PARSER_HPP
#define PARSER_HPP

#include <arpa/inet.h>

#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>

#include "../ConstConfig.hpp"
#include "../domain/domain.hpp"

namespace parser {
uint32_t parse_string_ip(const char* ip_str);
uint16_t parse_string_port(const char* port_str);
HttpRequest parseHead(const std::string& raw);
}  // namespace parser

#endif