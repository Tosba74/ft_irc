/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:54:12 by emenella          #+#    #+#             */
/*   Updated: 2022/05/09 18:18:06 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client/ACommand.hpp"
#include "client/Client.hpp"
#include "irc/Server.hpp"

class USER : public ACommand
{
    public:
        USER(Server *serv);
        USER(USER const& src);
        ~USER();
        int execute(Client &clicli, args_t::iterator begin, args_t::iterator end);
};