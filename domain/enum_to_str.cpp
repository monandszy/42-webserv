
#include "HttpMethod.hpp"
#include "HttpStatus.hpp"

std::string http_method_to_str(HttpMethod method) {
  switch (method) {
    case GET:
      return ("GET");
    case POST:
      return ("POST");
    case DELETE:
      return ("DELETE");
    default:
      return ("UNKNOWN");
  }
}

std::string http_status_to_str(HttpStatus status) {
  switch (status) {
    case CONTINUE:
      return ("Continue");
    case SWITCHING_PROTOCOLS:
      return ("Switching Protocols");

    case OK:
      return ("OK");
    case CREATED:
      return ("Created");
    case ACCEPTED:
      return ("Accepted");
    case NO_CONTENT:
      return ("No Content");

    case MOVED_PERMANENTLY:
      return ("Moved Permanently");
    case FOUND:
      return ("Found");
    case NOT_MODIFIED:
      return ("Not Modified");

    case BAD_REQUEST:
      return ("Bad Request");
    case UNAUTHORIZED:
      return ("Unauthorized");
    case FORBIDDEN:
      return ("Forbidden");
    case NOT_FOUND:
      return ("Not Found");
    case METHOD_NOT_ALLOWED:
      return ("Method Not Allowed");
    case REQUEST_TIMEOUT:
      return ("Request Timeout");
    case CONFLICT:
      return ("Conflict");
    case PAYLOAD_TOO_LARGE:
      return ("Payload Too Large");
    case TOO_MANY_REQUESTS:
      return ("Too Many Requests");

    case INTERNAL_SERVER_ERROR:
      return ("Internal Server Error");
    case NOT_IMPLEMENTED:
      return ("Not Implemented");
    case BAD_GATEWAY:
      return ("Bad Gateway");
    case SERVICE_UNAVAILABLE:
      return ("Service Unavailable");
    case GATEWAY_TIMEOUT:
      return ("Gateway Timeout");
    default:
      return ("Unknown Status");
  }
}