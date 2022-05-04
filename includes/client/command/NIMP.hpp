/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NIMP.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:46:02 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/04 17:39:27 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "client/ACommand.hpp"
#include "socket/SocketConnection.hpp"

class NIMP: ACommand
{
    public:
        NIMP(Server *serv, Client &clicli, std::string msg);
        NIMP(NIMP const& src);
        ~NIMP();  
        int execute();
};
