/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:38:35 by bmangin           #+#    #+#             */
/*   Updated: 2022/12/07 16:54:13 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <vector>
#include <string>
#include "socket/SocketServer.hpp"
#include "irc/Channel.hpp"
#include "client/Client.hpp"

class ACommand;
class Channel;

class Server: public SocketServer
{
	public:
		typedef std::map<std::string, ACommand*>	CommandMap;
		typedef std::map<std::string, Channel*>		ChannelMap;

	private:
		std::string				_password;
		CommandMap 				_commandes;

	public:
		ChannelMap 				_channels;
		
	public:
		Server(int port, std::string password);
		// Server(SocketServer const &src);
		// Server &operator=(SocketServer const &rhs);
		~Server() throw();

		std::string 			getPassword() const;
		Client*					getClient(const std::string& name) const;
		Channel*				getChannel(const std::string& name) const;
		void					setPassword(std::string password);

		void					onConnection(int connectionFd, sockaddr_in& address);
		void					onDisconnection(Connection& connection);
		void					onMessage(Connection& connection, std::string const& message);

		void 					parseCommand(std::string const &message, Client& client);
		int 					createChannel(std::string const &name);
		int 					joinChannel(std::string const &name, Client& client);
		int 					leaveChannel(std::string const &name, Client& client);
		
		bool					isAuthenticate(Client& client);
};

std::ostream&			operator<<(std::ostream& o, Server const& rhs);

