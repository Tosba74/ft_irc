/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:25:35 by bmangin           #+#    #+#             */
/*   Updated: 2022/04/04 20:11:32 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

Server::Server(){};
Server::Server(int port, std::string password) : _port(port), _pass(password)
{
	std::cout << "Server created" << std::endl;
}
Server::Server(const Server & rhs)
{
	*this = rhs;
}
Server::~Server()
{
	std::cout << "Server destroyed" << std::endl;
}


int				Server::getPort(void)
{
	return this->_port;
}
std::string		Server::getPass(void)
{	
	return this->_pass;
}