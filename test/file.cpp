/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 12:47:23 by samajat           #+#    #+#             */
/*   Updated: 2023/03/23 17:53:33 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include<fstream>
int main()
{
    std::ifstream file("test/file.cpp");
    std::string line;

    if (file.is_open())
    {
        while (getline(file, line))
             line + "\n";
        file.close();
    }

    return 0;
}
