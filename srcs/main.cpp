/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:25:38 by bmangin           #+#    #+#             */
/*   Updated: 2022/04/04 20:14:53 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

Server    check_arg(char **av)
{
    if (av[1].isdigit())
    {
        std::cout << "Port: OK!"<< std::endl;
    }
    std::cout << av[1] << av[2] << std::endl;
}
int main(int ac, char **av)
{
    if (ac != 3)
        std::cerr << "error:" << std::endl << "Usage : ./ircserv <port> <password>" << std::endl;
    else
        check_arg(av);
    return 0;
}
