/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:32:08 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/19 14:54:47 by bmangin          ###   ########lyon.fr   */
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
		std::vector<std::string>                _modo;
		
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
		
		void							setName(std::string name);
		void							setKey(std::string key);
		void							setLimit(unsigned long nb);
		void							addClient(Client& client);
		void							removeClient(Client& client, std::map<int, Client&> lst);
                void                                                    addModo(std::string newModo);
                bool                                                    isModo(std::string queried);
		void                                                    msgToUsers(std::string msg);
// Channel&						operator<<(Channel& chan, std::string const& msg);
};

		// Channel&						operator<<(std::string const& msg);
// std::ostream&                       operator<<(std::ostream& o, Channel const& rhs);
