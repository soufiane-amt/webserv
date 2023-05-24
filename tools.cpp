/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:54:19 by fech-cha          #+#    #+#             */
/*   Updated: 2023/05/24 10:55:25 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <cstring>
#include <iostream>
#include <vector>

char** convert_vector_to_char_array(std::vector<std::string>& vec) 
{
    char** arr = new char*[vec.size() + 1];
    for (size_t i = 0; i < vec.size(); ++i) {
        arr[i] = new char[vec[i].size() + 1];
        std::strcpy(arr[i], vec[i].c_str());
    }
    arr[vec.size()] = NULL;
    return arr;
}

//avoid memory leaks
void freeConvertedArray(char** array, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        delete[] array[i];
    }
    delete[] array;
}

bool isCGIFile(const std::string& filename)
{
    std::string::size_type dotPos = filename.rfind('.');
    if (dotPos != std::string::npos)
    {
        std::string extension = filename.substr(dotPos + 1);
        // Compare the extension with CGI file extensions
        if (extension == "cgi" || extension == "php" || extension == "py")
        {
            return true;
        }
    }
    return false;
}

bool is_cgi_url(const std::string& url)
{
  // Check if the URL starts with the "http://" protocol
  if (url.compare(0, 7, "http://") == 0) {
    // Look for the presence of a CGI script name in the URL's path
    const char* path = url.c_str() + (url.compare(0, 7, "http://") == 0 ? 7 : 8);
    if (std::strstr(path, "/cgi-bin/") != NULL || std::strstr(path, ".cgi") != NULL) {
      return true;
    }
  }
  // If the URL is not using CGI, return false
  return false;
}

// int main() {
//   std::string url1 = "http://example.com/cgi-bin/script.cgi";
//   std::string url2 = "file:///home/user/scripts/script.cgi";

//   if (is_cgi_url(url1)) {
//     std::cout << "URL 1 is using CGI" << std::endl;
//   } else {
//     std::cout << "URL 1 is not using CGI" << std::endl;
//   }

//   if (is_cgi_url(url2)) {
//     std::cout << "URL 2 is using CGI" << std::endl;
//   } else {
//     std::cout << "URL 2 is not using CGI" << std::endl;
//   }

//   return 0;
// }