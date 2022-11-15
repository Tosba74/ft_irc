/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:46:29 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/15 00:33:33 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "client/Client.hpp"

# define CHAN_PER_USER      100

# define MOD_CHAN_PRIVE     0b00000001
# define MOD_CHAN_SECRET    0b00000010
# define MOD_CHAN_VIP       0b00000100
# define MOD_CHAN_MODERE    0b00001000
# define MOD_CHAN_ONLYOP    0b00010000
# define MOD_CHAN_KEY       0b00100000
# define MOD_CHAN_EXTMSG    0b01000000
# define MOD_CHAN_MSGMOD    0b10000000

# define MOD_USER_INVIS     0b00000001
# define MOD_USER_SNOTIF    0b00000010
# define MOD_USER_WALLOP    0b00000100
# define MOD_USER_OP        0b00001000

class Server;

class ACommand {
    protected:
        Server *                _serv;
    public:

        ACommand(Server *serv);
        ACommand(ACommand const& src);
        virtual ~ACommand();
        
        ACommand& operator=(ACommand const& rhs);
        
        const Server *          getServ() const;
        virtual int             secureArgs(Client &clicli, std::vector<std::string> args) = 0;
        virtual int             execute(Client& clicli, std::vector<std::string> args) = 0;
        virtual void            descr(Client& clicli) = 0;
};


