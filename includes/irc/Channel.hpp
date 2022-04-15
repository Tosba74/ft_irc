/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:29:38 by bmangin           #+#    #+#             */
/*   Updated: 2022/04/14 22:23:10 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <vector>

class Client;

class Channel
{
	private:
		std::string				_name;
		std::vector<Client*>	_clients;
		
		
	public:
		Channel();
		Channel(std::string name);
		Channel(Channel const &src);
		Channel &operator=(Channel const &rhs);
		~Channel();
		
		//setters
		void setName(std::string name);
		
		//getters
		std::string				getName() const;
		std::vector<Client*>	getClients() const;
		
		//methods
		void addClient(Client &client);
		void removeClient(Client *client);
		void sendMessage(std::string message);
};

std::ostream &operator<<(std::ostream &o, Channel const &rhs);