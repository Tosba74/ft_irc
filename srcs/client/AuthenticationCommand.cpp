#include "client/AuthenticationCommand.hpp"

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
        clicli << "Usage: NICK <nickname>\n";
    }
    if (clicli.getPassword().empty())
    {
        clicli << "Usage: PASSWORD <password>\n";
    }
    if (clicli.getUsername().empty())
    {
        clicli << "Usage: USER <username>\n";
    }
    if (clicli.getNickname().empty() || clicli.getPassword().empty() || clicli.getUsername().empty())
    {
        return 0;
    }
    if (clicli.getPassword() == _serv->getPassword())
        return 1;
    return -1;
}
