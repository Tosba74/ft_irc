/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ME.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuber <ahuber@student.42lausanne.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:17:06 by ahuber            #+#    #+#             */
/*   Updated: 2022/10/31 11:21:43 by ahuber           ###   ########.fr       */
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
		int execute(Client &clicli, std::vector<std::string> args);
};
