/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AuthenticationCommand.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:36 by emenella          #+#    #+#             */
/*   Updated: 2022/05/10 17:26:38 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "client/ACommand.hpp"

class Server;

class AuthenticationCommand : public ACommand
{
    public:
        AuthenticationCommand(Server *serv);
        AuthenticationCommand(AuthenticationCommand const& src);
        virtual ~AuthenticationCommand();
        virtual int execute(Client &clicli, args_t::iterator begin, args_t::iterator end);
};