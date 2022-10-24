/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:57:20 by bmangin           #+#    #+#             */
/*   Updated: 2022/10/24 23:43:27 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "client/ACommand.hpp"

class NICK : public ACommand
{
	public:
		NICK(Server *serv);
		NICK(NICK const& src);
		~NICK();
		int execute(Client &clicli, std::vector<std::string> args);
};
