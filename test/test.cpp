#include <iostream>
#include <string>
#include <vector>


std::vector<std::string> split(std::string str, std::string delimiter) {
}


std::vector<std::string> ftsplit(std::string str, std::string delimiter)
{
        std::vector<std::string> tokens;
        size_t pos = 0;
        std::string token;
        // str = trim (str, delimiter);
        while ((pos = str.find(delimiter)) != std::string::npos) 
        {
            token = str.substr(0, pos);
            if (token.empty() == false)
                tokens.push_back(token);
            str.erase(0, pos + delimiter.length());
            while (str.length() >= delimiter.length() && ( str.substr(0, delimiter.length())) == delimiter)
                str.erase(0, delimiter.length());
        }
        if (token.empty() == false)
            tokens.push_back(str);
        return tokens;
}

int main ()
{
    std::vector<std::string> v = split("        f ", " ");
    for (size_t i = 0; i < v.size(); i++)
        std::cout << v[i] << std::endl;    
}