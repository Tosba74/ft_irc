/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ME.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:26:20 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/15 00:35:01 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "client/ACommand.hpp"

class ME : public ACommand
{
	public:
		ME(Server *serv);
		ME(ME const& src);
		~ME();
        int     secureArgs(Client &clicli, std::vector<std::string> args);
		int execute(Client &clicli, std::vector<std::string> args);
		void	descr(Client& clicli);
};