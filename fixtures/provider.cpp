#include "provider.hpp"

#include <vector>

Root createRootFixture() {
  Root root;
  root.setBodySize(1024);

  // First server
  Server server1("127.0.0.1", "8080", "first.com");
  server1.addErrorPage(404, "/404.html");
  server1.addErrorPage(500, "/50x.html");
  server1.addErrorPage(502, "/50x.html");
  server1.addErrorPage(503, "/50x.html");
  server1.addErrorPage(504, "/50x.html");

  Location loc1("/");
  loc1.addMethod(GET);
  loc1.addMethod(POST);
  loc1.setRoot("/data/www");
  loc1.addIndex("index.html");
  loc1.addIndex("index.htm");
  loc1.setAutoindex(false);
  server1.addLocation(loc1);

  Location loc2("/test");
  loc2.addMethod(GET);
  loc2.setRoot("/tmp/www");
  server1.addLocation(loc2);

  Location loc3("/redirection");
  loc3.setRedirectCode(301);
  loc3.setRedirectUrl("http://example.com/new-url");
  server1.addLocation(loc3);

  Location loc4("/upload");
  loc4.addMethod(GET);
  loc4.addMethod(POST);
  loc4.setRoot("/data/www/uploads");
  loc4.setUpload(true);
  loc4.setUploadStoreUrl("/data/www/uploads/files");
  server1.addLocation(loc4);

  Location loc5("/cgi-bin");
  loc5.addMethod(GET);
  loc5.addMethod(POST);
  loc5.setRoot("/data/www/cgi-bin");
  loc5.addCgiPass(".php", "/usr/bin/php-cgi");
  loc5.addCgiPass(".py", "/usr/bin/python3");
  server1.addLocation(loc5);

  root.addServer(server1);

  // Second server
  Server server2("127.0.0.1", "8081", "second.com");

  Location loc6("/");
  loc6.setRoot("/var/www/html");
  loc6.addMethod(GET);
  loc6.setAutoindex(true);
  server2.addLocation(loc6);

  root.addServer(server2);

  return root;
}
