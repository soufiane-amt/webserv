/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:47:23 by samajat           #+#    #+#             */
/*   Updated: 2023/05/25 14:15:16 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <dirent.h>

void listFiles(const std::string& directoryPath) {
    DIR* dir = opendir(directoryPath.c_str());
    if (dir) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            if (entry->d_type == DT_REG) {
                std::cout << entry->d_name << std::endl;
            }
        }
        closedir(dir);
    } else {
        std::cerr << "Failed to open directory: " << directoryPath << std::endl;
    }
}

int main() {
    std::string directoryPath = "./www/random/";
    listFiles(directoryPath);

    return 0;
}
