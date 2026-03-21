#ifndef CONSTCONFIG_HPP
#define CONSTCONFIG_HPP

#include <string>
#include <vector>

const std::string HTTP_END = "\r\n\r\n";
const std::string CONTENT_LENGTH = "content-length";
const std::string KEEP_ALIVE = "keep-alive";
const int TIMEOUT = -1;
const bool REUSE_ADDRESS = 1;
const int LIMIT = 64;
const size_t RECV_SIZE = 11;

#endif