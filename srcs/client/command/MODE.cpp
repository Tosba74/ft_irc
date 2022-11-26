/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 01:51:55 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/26 18:13:29 by bmangin          ###   ########lyon.fr   */
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
/*
int		MODE::checkMode(Client &clicli, std::string arg) {
	int i = 0;
	
	for (std::string::iterator it = arg.begin(); it != arg.end(); ++it) {
		if (i == 0 && !(*it == '+' || *it == '-')) {
			clicli << ERR_UMODEUNKNOWNFLAG();
			return 1;
		}
		// Commande: MODE <canal> {[+|-]|o|p|s|i|t|n|b|v} [<limite>] [<utilisateur>] [<masque de bannissement >]
		if (i > 0 && indexage(*it, "opsitnmlbv") == -1) {
			clicli << ERR_UNKNOWNMODE(arg.substr(i, 1));
			return 1;
		}
		// Commande: MODE <pseudonyme> {[+|-]|i|w|s|o}
		if (i > 0 && indexage(*it, "iswo") == -1) {
			clicli << ERR_UNKNOWNMODE(arg.substr(i, 1));
			return 1;
		}
		// Probleme JOIN set currrchan
		i++;
	}
	return 0;
}
*/

int		MODE::checkChannel(Client &clicli, std::string arg) {
	if (arg[0] != '#' || arg[0] != '&' || !_serv->getChannel(arg)) {
		clicli << ERR_NOSUCHCHANNEL(arg);
		return 1;
	// } else if (!_serv->getChannel(clicli.getCurrchan()) || arg.compare(clicli.getCurrchan())) {
		// clicli << ERR_NOTONCHANNEL(arg);
		// return 1;
	}
	return 0;
}

int		MODE::checkMode(Client &clicli, std::string arg, const char *cmp) {
	std::string::iterator it = arg.begin();
	if ((*it != '+' || *it != '-') || arg.size() < 2) {
		clicli << ERR_UMODEUNKNOWNFLAG();
		return 1;
	}
	++it; 
	for (; it != arg.end(); ++it) {
		std::cout << *it << std::endl;
		if (indexage(*it, cmp) == -1) {
			clicli << ERR_UMODEUNKNOWNFLAG();
			// clicli << ERR_USERSDONTMATCH();
			return 1;
		}
	}
	return 0;
}
// int		MODE::checkClient(Client &clicli, std::vector<std::string> client) {
	// for (std::vector<std::string>::iterator it = client.begin(); it != client.end(); ++it) {
		// if (!_serv->getClient(*it)) {
			// clicli << ERR_NOSUCHNICK(*it);
			// return 1;
		// }
	// }
	// return 0;
