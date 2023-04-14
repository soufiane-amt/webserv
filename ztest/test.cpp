#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <sys/stat.h>

std::string             get_last_modified(const std::string& filepath)
{
    struct stat result;
    if (stat(filepath.c_str(), &result) != 0) {
        return "";
    }
    std::time_t timestamp = result.st_mtime;
    std::stringstream last_modified;
    last_modified << std::put_time(std::gmtime(&timestamp), "%a, %d %b %Y %T GMT");
    return last_modified.str();
}
int main()
{
    std::string filepath = "../www/index.html";
    std::cout << get_last_modified(filepath) << std::endl;
}
//643962c4-cb

//Mon, 12 Sep 2022 17:13:19 GMT