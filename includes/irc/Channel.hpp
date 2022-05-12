/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 21:32:08 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/12 14:54:37 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "client/Client.hpp"
#include <map>

class Client;

class Channel
{
	typedef std::map<int, Client> clients_t;
	private:
		std::string					_name;
		clients_t					_clients;
		
	public:
		Channel(std::string name);
		Channel(Channel const &src);
		Channel &operator=(Channel const &rhs);
		~Channel();
		
		std::string	const				getName() const;
		clients_t::const_iterator		begin() const;
		clients_t::const_iterator		end() const;
		
		void							setName(std::string name);
		void							addClient(Client& client);
		void							removeClient(Client& client);
};

std::ostream&                       operator<<(std::ostream& o, Channel const& rhs);
