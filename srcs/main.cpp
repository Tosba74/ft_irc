/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:25:38 by bmangin           #+#    #+#             */
/*   Updated: 2022/04/12 17:36:44 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket/SocketServer.hpp"

int main(int ac, char **av)
{
    (void)ac;
    SocketServer server(av[1], atoi(av[2]));
    server.start();
    return 0;
}
