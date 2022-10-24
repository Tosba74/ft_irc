/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:25:38 by bmangin           #+#    #+#             */
/*   Updated: 2022/10/19 20:46:41 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "irc/Server.hpp"
#include <cstdlib>

int main(int ac, char **av) {
    (void)ac;
    (void)av;
    if (ac != 3) {
        std::cout << "Usage: ./ircserv [PORT] password" << std::endl << "ex: ./ircserv 6667 ****" << std::endl;
        return 1;
    }
    try {
        Server server(std::atoi(av[1]), av[2]);
        server.start();
    } catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}



