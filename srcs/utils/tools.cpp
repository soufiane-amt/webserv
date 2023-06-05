/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:54:19 by fech-cha          #+#    #+#             */
/*   Updated: 2023/06/05 16:14:04 by fech-cha         ###   ########.fr       */
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
