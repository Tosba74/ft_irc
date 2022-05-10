/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:28:02 by emenella          #+#    #+#             */
/*   Updated: 2022/05/10 18:26:05 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/USER.hpp"


USER::USER(Server *serv): ACommand(serv)
{

}


USER::USER(USER const& src): ACommand(src)
{

}


USER::~USER()
{

}


int USER::execute(Client &clicli, args_t::iterator begin, args_t::iterator end)
{
    if (std::distance(begin, end) != 5)
    {
        clicli << "Usage: USER <username> <hostname> <servername> <realname>\n";
        return 0;
    }
    else
    {
        clicli.setUsername(begin[1]);
        clicli.setHostname(begin[2]);
        clicli.setServerName(begin[3]);
        clicli.setRealName(begin[4]);
    }
    return 1;
}


