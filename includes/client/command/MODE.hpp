/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 01:51:52 by bmangin           #+#    #+#             */
/*   Updated: 2022/10/31 02:04:20 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/ACommand.hpp"
#pragma once

class MODE : public ACommand {
	public:
		MODE(Server *serv);
		MODE(MODE const& src);
		~MODE();
		int		execute(Client &clicli, std::vector<std::string> args);
		void	descr(Client& clicli);
};

