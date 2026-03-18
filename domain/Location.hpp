#ifndef LOCATION
#define LOCATION

#include <map>
#include <string>
#include <vector>

enum HttpMethod { GET, POST, DELETE };

class Location {
 private:
  Location();
  const std::string _path;
  std::vector<HttpMethod> _methods;

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

 public:
  Location(const std::string& path);
  Location(const Location& other);
  Location& operator=(const Location& other);
  ~Location();

  // Getters
  const std::string& getPath() const;
  const std::vector<HttpMethod>& getMethods() const;
  const std::string& getRoot() const;
  const std::vector<std::string>& getIndex() const;
  bool getAutoindex() const;
  int getRedirectCode() const;
  const std::string& getRedirectUrl() const;
  bool getUpload() const;
  const std::string& getUploadStoreUrl() const;
  const std::map<std::string, std::string>& getCgiPass() const;

  // Setters
  void setAutoindex(bool autoindex);
  void setRedirectCode(int redirect_code);
  void setRedirectUrl(const std::string& redirect_url);
  void setUpload(bool upload);
  void setUploadStoreUrl(const std::string& upload_store_url);
  void setMethods(const std::vector<HttpMethod>& methods);
  void setRoot(const std::string& root);
};

#endif