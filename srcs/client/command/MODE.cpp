/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 01:51:55 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/09 13:31:85by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/MODE.hpp"
#include "irc/Server.hpp"
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

enum e_mode {
	o = (1 << 0),
	p = (1 << 1),
	s = (1 << 2),
	i = (1 << 3),
	t = (1 << 4),
	n = (1 << 5),
	m = (1 << 6),
	l = (1 << 7),
	b = (1 << 8),
	v = (1 << 9),
	k = (1 << 10)
};

// REPLY :
	// clicli << RPL_CHANNELMODEIS(args[1], clicli.getMode(), args[5]);
	// clicli << ERR_CHANOPRIVSNEEDED(args[1]);
	// clicli << RPL_BANLIST(args[1], args[5]);
	// clicli << RPL_ENDOFBANLIST(args[1]);
	// clicli << ERR_KEYSET(args[1]);
	// clicli << ERR_USERSDONTMATCH();
	// clicli << RPL_UMODEIS(clicli.getMode());
	// clicli << ERR_UMODEUNKNOWNFLAG();
	
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
	// std::string		name = arg.substr(1, arg.size() - 1);
	if (arg[0] != '#' || !_serv->getChannel(arg)) {
		clicli << ERR_NOSUCHCHANNEL(arg);
		return 1;
	} else if (!_serv->getChannel(clicli.getCurrchan()) || arg.compare(clicli.getCurrchan())) {
		clicli << ERR_NOTONCHANNEL(arg);
		return 1;
	}
	return 0;
}

int		MODE::checkMode(Client &clicli, std::string arg, const char *cmp) {
	std::string::iterator it = arg.begin();
	if (!(*it == '+' || *it == '-')) {
		clicli << ERR_UMODEUNKNOWNFLAG();
		return 1;
	}
	++it; 
	for (; it != arg.end(); ++it) {
		std::cout << *it << std::endl;
		if (indexage(*it, cmp) == -1) {
			clicli << ERR_USERSDONTMATCH();
			return 1;
		}
	}
	return 0;
}

int		MODE::verifArgs(Client &clicli, std::vector<std::string> args) {
	if (args[1][0] == '#') {
		if (!_serv->getChannel(args[1])) {
			clicli << ERR_NOSUCHCHANNEL(args[1]);
			return -1;
		} else {
			if (args[1].compare(clicli.getCurrchan())) {
				clicli << ERR_NOTONCHANNEL(args[1]);
				return -1;
			} else {
				if (checkMode(clicli, args[2], "psimtknvlob") == -1)
					return -1;
				else
					return 0;
			}
		}
	} else {
		if (!_serv->getClient(args[1])) {
			clicli << ERR_NOSUCHNICK(args[1]);
			return -1;
		} else {
			if (checkMode(clicli, args[2], "iswo") == 1)
				return -1;
			else
				return 1;
		}
	}
	return -1;
}

int		MODE::execute(Client &clicli, std::vector<std::string> args) {
	if (args.size() < 3) {
		clicli << ERR_NEEDMOREPARAMS(args[0]);
		return 1;
	}
	int i = verifArgs(clicli, args);
	if (i == -1) {
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
		std::cout << "args[2] is a Channel" << std::endl;
		Channel		*chan = _serv->getChannel(args[1]);
		std::string::iterator it = args[2].begin();
		++it; 
		for (; it != args[2].end(); ++it) {
			int		index = indexage(*it, "psimtknvlob") + 1;
			if (index < 9) {
				chan->_mod ^= (1 << index);
			} else if (index == 9) {
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
			} else if (index == 10) {
				// clicli + o;
				;
			} else if (index == 11) {
				if (args.size() == 3) {
					clicli << ERR_NEEDMOREPARAMS(args[0]);
					return 1;
				} else {
					std::vector<std::string>::iterator it = args.begin();
					++it;
					for (; it != args.end(); ++it) {
						if (!_serv->getClient(*it)) {
							clicli << ERR_NOSUCHNICK(*it);
							return 1;
						} else {
							chan->addClient(*(_serv->getClient(*it)), chan->getBan());
						}
					}
				}
			}
		}
	}
	return 0;
}

/*
int		MODE::execute(Client &clicli, std::vector<std::string> args) {
	if (args.size() < 3) {
		clicli << ERR_NEEDMOREPARAMS(args[0]);
		return 1;
	}
	std::cout << "Parser passe !!!";
	if (checkChannel(clicli, args[1]))
		return 1;
	if (checkMode(clicli, args[2]))
		return 1;
	
	std::cout << "Verif arguments !";
	if (args[2][1] == 'p') {
		std::cout << "parser P";
		if (args[2][0] == '+')
			_serv->getChannel(args[2])->_mod ^= MOD_CHAN_VIP;
		if (args[2][0] == '-')
			_serv->getChannel(args[2])->_mod |= MOD_CHAN_VIP;
	}
	// if (_serv->getChannel(clicli.getCurrchan()) ==  NULL) {
		// clicli << ERR_NOTONCHANNEL(args[1]);
		// return 1;
	// } else if (_serv->getChannel(args[1])) {
		// clicli << ERR_NOSUCHCHANNEL(args[1]);
		// return 1;
	// }
	(void)clicli;
	(void)args;
	return 0;
}
*/

void	MODE::descr(Client& clicli) {
	clicli << "Usage: MODE <canal> {[+|-]|o|p|s|i|t|n|b|v} [<limite>] [<utilisateur>] [<masque de bannissement >]\n";
	clicli << "Usage: MODE <pseudonyme> {[+|-]|i|w|s|o}\n";
}