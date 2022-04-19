/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketListener.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:30:15 by bmangin           #+#    #+#             */
/*   Updated: 2022/04/19 23:30:27 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <socket/Socket.hpp>

class SocketListener : public Socket
{
protected:
	bool	listening;

public:
	~SocketListener() throw();

	SocketListener(int type = AF_INET, int opt = SOCK_STREAM, int proto = IPPROTO_IP) throw();

	void bind(std::string const& hostname, int service, int type = AF_INET);

	void listen();

	virtual int accept(sockaddr_in &clientAddr);

	virtual void close() throw();

	bool	isListening() const throw()
	{ return listening; }
};