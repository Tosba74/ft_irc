/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NIMP.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:46:02 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/04 19:07:39 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "client/ACommand.hpp"
#include "socket/SocketConnection.hpp"

class NIMP: public ACommand
{
    public:
        NIMP(Server *serv, Client &clicli, std::string msg);
        NIMP(NIMP const& src);
        ~NIMP();  
        int execute();
};
