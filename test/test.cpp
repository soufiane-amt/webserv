#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <sys/stat.h>

std::string generate_etag(const std::string& filepath)
{
    struct stat result;
    if (stat(filepath.c_str(), &result) != 0) {
        return "";
    }
    std::time_t timestamp = result.st_mtime;
    std::stringstream etag;
    etag << std::hex << timestamp << "-" << result.st_size;
    return "\"" + etag.str() + "\"";
}

int main()
{
    std::string filepath = "../www/index.html";
    std::cout << "ETag: " << generate_etag(filepath) << std::endl;
}
//643962c4-cb