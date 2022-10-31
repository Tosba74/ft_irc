/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LIST.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuber <ahuber@student.42lausanne.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:17:06 by ahuber            #+#    #+#             */
/*   Updated: 2022/10/31 11:11:26 by ahuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "client/ACommand.hpp"

class LIST : public ACommand
{
	public:
		LIST(Server *serv);
		LIST(LIST const& src);
		~LIST();
		int execute(Client &clicli, std::vector<std::string> args);
};
