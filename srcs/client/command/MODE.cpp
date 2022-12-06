/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 01:51:55 by bmangin           #+#    #+#             */
/*   Updated: 2022/12/06 11:58:43 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/MODE.hpp"
#include "irc/Server.hpp"
#include <cstdlib>
#include <memory>
#include <vector>
// #include <ios>

// Commande: MODE <canal> {[+|-]|o|p|s|i|t|n|b|v} [<limite>] [<utilisateur>] [<masque de bannissement >]

// REPLY :
	// clicli << RPL_CHANNELMODEIS(args[1], clicli.getMode(), args[5]);
	// clicli << ERR_CHANOPRIVSNEEDED(args[1]);
	// clicli << RPL_BANLIST(args[1], args[5]);
	// clicli << RPL_ENDOFBANLIST(args[1]);
	// clicli << ERR_KEYSET(args[1]);
	// clicli << ERR_USERSDONTMATCH();
	// clicli << RPL_UMODEIS(clicli.getMode());
	// clicli << ERR_NOSUCHNICK(args[4]);
	// clicli << ERR_UMODEUNKNOWNFLAG();
	
	// clicli << ERR_UNKNOWNMODE(char);

// Les modes disponibles pour les canaux sont les suivants :
	// o - donne/retire les privilèges d'opérateur de canal
	// p - drapeau de canal privé
	// s - drapeau de canal secret
	// i - drapeau de canal accessible uniquement sur invitation
	// t - drapeau de sujet de canal modifiable uniquement par les opérateurs
	// n - pas de messages dans un canal provenant de clients à l'extérieur du canal
	// m - canal modéré
	// l - définit le nombre maximal de personnes dans un canal
	// b - définit un masque de bannissement pour interdire l'accès à des utilisateurs
	// v - donne/retire la possibilité de parler dans un canal modéré
	// k - définit la clé du canal (mot de passe)

// Les modes disponibles sont :
	// i - marque un utilisateur comme invisible ;
	// s - marque un utilisateur comme recevant les notifications du serveur ;
	// w - l'utilisateur reçoit les WALLOPs ;
	// o - drapeau d'opérateur.

MODE::MODE(Server *serv) : ACommand(serv) {}

MODE::MODE(MODE const& src) : ACommand(src) {
    if (this != &src)
        this->_serv = src._serv;
}

MODE::~MODE() {}

// REPLY :
	// clicli << ERR_CHANOPRIVSNEEDED(args[1]);
	// clicli << ERR_KEYSET(args[1]);
	// clicli << ERR_USERSDONTMATCH();
	// clicli << ERR_UMODEUNKNOWNFLAG();
	
	// clicli << RPL_CHANNELMODEIS(args[1], clicli.getMode(), args[5]);
	// clicli << RPL_UMODEIS(clicli.getMode());
	// clicli << RPL_ENDOFBANLIST(args[1]);
	// clicli << RPL_BANLIST(args[1], args[5]);
	// clicli << ERR_UNKNOWNMODE(char);
	// clicli << ERR_NOSUCHNICK(args[4]);
	
int		MODE::indexage(char c, const char *ismode) {
	int i = -1;
	
	while (ismode[++i])
		if (ismode[i] == c)
			return i;
	return -1;
}

// int		MODE::checkChannel(Client &clicli, std::string arg) {
// 	if ((arg[0] != '#' && arg[0] != '&') || !_serv->getChannel(arg)) {
// 		clicli << ERR_NOSUCHCHANNEL(arg);
// 		return 1;
// 	// } else if (!_serv->getChannel(clicli.getCurrchan()) || arg.compare(clicli.getCurrchan())) {
// 		// clicli << ERR_NOTONCHANNEL(arg);
// 		// return 1;
// 	}
// 	return 0;
// }

int		MODE::checkMode(Client &clicli, std::string arg, const char *cmp) {
	std::string::iterator it = arg.begin();
	
	// std::cout << "\e[33mArg: " << arg << " | cmp: " << cmp << "\e[0m" << std::endl;
	// std::cout << "\e[33mArg[0]:/e[0m ";
	
	if ((*it != '+' && *it != '-') || (arg.size() < 2 || arg.size() > 3)) {
		// std::cout << "\e[31mKO\e[0m" << std::endl;
		clicli << ERR_UMODEUNKNOWNFLAG();
		return 1;
	}
	// std::cout << "\e[32mOK\e[0m" << std::endl;
	++it; 
	for (; it != arg.end(); ++it) {
		std::cout << *it << std::endl;
		if (indexage(*it, cmp) == -1) {
			clicli << ERR_UMODEUNKNOWNFLAG();
			return 1;
		}
	}
	return 0;
}

int		MODE::checkClient(Client &clicli, std::string client) {
	if (!_serv->getClient(client)) {
		clicli << ERR_NOSUCHNICK(client);
		return 1;
	}
	return 0;
}

bool	MODE::passNoGood(std::string pass) {
	if (pass.size() > 512 || pass.size() < 2)
		return false;	
	std::string::iterator it = pass.begin();
	for (; it != pass.end(); ++it) {
		if (*it == ' ' || *it == '#' || *it == '&' || *it == '\t' || *it == '\r' || *it == '\n')
			return false;
	}
	return true;
}

int     MODE::secureArgs(Client &clicli, std::vector<std::string> args) {
	if (args.size() < 2) {
		clicli << ERR_NEEDMOREPARAMS(args[0]);
		return 1;
	}
	return 0;
}
int		MODE::execute(Client &clicli, std::vector<std::string> args) {
	if (secureArgs(clicli, args))
		return 1;
	if (args.size() == 2)
		return 0;
		
	// if (!checkChannel(clicli, args[1]) && !checkMode(clicli, args[2],  "psimtknvlob")) {
	if ((args[1][0] == '#' || args[1][0] == '&') && !checkMode(clicli, args[2],  "psimtknvlob")) {
		std::cout << "MODEChannel checkmode:";
		if (checkChannel(clicli, args[1]))
			return 1;
		// Channel	*chan = _serv->getChannel(args[1]);
		std::string::iterator it = args[2].begin() + 1;
		
		for (; it != args[2].end(); it++) {
			int		idx = indexage(*it, "psimtknvlob");
			std::cout << "\e[32mGUT!\e[0m" << std::endl << "Execute: ";
			std::cout << "indexage = " << idx << std::endl;
			if (idx < 8) {
				// if (args[2][0] == '+') {
					_serv->getChannel(args[1])->_mod ^= (1 << idx);
				// } else if (args[2][0] == '-') {
					// _serv->getChannel(args[1])->_mod |= (1 << idx);
				// }

			}
			if (idx > 4) {
				if (args.size() == 3) {
					clicli << ERR_NEEDMOREPARAMS(args[0]);
					return 1;
				}
				if (idx != 8) {
					if (!_serv->getClient(args[3])) {
						clicli << ERR_NOSUCHNICK(args[3]);
						return 1;
					}
				}
			}
			if (idx == 6) {
				clicli << ERR_KEYSET(args[1]);
				if (clicli._mod & MOD_USER_OP)
					clicli << ERR_CHANOPRIVSNEEDED(args[1]);
				if (passNoGood(args[3]))
					return 1;
				if (args[2][0] == '+') {
					_serv->getChannel(args[1])->setKey(args[3]);
				} else if (args[2][0] == '-') {
					_serv->getChannel(args[1])->setKey("");
				}
				return 1;
			} else if (idx == 8) {
				if (std::strtoul(args[3].c_str(), NULL, 10))
					_serv->getChannel(args[1])->setLimit(std::strtoul(args[3].c_str(), NULL, 10));
				_serv->getChannel(args[1])->setLimit(std::strtoul(args[3].c_str(), NULL, 10));
			} else if (idx == 9) {
				if (args[2][0] == '+') {
					if (_serv->getClient(args[3])->isInChannel(args[1]) == false) {
						clicli << ERR_NOTONCHANNEL(args[1]);
						return 1;
					}
					_serv->getChannel(args[1])->addModo(args[1]);
				} else if (args[2][0] == '-') {
					if (_serv->getChannel(args[1])->isModo(args[3]))
						_serv->getChannel(args[1])->removeModo(args[3]);
				}
			} else if (idx == 10) {
				if (args[2][0] == '+') {
					if (clicli.isInChannel(args[1]) == false) {
						clicli << ERR_NOTONCHANNEL(args[1]);
						return 1;
					}
					_serv->getChannel(args[1])->addBan(*_serv->getClient(args[3]));
					_serv->getChannel(args[1])->removeClient(*_serv->getClient(args[3]));
					clicli << RPL_BANLIST(args[1], args[3]);
				} else if (args[2][0] == '-') {
					_serv->getChannel(args[1])->removeBan(*_serv->getClient(args[3]));
					clicli << RPL_ENDOFBANLIST(args[1]);
				}
			}
			// *_serv->getClient(args[3]) << RPL_UMODEIS(args[2]);
			// _serv->getClient(args[3]) << RPL_UMODEIS(args[2]);
			// << RPL_UMODEIS(args[2]);
			clicli << RPL_CHANNELMODEIS(args[1], args[2], *it);
		}
	} else if (!checkClient(clicli, args[1]) && !checkMode(clicli, args[2], "iswo")) {
		std::cout << "MODEClient checkmode:";
		Client					*client = _serv->getClient(args[1]);
		std::string::iterator	it = args[2].begin() + 1;

		std::cout << "\e[32mGUT!\e[0m" << std::endl << "Execute: ";
		for (; it != args[2].end(); ++it) {
			int		idx = indexage(*it, "iswo");
			// if (args[2][0] == '+') {
				client->_mod ^= (1 << idx);
			// } else if (args[2][0] == '-') {
				// client->_mod |= (1 << idx);
			// }
			*client << RPL_UMODEIS(args[2]);
		}
		std::cout << "\e[32mGUT!\e[0m(" << client->_mod << ")" << std::endl << "Execute: ";
	}
	// std::cout << "\e[32mGUT!\e[0m" << std::endl;
	return 0;
}
	
void	MODE::descr(Client& clicli) {
	clicli << "Usage: MODE <canal> {[+|-]|o|p|s|i|t|n|b|v} [<limite>] [<utilisateur>] [<masque de bannissement >]\n";
	clicli << "Usage: MODE <pseudonyme> {[+|-]|i|w|s|o}\n";
}
