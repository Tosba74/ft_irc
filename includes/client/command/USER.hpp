/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:54:12 by emenella          #+#    #+#             */
/*   Updated: 2022/05/17 16:58:46 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "client/ACommand.hpp"
#include "irc/Server.hpp"

class USER : public ACommand
{
    public:
        USER(Server *serv);
        USER(USER const& src);
        ~USER();
        int execute(Client &clicli, args_t::iterator begin, args_t::iterator end);
};