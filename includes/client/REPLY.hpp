/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   REPLY.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 23:39:08 by bmangin           #+#    #+#             */
/*   Updated: 2022/10/15 23:40:59 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define RPL_WELCOME(nick, user, host) "001 " + _nickname + " :Welcome to the Internet Relay Network " + _nickname + "!" + _username + "@" + _hostname

#define ERR_NEEDMOREPARAMS(command) "461 " + command " :Not enough parameters"

