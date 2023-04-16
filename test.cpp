#include <string>
#include <cstring>
#include <iostream>

bool is_cgi_url(const std::string& url) {
  // Check if the URL starts with the "http://" or "https://" protocol
  if (url.compare(0, 7, "http://") == 0 || url.compare(0, 8, "https://") == 0) {
    // Look for the presence of a CGI script name in the URL's path
    const char* path = url.c_str() + (url.compare(0, 7, "http://") == 0 ? 7 : 8);
    if (std::strstr(path, "/cgi-bin/") != NULL || std::strstr(path, ".cgi") != NULL) {
      return true;
    }
  }
  // If the URL is not using CGI, return false
  return false;
}

int main() {
  std::string url1 = "http://example.com/cgi-bin/script.cgi";
  std::string url2 = "file:///home/user/scripts/script.cgi";

  if (is_cgi_url(url1)) {
    std::cout << "URL 1 is using CGI" << std::endl;
  } else {
    std::cout << "URL 1 is not using CGI" << std::endl;
  }

  if (is_cgi_url(url2)) {
    std::cout << "URL 2 is using CGI" << std::endl;
  } else {
    std::cout << "URL 2 is not using CGI" << std::endl;
  }

  return 0;
}