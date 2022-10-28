/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MSG.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuber <ahuber@student.42lausanne.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:17:06 by ahuber            #+#    #+#             */
/*   Updated: 2022/10/28 13:49:02 by ahuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "client/ACommand.hpp"

class MSG : public ACommand
{
	public:
		MSG(Server *serv);
		MSG(MSG const& src);
		~MSG();
		int execute(Client &clicli, std::vector<std::string> args);
};
