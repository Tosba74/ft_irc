/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:24 by emenella          #+#    #+#             */
/*   Updated: 2022/11/15 02:15:12 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "client/ACommand.hpp"
#include "irc/Channel.hpp"

class PING : public ACommand
{
    public:
        PING(Server *serv);
        PING(PING const& src);
        ~PING();
        int     secureArgs(Client &clicli, std::vector<std::string> args);
        int     execute(Client &clicli, std::vector<std::string> args);
		void	descr(Client& clicli);
};
