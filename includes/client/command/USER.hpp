/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:54:12 by emenella          #+#    #+#             */
/*   Updated: 2022/05/09 23:05:51 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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