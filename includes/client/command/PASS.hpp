/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:27:37 by emenella          #+#    #+#             */
/*   Updated: 2022/10/30 23:23:03 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "client/ACommand.hpp"

class PASS: public ACommand
{
    public:
        PASS(Server *serv);
        PASS(PASS const& src);
        ~PASS();
        int     execute(Client &clicli, std::vector<std::string> args);
        void    descr(Client& clicli);
};
