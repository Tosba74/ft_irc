/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AWAY.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuber <ahuber@student.42lausanne.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:17:06 by ahuber            #+#    #+#             */
/*   Updated: 2022/10/31 10:58:34 by ahuber           ###   ########.fr       */
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
};
