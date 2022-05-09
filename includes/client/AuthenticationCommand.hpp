#pragma once
#include "client/ACommand.hpp"
#include "client/Client.hpp"
#include "irc/Server.hpp"

class AuthenticationCommand : public ACommand
{
    public:
        AuthenticationCommand(Server *serv);
        AuthenticationCommand(AuthenticationCommand const& src);
        virtual ~AuthenticationCommand();
        virtual int execute(Client &clicli, args_t::iterator begin, args_t::iterator end);
};