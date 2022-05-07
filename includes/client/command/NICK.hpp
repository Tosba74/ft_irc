#pragma once
#include "ACommand.hpp"

class ACommand;

class NICK : public ACommand
{
	public:
	NICK(Server *serv);
	~NICK();

	int execute(Client &clicli,args_t::iterator begin, args_t::iterator end);
};