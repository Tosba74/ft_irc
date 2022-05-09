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
    // TODO
}


