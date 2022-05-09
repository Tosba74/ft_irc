#include "client/command/JOIN.hpp"

JOIN::JOIN(Server *serv): AuthenticationCommand(serv)
{

}

JOIN::JOIN(AuthenticationCommand const& src) : AuthenticationCommand(src)
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
        //TODO: join channel
    }
    else
    {
        clicli << "You must be authenticated to join a channel\n";
    }
    return 0;
}
