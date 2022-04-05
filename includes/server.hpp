/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 18:25:43 by bmangin           #+#    #+#             */
/*   Updated: 2022/04/04 20:09:25 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>

class Server
{
	private:
		int				_port;
		std::string		_pass;
		
		Server(const Server & rhs);
		Server();
		
		Server operator=(const Server & rhs);
		
	public:
		Server(int port, std::string password);
		~Server();
		
		int				getPort(void);
		std::string		getPass(void);
};