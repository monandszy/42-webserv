#include "server.hpp"

/*
  Decide the result of the request based on data in Root and Server
*/
void resolve(Client& client, Server& server) {
  (void)client;
  (void)server;
}

/*
  Based on client.getResponse() build the final string
*/
void build(Client& client) {
  const char* resp = "HTTP/1.1 200 OK\r\nContent-Length: 2\r\n\r\nOK";
  client.appendResponse(resp);
}

HandleResult response_builder::process_response(Client& client,
                                                Server& server) {
  if (client.getResponseBuffer().empty()) {
    resolve(client, server);
    build(client);
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