#include "parser.hpp"

std::string trim(const std::string& s) {
  const std::string whitespace = " \t\r\n";
  size_t first = s.find_first_not_of(whitespace);
  if (first == std::string::npos) return "";
  size_t last = s.find_last_not_of(whitespace);
  return s.substr(first, (last - first + 1));
}

void parseRequestLine(const std::string& line, HttpRequest& request) {
  std::istringstream line_stream(line);
  std::string method, uri, version;
  line_stream >> method >> uri >> version;

  if (method == "GET")
    request.setMethod(GET);
  else if (method == "POST")
    request.setMethod(POST);
  else if (method == "DELETE")
    request.setMethod(DELETE);
  else
    throw std::runtime_error("Unknown HTTP metod!");

  request.setUri(uri);
  request.setVersion(version);
}

void parseHeaderLine(const std::string& line, HttpRequest& request) {
  size_t colon_pos = line.find(':');
  if (colon_pos != std::string::npos) {
    std::string key = trim(line.substr(0, colon_pos));
    std::string value = trim(line.substr(colon_pos + 1));
    request.setHeader(key, value);
  }
}

void parser::parseHead(const std::string& raw, HttpRequest& request) {
  std::istringstream stream(raw);
  std::string line;

  if (std::getline(stream, line)) {
    parseRequestLine(line, request);
  }

  while (std::getline(stream, line)) {
    std::string trimmed_line = trim(line);
    if (trimmed_line.empty()) break;
    parseHeaderLine(line, request);
  }

  std::string content_length = request.getHeader(Header::CONTENT_LENGTH);
  if (!content_length.empty()) {
    request.setBodySize(std::strtoul(content_length.c_str(), NULL, BASE));
  } else {
    request.setBodySize(0);
  }
}