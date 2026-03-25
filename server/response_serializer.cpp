#include <map>
#include <sstream>
#include <string>

#include "server.hpp"

void serializeStatusLine(const HttpResponse& response, std::ostream& os) {
  os << response.getVersion() << " ";

  os << static_cast<int>(response.getStatus()) << " ";

  os << response.getReason();

  os << "\r\n";
}

void serializeHeaders(const HttpResponse& response, std::ostream& os) {
  const std::map<std::string, std::string>& headers = response.getHeaders();

  for (std::map<std::string, std::string>::const_iterator it = headers.begin();
       it != headers.end(); ++it) {
    os << it->first << ": " << it->second << "\r\n";
  }

  os << "\r\n";
}

void serializeBody(const HttpResponse& response, std::ostream& os) {
  if (!response.getBody().empty()) {
    os << response.getBody();
  }
}

/*
  Based on client.getResponse() build the final string
*/
std::string serialize(const HttpResponse& response) {
  std::stringstream ss;

  serializeStatusLine(response, ss);
  serializeHeaders(response, ss);
  serializeBody(response, ss);

  return ss.str();
}

HandleResult response_serializer::process_response(Client& client,
                                                   Server& server) {
  if (client.getResponseBuffer().empty()) {
    client.setResponse(router::route_request(client.getRequest(), server));
    client.appendResponseBuffer(serialize(client.getResponse()));
    std::cout << "Fully parsed " << client << "\n";
  }

  const std::string& buf = client.getResponseBuffer();
  ssize_t sent = send(client.getFd(), buf.c_str(), buf.size(), 0);

  if (sent <= 0) {
    return DROP_CONNECTION;
  }

  client.consumeResponse(sent);
  return KEEP_CONNECTION;
}