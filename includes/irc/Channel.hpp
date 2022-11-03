/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:32:08 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/03 02:36:24 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "client/Client.hpp"
#include <map>

class Client;

class Channel {
	private:
		std::string						_name;
		std::map<int, Client&>			_clients;
		
	public:
		Channel(std::string name);
		Channel(Channel const &src);
		Channel &operator=(Channel const &rhs);
		~Channel();
		
		std::string	const&				getName() const;
		std::map<int, Client&> const&	getClients() const;
		
		void							setName(std::string name);
		void							addClient(Client& client);
		void							removeClient(Client& client);
};

std::ostream&                       operator<<(std::ostream& o, Channel const& rhs);
