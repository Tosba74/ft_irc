/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:25:35 by bmangin           #+#    #+#             */
/*   Updated: 2022/04/08 18:23:26 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port, std::string ip): port(port), ip(ip)
{
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1)
		throw std::runtime_error("socket() failed");
	server_in.sin_family = AF_INET;
	server_in.sin_port = htons(port);
	server_in.sin_addr.s_addr = inet_addr(ip.c_str());
	if (bind(server_fd, (struct sockaddr *)&server_in, sizeof(server_in)) == -1)
		throw std::runtime_error("bind() failed");
	if (listen(server_fd, 42) == -1)
		throw std::runtime_error("listen() failed");
}

Server::Server(int port, std::string ip, std::string password): port(port), ip(ip), password(password)
{
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1)
		throw std::runtime_error("socket() failed");
	server_in.sin_family = AF_INET;
	server_in.sin_port = htons(port);
	server_in.sin_addr.s_addr = inet_addr(ip.c_str());
	if (bind(server_fd, (struct sockaddr *)&server_in, sizeof(server_in)) == -1)
		throw std::runtime_error("bind() failed");
	if (listen(server_fd, 42) == -1)
		throw std::runtime_error("listen() failed");
}

Server::Server(): port(6665), ip("127.0.0.1")
{
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd == -1)
		throw std::runtime_error("socket() failed");
	server_in.sin_family = AF_INET;
	server_in.sin_port = htons(port);
	server_in.sin_addr.s_addr = inet_addr(ip.c_str());
	if (bind(server_fd, (struct sockaddr *)&server_in, sizeof(server_in)) == -1)
		throw std::runtime_error("bind() failed");
	if (listen(server_fd, 42) == -1)
		throw std::runtime_error("listen() failed");
}

Server::Server(Server const &src)
{
	//copy attributes
	if (this != &src)
	{
		port = src.port;
		ip = src.ip;
		password = src.password;
		server_fd = src.server_fd;
		server_in = src.server_in;
	}
	
}

Server& Server::operator=(Server const &rhs)
{
	port = rhs.port;
	ip = rhs.ip;
	server_fd = rhs.server_fd;
	server_in = rhs.server_in;
	return (*this);
}

Server::~Server()
{
	close(server_fd);
}

int Server::loop()
{
	while(1)
	{
		Client *client = new Client(server_fd);
		if (client == NULL && client->getFd() == -1)
			throw std::runtime_error("new Client() failed");
		clients.push_back(client);
	}
	
}
