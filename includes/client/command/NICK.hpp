/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:57:20 by bmangin           #+#    #+#             */
/*   Updated: 2022/10/24 15:37:50 by ahuber           ###   ########.fr       */
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
		int execute(Client &clicli, ACommand::args_t::iterator begin, ACommand::args_t::iterator end);
};
