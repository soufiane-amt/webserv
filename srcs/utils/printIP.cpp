/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printIP.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fech-cha <fech-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:46:08 by fech-cha          #+#    #+#             */
/*   Updated: 2023/05/29 18:34:39 by fech-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <arpa/inet.h>
#include <stdio.h>
# define INET_ADDRSTRLEN 5000

int main()
{
    struct sockaddr_in sa; 

    //from printable to binary
    inet_pton(AF_INET, "10.12.110.57", &(sa.sin_addr));

    //from binary to printable
    char ip_address[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(sa.sin_addr), ip_address, INET_ADDRSTRLEN);

    printf("%s\n", ip_address);

    return (0);
}

  