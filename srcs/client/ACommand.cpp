/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ACommand.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:46:18 by bmangin           #+#    #+#             */
/*   Updated: 2022/11/17 13:19:07 by ahuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/ACommand.hpp"

ACommand::ACommand(Server *serv) : _serv(serv) {}

ACommand::ACommand(ACommand const& src)  : _serv(src._serv) {
    #ifdef DEBUG
        std::cout << "Copy Constructeur Called" << std::endl;
    #endif
}
ACommand::~ACommand() {
    #ifdef DEBUG
        std::cout << "Destructeur Called" << std::endl;
    #endif
}

ACommand&   ACommand::operator=(ACommand const& rhs) {
	if (this != &rhs) {
		this->_serv = rhs._serv;
	}
	return *this;
}

const Server *				ACommand::getServ() const {
	return this->_serv;
}
