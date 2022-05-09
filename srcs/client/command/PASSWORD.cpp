#include "client/command/PASSWORD.hpp"

PASSWORD::PASSWORD(Server *serv) : ACommand(serv)
{

}

PASSWORD::PASSWORD(PASSWORD const& src) : ACommand(src)
{
    if (this != &src)
    {
        this->_serv = src._serv;
    }
}

PASSWORD::~PASSWORD()
{
}

int PASSWORD::execute(Client &clicli, args_t::iterator begin, args_t::iterator end)
{
    std::size_t len = std::distance(begin, end);
    if (len < 2)
    {
        clicli << "Usage: PASSWORD <password>\n";
        return 0;
    }
    std::string pass = begin[1];
    clicli.setPassword(pass);
    return 0;
}