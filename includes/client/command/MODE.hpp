/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 01:51:52 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/01 10:46:23 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "client/ACommand.hpp"

class MODE : public ACommand {
	public:
		MODE(Server *serv);
		MODE(MODE const& src);
		~MODE();
		int		execute(Client &clicli, std::vector<std::string> args);
		void	descr(Client& clicli);
};

