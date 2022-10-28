/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:38:35 by bmangin           #+#    #+#             */
/*   Updated: 2022/10/28 13:53:09 by ahuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <string>
#include "socket/SocketServer.hpp"
#include "irc/Channel.hpp"
#include "client/Client.hpp"
#include "client/command/NICK.hpp"
#include "client/command/PASSWORD.hpp"
#include "client/command/JOIN.hpp"

class ACommand;
class Channel;

class Server: public SocketServer
{
	public:
		typedef std::map<std::string, ACommand*>	CommandMap;
		typedef std::map<std::string, Channel*>		ChannelMap;
		typedef std::map<std::string, Client*>		ClientAllMap;
	private:
		std::string		_password;
		CommandMap 		_commandes;
		ChannelMap 		_channels;
		ClientAllMap		_clientAll;
		
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

		void 			parseCommand(std::string const &message, Client& client);
		int 			createChannel(std::string const &name);
		int 			joinChannel(std::string const &name, Client& client);
		int 			leaveChannel(std::string const &name, Client& client);
};
