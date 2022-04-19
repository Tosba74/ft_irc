/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:38:35 by bmangin           #+#    #+#             */
/*   Updated: 2022/04/19 23:38:36 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "socket/SocketServer.hpp"
#include "irc/Channel.hpp"
#include "client/Client.hpp"

class Server: public SocketServer
{
	private:
		std::string		_password;
	public:
		Server(int port, std::string password);
		Server(SocketServer const &src);
		Server &operator=(SocketServer const &rhs);
		~Server() throw();

		std::string 	getPassword() const;

		void			setPassword(std::string password);

		Connection*		onConnection(int connectionFd, sockaddr_in& address);
		void			onDisconnection(Connection* connection);
		void			onMessage(Connection* connection, std::string const& message);
};