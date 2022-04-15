/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:25:43 by bmangin           #+#    #+#             */
/*   Updated: 2022/04/15 11:29:29 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "user/Client.hpp"


class Server
{
	private:
		int						port;
		std::string				ip;
		std::string 			password;
		int						server_fd;
		std::vector<Client*>	clients;
		struct sockaddr_in 		server_in;
		
		
	public:
		Server(int port, std::string ip);
		Server(int port, std::string ip, std::string password);
		Server();
		Server(Server const &src);
		Server &operator=(Server const &rhs);
		~Server();

		//setters
		void setPort(int port);
		void setIp(std::string ip);
		void setPassword(std::string password);
		
		//getters
		int getPort();
		std::string getIp();
		std::string getPassword();

		//methods
		int loop();
};