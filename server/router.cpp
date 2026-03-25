#include <sstream>

#include "server.hpp"

HttpResponse router::route_request(const HttpRequest& request, Server& server) {
  HttpResponse response;
  if (request.getBodySize() > server.getBodySize()) {
    response.setStatus(PAYLOAD_TOO_LARGE);
  } else {
    response.setStatus(OK);
    response.setBody("Message");
    response.setReason(http_status_to_str(OK));
    response.setBodySize(7);
  }

  response.setVersion("HTTP/1.1");

  std::ostringstream oss;
  oss << response.getBodySize();
  response.setHeader(Header::CONTENT_LENGTH, oss.str());

  return response;
}