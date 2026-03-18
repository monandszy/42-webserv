#include "Location.hpp"

Location::Location(const std::string& path)
    : _path(path), _autoindex(false), _redirect_code(0), _upload(false) {}

Location::Location(const Location& other) : _path(other._path) {
  *this = other;
}

Location& Location::operator=(const Location& other) {
  if (this != &other) {
    _methods = other._methods;
    _root = other._root;
    _index = other._index;
    _autoindex = other._autoindex;
    _redirect_code = other._redirect_code;
    _redirect_url = other._redirect_url;
    _upload = other._upload;
    _upload_store_url = other._upload_store_url;
    _cgi_pass = other._cgi_pass;
  }
  return *this;
}

Location::~Location() {}

const std::string& Location::getPath() const { return _path; }
const std::vector<HttpMethod>& Location::getMethods() const { return _methods; }
const std::string& Location::getRoot() const { return _root; }
const std::vector<std::string>& Location::getIndex() const { return _index; }
bool Location::getAutoindex() const { return _autoindex; }
int Location::getRedirectCode() const { return _redirect_code; }
const std::string& Location::getRedirectUrl() const { return _redirect_url; }
bool Location::getUpload() const { return _upload; }
const std::string& Location::getUploadStoreUrl() const {
  return _upload_store_url;
}
const std::map<std::string, std::string>& Location::getCgiPass() const {
  return _cgi_pass;
}

void Location::setAutoindex(bool autoindex) { _autoindex = autoindex; }
void Location::setRedirectCode(int redirect_code) {
  _redirect_code = redirect_code;
}
void Location::setRedirectUrl(const std::string& redirect_url) {
  _redirect_url = redirect_url;
}
void Location::setUpload(bool upload) { _upload = upload; }
void Location::setUploadStoreUrl(const std::string& upload_store_url) {
  _upload_store_url = upload_store_url;
}
void Location::setMethods(const std::vector<HttpMethod>& methods) {
  _methods = methods;
}
void Location::setRoot(const std::string& root) { _root = root; }
