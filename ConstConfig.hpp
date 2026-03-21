#ifndef CONSTCONFIG_HPP
#define CONSTCONFIG_HPP

#include <string>
#include <vector>

namespace Header {
const std::string CONTENT_LENGTH = "content-length";
const std::string CONNECTION = "connection";
}  // namespace Header

namespace HeaderValue {
const std::string KEEP_ALIVE = "keep-alive";
const std::string CLOSE = "close";
}  // namespace HeaderValue

const std::string HTTP_END = "\r\n\r\n";
const int TIMEOUT = -1;
const bool REUSE_ADDRESS = 1;
const int LIMIT = 64;
const size_t RECV_SIZE = 11;
const int BASE = 10;

#endif