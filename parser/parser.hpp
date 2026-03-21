#ifndef PARSER_HPP
#define PARSER_HPP

#include <arpa/inet.h>

#include <cstdio>
#include <cstdlib>
#include <stdexcept>

uint32_t parse_string_ip(const char *ip_str);
uint16_t parse_string_port(const char *port_str);

#endif