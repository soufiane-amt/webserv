/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 06:04:33 by fech-cha          #+#    #+#             */
/*   Updated: 2023/03/30 07:17:29 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

void setAsNonBlocking(int descriptor) {
fcntl(descriptor, F_SETFL, fcntl(descriptor, F_GETFL) | O_NONBLOCK); // preserve other set flags
}

void setAsBlocking(int descriptor) {
fcntl(descriptor, F_SETFL, fcntl(descriptor, F_GETFL) & ~O_NONBLOCK); // suppress blocking bit, preserve others
}

bool isBlocking(int descriptor) {
return (fcntl(descriptor, F_GETFL) & O_NONBLOCK) == 0;
}

bool isNonBlocking(int descriptor) {
return !isBlocking(descriptor);
}