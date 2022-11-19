/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:38:35 by bmangin           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/18 10:07:49 by bmangin          ###   ########lyon.fr   */
=======
/*   Updated: 2022/11/18 14:34:08 by bmangin          ###   ########lyon.fr   */
>>>>>>> origin/privmsg
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <vector>
#include <string>
#include "socket/SocketServer.hpp"
#include "irc/Channel.hpp"
#include "client/Client.hpp"
#include "client/command/NICK.hpp"
#include "client/command/PASS.hpp"
#include "client/command/USER.hpp"
#include "client/command/JOIN.hpp"
#include "client/command/LIST.hpp"
#include "client/command/MODE.hpp"
#include "client/command/OPER.hpp"
#include "client/command/AWAY.hpp"
#include "client/command/PRIVMSG.hpp"
#include "client/command/ME.hpp"

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