/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:25:38 by bmangin           #+#    #+#             */
/*   Updated: 2022/04/11 15:48:22 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc/Server.hpp"

int main(int ac, char **av)
{
    (void)av;
    if (ac != 3)
        std::cerr << "error:" << std::endl << "Usage : ./ircserv <port> <password>" << std::endl;
    return 0;
}
