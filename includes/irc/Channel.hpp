/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:32:08 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/26 16:44:20 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "client/Client.hpp"
#include <map>
#include <vector>

class Client;

class Channel {
	private:
		std::string						_name;
		std::string						_key;
		bool							_vip;
		unsigned long					_limit;
		std::map<int, Client&>			_clients;
		std::map<int, Client&>			_ban;
		std::vector<std::string>        _modo;
		
	protected:

	public:
		int								_mod;

		Channel(std::string name);
		Channel(Channel const &src);
		Channel &operator=(Channel const &rhs);
		~Channel();
		
		std::string	const&				getName() const;
		std::map<int, Client&> const&	getClients() const;
		std::map<int, Client&> const&	getBan() const;
		// std::string						getMode() const;
		std::string						getKey() const;
		unsigned int					getLimit() const;
		bool							getVip() const;
		std::string						getStringUser() const;
		
		void							setName(std::string name);
		void							setKey(std::string key);
		void							setLimit(unsigned long nb);
		void							addClient(Client& client);
		void							removeClient(Client& client);
		void							addBan(Client& client);
		void							removeBan(Client& client);
		bool							isBan(Client& client) const;
        void							addModo(std::string newModo);
		bool							isModo(std::string const& queried) const;
		void							removeModo(std::string modo);
		void							msgToUsers(std::string msg);
// Channel&						operator<<(Channel& chan, std::string const& msg);
		Channel &						operator<<(std::string const& reply);
};

std::ostream &						operator<<(std::ostream & o, Channel const &rhs);
// / std::ostream&                       operator<<(std::ostream& o, Channel const& rhs);
		// Channel&						operator<<(std::string const& msg);
// std::ostream&                       operator<<(std::ostream& o, Channel const& rhs);
