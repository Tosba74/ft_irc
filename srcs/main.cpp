/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:25:38 by bmangin           #+#    #+#             */
/*   Updated: 2022/10/19 13:40:57 by bmangin          ###   ########lyon.fr   */
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
        std::cout << "go start" << std::endl;
        server.start();
        std::cout << "pas la !" << std::endl;
    } catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}



