/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:32:08 by bmangin           #+#    #+#             */
/*   Updated: 2022/12/16 14:29:24 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/usr/include/sys/_types/_size_t.h"
#include "client/Client.hpp"
#include <map>
#include <vector>

class Client;

class Channel {
	private:
		std::string						_name;
		std::string						_key;
		std::string						_sujet;
		size_t							_limit;
		std::map<int, Client&>			_clients;
		std::map<int, Client&>			_modo;
		std::map<int, Client&>			_ban;
		std::map<int, Client&>			_vip;
		// std::vector<std::string>        _modo;
		
	public:
		int								_mod;

		Channel(std::string name);
		Channel(Channel const &src);
		Channel &operator=(Channel const &rhs);
		~Channel();
		
		std::string	const&				getName() const;
		std::string						getSujet() const;
		std::map<int, Client&> const&	getClients() const;
		std::map<int, Client&> const&	getModo() const;
		std::map<int, Client&> const&	getBan() const;
		std::map<int, Client&> const&	getVip() const;
		// std::string						getMode() const;
		std::string						getKey() const;
		size_t							getLimit() const;
		std::string const 				getStringUser() const;
		std::string const 				getStringBan() const;
		
		void							setName(std::string name);
		void							setSujet(std::string name);
		void							setKey(std::string key);
		void							setLimit(size_t nb);
		void							addClient(Client& client);
		void							removeClient(Client& client);
		void							addBan(Client& client);
		bool							isBan(Client& client) const;
		void							removeBan(Client& client);
		void							addModo(Client& client);
		bool							isModo(Client& client) const;
		void							removeModo(Client& client);
        // void							addModo(std::string modo);
		// bool							isModo(std::string const& name) const;
		// void							removeModo(std::string modo);
		void							addVip(Client& client);
		bool							isVip(Client& client) const;
		void							removeVip(Client& client);
		void							msgToUsers(Client& client, std::string msg);
// Channel&						operator<<(Channel& chan, std::string const& msg);
		Channel &						operator<<(std::string const& reply);
};

std::ostream &						operator<<(std::ostream & o, Channel const &rhs);
// / std::ostream&                       operator<<(std::ostream& o, Channel const& rhs);
		// Channel&						operator<<(std::string const& msg);
// std::ostream&                       operator<<(std::ostream& o, Channel const& rhs);
