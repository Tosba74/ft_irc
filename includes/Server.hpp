/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:25:43 by bmangin           #+#    #+#             */
/*   Updated: 2022/04/08 18:23:19 by emenella         ###   ########.fr       */
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

#include "Client.hpp"


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