/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:47:23 by samajat           #+#    #+#             */
/*   Updated: 2023/03/23 13:05:42 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>

#include <iostream>
#include <sys/stat.h>
using namespace std;
  
int main()
{
    // Path to the directory
    const char* dir = "/Users/samajat/Desktop/webserv/test";
  
    // Structure which would store the metadata
    struct stat sb;
  
    // Calls the function with path as argument
    // If the file/directory exists at the path returns 0
    // If block executes if path exists
    if (stat(dir, &sb) == 0)
        cout << "The path is valid!";
    else
        cout << "The Path is invalid!";
  
    std::cout << S_ISDIR(sb.st_mode) << std::endl;
    return 0;
}
