/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:25:35 by bmangin           #+#    #+#             */
/*   Updated: 2022/04/07 16:34:42 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port, std::string ip): port(port), ip(ip)
{
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		throw std::runtime_error("socket() failed");
	server_in.sin_family = AF_INET;
	server_in.sin_port = htons(port);
	server_in.sin_addr.s_addr = inet_addr(ip.c_str());
	if (bind(sock, (struct sockaddr *)&server_in, sizeof(server_in)) == -1)
		throw std::runtime_error("bind() failed");
	if (listen(sock, 42) == -1)
		throw std::runtime_error("listen() failed");
}

Server::Server(int port, std::string ip, std::string password): port(port), ip(ip), password(password)
{
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		throw std::runtime_error("socket() failed");
	server_in.sin_family = AF_INET;
	server_in.sin_port = htons(port);
	server_in.sin_addr.s_addr = inet_addr(ip.c_str());
	if (bind(sock, (struct sockaddr *)&server_in, sizeof(server_in)) == -1)
		throw std::runtime_error("bind() failed");
	if (listen(sock, 42) == -1)
		throw std::runtime_error("listen() failed");
}

Server::Server(): port(6665), ip("127.0.0.1")
{
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
		throw std::runtime_error("socket() failed");
	server_in.sin_family = AF_INET;
	server_in.sin_port = htons(port);
	server_in.sin_addr.s_addr = inet_addr(ip.c_str());
	if (bind(sock, (struct sockaddr *)&server_in, sizeof(server_in)) == -1)
		throw std::runtime_error("bind() failed");
	if (listen(sock, 42) == -1)
		throw std::runtime_error("listen() failed");
}

Server::Server(Server const &src)
{
	//copy attributes
	if (this != &src)
	{
		port = src.port;
		ip = src.ip;
		sock = src.sock;
		server_in = src.server_in;
		client_in = src.client_in;
		nb_client = src.nb_client;
		max_client = src.max_client;
		clients = new int[max_client];
		for (int i = 0; i < nb_client; i++)
			clients[i] = src.clients[i];
	}
	
}

Server& Server::operator=(Server const &rhs)
{
	port = rhs.port;
	ip = rhs.ip;
	sock = rhs.sock;
	server_in = rhs.server_in;
	client_in = rhs.client_in;
	nb_client = rhs.nb_client;
	max_client = rhs.max_client;
	delete[] clients;
	clients = new int[max_client];
	for (int i = 0; i < nb_client; i++)
		clients[i] = rhs.clients[i];
	return (*this);
}

Server::~Server()
{
	close(sock);
	delete[] clients;
}
