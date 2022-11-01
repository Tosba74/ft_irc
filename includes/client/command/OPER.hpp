/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OPER.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:46:34 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/01 10:49:38 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "client/ACommand.hpp"

class Server;

class OPER : public ACommand {
	public:
		OPER(Server *serv);
		OPER(OPER const& src);
		~OPER();
		int		execute(Client &clicli, std::vector<std::string> args);
		void	descr(Client& clicli);
};