/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 23:33:29 by bmangin           #+#    #+#             */
/*   Updated: 2022/10/30 23:36:56 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "client/ACommand.hpp"

class USER : public ACommand
{
	public:
		USER(Server *serv);
		USER(USER const& src);
		~USER();
		int		execute(Client &clicli, std::vector<std::string> args);
		void	descr(Client& clicli);
};

