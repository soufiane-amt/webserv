#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(std::string str, std::string delimiter)
{
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token = "";
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        if (!token.empty()) {
            tokens.push_back(token);
        }
        str.erase(0, pos + delimiter.length());
    }
    if (!str.empty()) {
        tokens.push_back(str);
    }
    return tokens;
}


bool isQueryString(const std::string& str) 
{
    if (str.empty())
        return false;

    if (str[0] != '?')
        return false;

    std::vector<std::string> parameters = split(str.substr(1), "&");

    for (std::vector<std::string>::const_iterator it = parameters.begin(); it != parameters.end(); ++it)
        if (it->empty() || it->find('=') == std::string::npos)
            return false;
    return true;
}

int main() {
    std::string queryString1 = "?key1=value1&key2=value2";
    std::string queryString2 = "?key1=value1&&key2=value2";
    std::string queryString3 = "?key1=value1&key2=";

    std::cout << queryString1 << " is query string: " << isQueryString(queryString1) << std::endl;
    std::cout << queryString2 << " is query string: " << isQueryString(queryString2) << std::endl;
    std::cout << queryString3 << " is query string: " << isQueryString(queryString3) << std::endl;

    return 0;
}
