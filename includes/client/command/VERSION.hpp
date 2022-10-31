/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VERSION.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 01:08:34 by bmangin           #+#    #+#             */
/*   Updated: 2022/10/31 01:10:47 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class VERSION : public ACommand
{
	public:
		VERSION(Server *serv);
		VERSION(VERSION const& src);
		~VERSION();
		int		execute(Client &clicli, std::vector<std::string> args);
		void	descr(Client& clicli);
};
