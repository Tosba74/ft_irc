/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NIMP.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:46:02 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/05 17:46:06 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "client/ACommand.hpp"
#include "socket/SocketConnection.hpp"

class NIMP: public ACommand
{
    public:
        NIMP(Server *serv);
        NIMP(NIMP const& src);
        ~NIMP();  
        int execute(Client &clicli, std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end);
};
