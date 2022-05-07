/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NIMP.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:46:02 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/06 19:44:17 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "client/ACommand.hpp"
#include "client/Client.hpp"

class NIMP: public ACommand
{
    public:
        NIMP(Server *serv);
        NIMP(NIMP const& src);
        ~NIMP();  
        int execute(Client &clicli, std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end);
};
