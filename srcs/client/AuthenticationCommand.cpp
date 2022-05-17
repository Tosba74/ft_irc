/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AuthenticationCommand.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:28:08 by emenella          #+#    #+#             */
/*   Updated: 2022/05/17 16:53:28 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/AuthenticationCommand.hpp"
#include "irc/Server.hpp"

AuthenticationCommand::AuthenticationCommand(Server *serv): ACommand(serv)
{
}

AuthenticationCommand::AuthenticationCommand(AuthenticationCommand const& src): ACommand(src)
{
}

AuthenticationCommand::~AuthenticationCommand()
{

}

int AuthenticationCommand::execute(Client &clicli, args_t::iterator begin, args_t::iterator end)
{
    (void)begin;
    (void)end;
    if (clicli.getNickname().empty())
    {
        clicli << "Usage: NICK <nickname>";
    }
    if (clicli.getPassword().empty())
    {
        clicli << "Usage: PASSWORD <password>";
    }
    if (clicli.getUsername().empty())
    {
        clicli << "Usage: USER <username>";
    }
    if (clicli.getNickname().empty() || clicli.getPassword().empty() || clicli.getUsername().empty())
    {
        return 0;
    }
    if (clicli.getPassword() == _serv->getPassword())
    {
        clicli.setRegister(true);
        return 1;
    }
    clicli.setRegister(false);
    return -1;
}
