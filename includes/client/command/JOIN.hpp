#pragma once
#include "client/AuthenticationCommand.hpp"

class JOIN : public AuthenticationCommand
{
    public:
        JOIN(Server *serv);
        JOIN(AuthenticationCommand const& src);
        ~JOIN();
        int execute(Client &clicli, args_t::iterator begin, args_t::iterator end);
};