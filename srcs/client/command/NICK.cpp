#include "client/command/NICK.hpp"

NICK::NICK(Server *serv) : ACommand(serv)
{

}

void NICK::execute(Client &clicli, std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end)
{
	if[begin != end]]
		clicli.setUsername(*(begin + 1));
	std::cout << "NICK: " << clicli.getUsername() << std::endl;	
}