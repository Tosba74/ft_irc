/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BAN.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:24 by emenella          #+#    #+#             */
/*   Updated: 2022/11/01 17:12:51 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "client/ACommand/BAN.hpp"
#include "irc/Channel.hpp"

class BAN : public ACommand
{
    public:
        BAN(Server *serv);
        BAN(BAN const& src);
        ~BAN();
        int     execute(Client &clicli, std::vector<std::string> args);
		void	descr(Client& clicli);
};
