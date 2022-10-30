/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MSGPRIV.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 21:13:41 by bmangin           #+#    #+#             */
/*   Updated: 2022/10/30 22:59:39 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "client/ACommand.hpp"

class MSGPRIV : public ACommand
{
	public:
		MSGPRIV(Server *serv);
		MSGPRIV(MSGPRIV const& src);
		~MSGPRIV();
		int execute(Client &clicli, std::vector<std::string> args);
		void	descr(Client& clicli);
};