/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:47:23 by samajat           #+#    #+#             */
/*   Updated: 2023/05/24 15:15:21 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <unistd.h>

int main() {
    char currentDir[FILENAME_MAX];

    if (getcwd(currentDir, sizeof(currentDir)) != nullptr) {
        std::cout << "Current working directory: " << currentDir << std::endl;
    } else {
        std::cerr << "Failed to get the current working directory." << std::endl;
        return 1;
    }

    return 0;
}
