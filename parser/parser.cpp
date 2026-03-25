#include "parser.hpp"

uint32_t parser::parse_string_ip(const char *ip_str) {
  unsigned int a, b, c, d;

  if (sscanf(ip_str, "%u.%u.%u.%u", &a, &b, &c, &d) != 4) {
    throw std::invalid_argument("Failed to parse 4 ip segments");
  }
  if (a > 255 || b > 255 || c > 255 || d > 255) {
    throw std::invalid_argument("Ip values non valid octets");
  }
  uint32_t host_ip = (a << 24) | (b << 16) | (c << 8) | d;
  return htonl(host_ip);
}

uint16_t parser::parse_string_port(const char *port_str) {
  char *endptr;
  long port_num = std::strtol(port_str, &endptr, BASE);

  if (*endptr != '\0' || port_num <= 0 || port_num > 65535) {
    throw std::invalid_argument("Invalid port number");
  }

  return htons((uint16_t)port_num);
}