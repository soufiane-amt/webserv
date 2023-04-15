#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <sys/stat.h>

// std::string             get_last_modified(const std::string& filepath)
// {
//     struct stat result;
//     if (stat(filepath.c_str(), &result) != 0) {
//         return "";
//     }
//     std::time_t timestamp = result.st_mtime;
//     std::stringstream last_modified;
//     last_modified << std::put_time(std::gmtime(&timestamp), "%a, %d %b %Y %T GMT");
//     return last_modified.str();
// }
int main()
{
    std::string str = "hello hello";
    std::cout << str.find_last_of("hello") << std::endl;
}
//643962c4-cb

//Mon, 12 Sep 2022 17:13:19 GMT