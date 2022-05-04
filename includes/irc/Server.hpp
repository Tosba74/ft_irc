/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:38:35 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/04 18:01:02 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include "socket/SocketServer.hpp"
#include "irc/Channel.hpp"
#include "client/Client.hpp"

class Client;
class Icommand;

class Server: public SocketServer
{
	private:
		std::string		_password;
		// std::map<std::string, Icommand> _commandes;
	public:
		Server(int port, std::string password);
		// Server(SocketServer const &src);
		// Server &operator=(SocketServer const &rhs);
		~Server() throw();

		std::string 	getPassword() const;

		void			setPassword(std::string password);

		void			onConnection(int connectionFd, sockaddr_in& address);
		void			onDisconnection(Connection& connection);
		void			onMessage(Connection& connection, std::string const& message);

		// ACommand 			parseMsg(Client &client, std::string const &message);
};