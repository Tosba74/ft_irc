/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASSWORD.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:27:37 by emenella          #+#    #+#             */
/*   Updated: 2022/10/18 18:48:39 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "client/ACommand.hpp"

class PASSWORD: public ACommand
{
    public:
        PASSWORD(Server *serv);
        PASSWORD(PASSWORD const& src);
        ~PASSWORD();
        int     execute(Client &clicli, args_t::iterator begin, args_t::iterator end);
};
