/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:27:56 by emenella          #+#    #+#             */
/*   Updated: 2022/05/17 17:37:39 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/command/PASS.hpp"

PASS::PASS(Server *serv) : ACommand(serv)
{

}

PASS::PASS(PASS const& src) : ACommand(src)
{
    if (this != &src)
    {
        this->_serv = src._serv;
    }
}

PASS::~PASS()
{
}

int PASS::execute(Client &clicli, args_t::iterator begin, args_t::iterator end)
{
    if (clicli.getRegister())
	{
		clicli << ERR_ALREADYREGISTRED;
		return 0;
	}
    std::size_t len = std::distance(begin, end);
    if (len < 2)
    {
        clicli << ERR_NEEDMOREPARAMS("PASSWORD");
        return 0;
    }
    std::string pass = begin[1];
    clicli.setPassword(pass);
    clicli.updateRegister();
    return 0;
}