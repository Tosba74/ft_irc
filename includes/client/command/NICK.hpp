/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:57:20 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/07 13:34:20 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "client/ACommand.hpp"
#include "client/Client.hpp"

class NICK : public ACommand
{
	public:
		NICK(Server *serv);
		NICK(NICK const& src);
		~NICK();
		int execute(Client &clicli, ACommand::args_t::iterator begin, ACommand::args_t::iterator end);
};