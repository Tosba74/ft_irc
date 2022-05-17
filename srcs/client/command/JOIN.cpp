/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:51 by emenella          #+#    #+#             */
/*   Updated: 2022/05/17 16:48:00 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/JOIN.hpp"
#include "irc/Server.hpp"

JOIN::JOIN(Server *serv): AuthenticationCommand(serv)
{

}

JOIN::JOIN(JOIN const& src): AuthenticationCommand(src)
{

}

JOIN::~JOIN()
{

}

int JOIN::execute(Client &clicli, args_t::iterator begin, args_t::iterator end)
{
    int ret = AuthenticationCommand::execute(clicli, begin, end);
    if (ret == 1)
    {
        _serv->createChannel(begin[1]);
        _serv->joinChannel(begin[1], clicli);
        
    }
    else
    {
        clicli << ERR_NOTREGISTERED;
    }
    return 0;
}
