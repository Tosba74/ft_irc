/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LIST.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:24 by emenella          #+#    #+#             */
/*   Updated: 2022/10/31 02:08:14 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "client/ACommand.hpp"
#include "irc/Channel.hpp"

class LIST : public ACommand
{
    public:
        LIST(Server *serv);
        LIST(LIST const& src);
        ~LIST();
        int     execute(Client &clicli, std::vector<std::string> args);
		void	descr(Client& clicli);
};