// }
int		MODE::checkClient(Client &clicli, std::string client) {
	if (!_serv->getClient(client)) {
		clicli << ERR_NOSUCHNICK(client);
		return 1;
	}
	return 0;
}
/*
int		MODE::secureArgs(Client &clicli, std::vector<std::string> args) {
    if (!splitArgs(args[1]).empty()) { 
    	clicli << ERR_NEEDMOREPARAMS(args[0]); // this->decr();
        return 1;
    } else {
    	std::vector<std::string> newargs = splitArgs(args[1]);
    	args.erase(newargs.begin() + 1);
    	args.insert(args.begin() + 1, newargs.begin(), newargs.end());
    }

	for (std::vector<std::string>::iterator it = args.begin(); it != args.end(); ++it)
		std::cout << " " << *it << std::endl;


	
	if (args[1][0] == '#' || args[1][0] == '&') {
		if (!_serv->getChannel(args[1])) {
			clicli << ERR_NOSUCHCHANNEL(args[1]);
			return 1;
		} else {
			if (args[1].compare(clicli.getCurrchan())) {
				clicli << ERR_NOTONCHANNEL(args[1]);
				return 1;
			} else {
				if (checkMode(clicli, args[2], "psimtknvlob") == -1)
					return 1;
				else
					return 0;
			}
		}
	} else {
		if (!_serv->getClient(args[1])) {
			clicli << ERR_NOSUCHNICK(args[1]);
			return 1;
		} else {
			if (checkMode(clicli, args[2], "iswo") == -1)
				return 1;
			else
				return 0;
		}
	}
	return 0;
}

int		MODE::execute(Client &clicli, std::vector<std::string> args) {
	// if (args.size() < 2) {
		// // clicli << ERR_NEEDMOREPARAMS(args[0]);
		// // return 1;
	// }
	int i = secureArgs(clicli, args);
	if (i == 1) {
		return 1;
	} else if (i == 1) {
		std::cout << "args[2] is a Client" << std::endl;
		Client		*dest = _serv->getClient(args[1]);
		std::string::iterator it = args[2].begin();
		++it; 
		for (; it != args[2].end(); ++it) {
			int		index = indexage(*it, "iswo") + 1;
			if (index < 4)
				dest->_mod ^= (1 << index);
		}
	} else {
		std::cout << args[2] << " is a Channel" << std::endl;
		Channel		*chan = _serv->getChannel(args[1]);
		std::string::iterator it = args[2].begin();
		++it; 
		for (; it != args[2].end(); ++it) {
			int		index = indexage(*it, "psimtknvlob") + 1;
			if (index < 8) {
				chan->_mod ^= (1 << index);
			} else if (index == 8) {
				std::cout << "size: " << args.size() << std::endl;
				if (args.size() == 3) {
					clicli << ERR_NEEDMOREPARAMS(args[0]);
					return 1;
				} else {
					if (std::strtoul(args[3].c_str(), NULL, 10) > 0)
						chan->setLimit(std::strtoul(args[3].c_str(), NULL, 10));
					// if (std::strtoul(args[3].c_str()) > 0)
						// chan->setLimit(std::strtoul(args[3].c_str()));
				}
			} else if (index == 9) {
				// clicli + o;
				;
			} else if (index == 10) {
				clicli << "HA WE SUPER\n";
				_serv->getChannel(args[1])->removeClient(*_serv->getClient(args[3]));	
				_serv->getChannel(args[1])->addBan(*_serv->getClient(args[3]));	
				// if (args.size() == 3) {
					// clicli << ERR_NEEDMOREPARAMS(args[0]);
					// return 1;
				// } else {
					// std::vector<std::string>::iterator it = args.begin();
					// ++it;
					// for (; it != args.end(); ++it) {
						// if (!_serv->getClient(*it)) {
							// clicli << ERR_NOSUCHNICK(*it);
							// return 1;
						// } else {
							// // ATTENTION A LA LISTE DE BAN ET PAS ADDCLIENT
							// // chan->addClient(*(_serv->getClient(*it)), chan->getBan());
							// chan->addClient(*(_serv->getClient(*it)));
						// }
					// }
				// }
			}
		}
	}
	return 0;
}
*/

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
	if (secureArgs(clicli, args)) {
		return 1;
	}
	if (args.size() == 2) {
		return 0;
	}
	if (!checkClient(clicli, args[1]) && !checkMode(clicli, args[2], "iswo")) {
		std::cout << "MODEClient checkmode:";
		Client					*client = _serv->getClient(args[1]);
		std::string::iterator	it = args[2].begin() + 1;

		std::cout << "\e[32mGUT!\e[0m" << std::endl << "Execute: ";
		for (; it != args[2].end(); ++it) {
			int		idx = indexage(*it, "iswo") + 1;
			if (args[2][0] == '+') {
				client->_mod ^= (1 << idx);
			} else if (args[2][0] == '-') {
				client->_mod |= (1 << idx);
			}
			*client << RPL_UMODEIS(args[2]);
		}
		std::cout << "\e[32mGUT!\e[0m(" << client->_mod << ")" << std::endl << "Execute: ";

		
	} else if (!checkChannel(clicli, args[1]) && !checkMode(clicli, args[2],  "psimtknvlob")) {
		std::cout << "MODEChannel checkmode:";
		if (!_serv->getChannel(args[1])) {
			clicli << ERR_NOSUCHCHANNEL(args[1]);
			return 1;
		}
		Channel	*chan = _serv->getChannel(args[1]);
		std::string::iterator it = args[2].begin() + 1;
		
		for (; it != args[2].end(); ++it) {
			int		idx = indexage(*it, "psimtknvlob") + 1;
			if (idx < 8)
				chan->_mod ^= (1 << idx);
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
			std::cout << "\e[32mGUT!\e[0m" << std::endl << "Execute: ";
			if (idx == 6) {
				clicli << ERR_KEYSET(args[1]);
				if (clicli._mod & MOD_USER_OP)
					clicli << ERR_CHANOPRIVSNEEDED(args[1]);
				if (passNoGood(args[3]))
					return 1;
				if (args[2][0] == '+') {
					chan->setKey(args[3]);
				} else if (args[2][0] == '-') {
					chan->setKey("");
				}
				return 1;
			} else if (idx == 8) {
				if (std::strtoul(args[3].c_str(), NULL, 10))
					chan->setLimit(std::strtoul(args[3].c_str(), NULL, 10));
				chan->setLimit(std::strtoul(args[3].c_str(), NULL, 10));
			} else if (idx == 9) {
				if (args[2][0] == '+') {
					if (_serv->getClient(args[3])->isInChannel(args[1]) == false) {
						clicli << ERR_NOTONCHANNEL(args[1]);
						return 1;
					}
					chan->addModo(args[1]);
				} else if (args[2][0] == '-') {
					if (chan->isModo(args[3]))
						chan->removeModo(args[3]);
				}
			} else if (idx == 10) {
				if (args[2][0] == '+') {
					if (_serv->getClient(args[3])->isInChannel(args[1]) == false) {
						clicli << ERR_NOTONCHANNEL(args[1]);
						return 1;
					}
					chan->addBan(*_serv->getClient(args[3]));
					chan->removeClient(*_serv->getClient(args[3]));
					clicli << RPL_BANLIST(args[1], args[3]);
				} else if (args[2][0] == '-') {
					chan->removeBan(*_serv->getClient(args[3]));
					clicli << RPL_ENDOFBANLIST(args[1]);
				}
			}
			*_serv->getClient(args[3]) << RPL_UMODEIS(args[2]);
			clicli << RPL_CHANNELMODEIS(args[1], args[2], *it);
		}
	}
	std::cout << "\e[32mGUT!\e[0m" << std::endl;
	return 0;
}
	
void	MODE::descr(Client& clicli) {
	clicli << "Usage: MODE <canal> {[+|-]|o|p|s|i|t|n|b|v} [<limite>] [<utilisateur>] [<masque de bannissement >]\n";
	clicli << "Usage: MODE <pseudonyme> {[+|-]|i|w|s|o}\n";
}
