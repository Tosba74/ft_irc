/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:25:38 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/11 17:26:02 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc/Server.hpp"
#include <cstdlib>

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    try
    {
        Server server(std::atoi(av[1]), av[2]);
        server.start();
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}



