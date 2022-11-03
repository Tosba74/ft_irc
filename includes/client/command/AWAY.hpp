/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AWAY.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:28:33 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/02 17:28:54 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "client/ACommand.hpp"

class AWAY : public ACommand
{
	public:
		AWAY(Server *serv);
		AWAY(AWAY const& src);
		~AWAY();
		int execute(Client &clicli, std::vector<std::string> args);
		void	descr(Client& clicli);
};