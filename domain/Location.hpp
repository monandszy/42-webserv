#ifndef LOCATION
#define LOCATION

#include <string>
#include <vector>
#include <map>

class Location {
private:
  std::string _path;
  // methods (add enum)
  std::vector<std::string> _accept;

  std::string _root;

  // url
  std::vector<std::string> _index;
      
  bool _autoindex;

  int _redirect_code;
  std::string _redirect_url;

  bool _upload;
  std::string _upload_store_url;

  // extension, url
  std::map<std::string, std::string> _cgi_pass;

  Location();
};

#endif