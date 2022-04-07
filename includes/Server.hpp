/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:25:43 by bmangin           #+#    #+#             */
/*   Updated: 2022/04/07 15:16:42 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


class Server
{
	private:
		int				port;
		std::string		ip;
		std::string 	password;
		int				sock;
		int 			*clients;
		int 			nb_client;
		int 			max_client;
		struct sockaddr_in server_in;
		struct sockaddr_in client_in;
		char			buffer[1024];
		
		
	public:
		Server(int port, std::string ip);
		Server(int port, std::string ip, std::string password);
		Server();
		Server(Server const &src);
		Server &operator=(Server const &rhs);
		~Server();
};