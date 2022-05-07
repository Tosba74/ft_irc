/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketListener.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:30:15 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/07 13:17:29 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <socket/Socket.hpp>

class SocketListener : public Socket
{
	private:
		virtual void close() throw();
	protected:
		bool	listening;

	public:
		virtual ~SocketListener();
		SocketListener(int type = AF_INET, int opt = SOCK_STREAM, int proto = IPPROTO_IP);
		void bind(std::string const& hostname, int service, int type = AF_INET);
		void listen();
		virtual int accept(sockaddr_in &clientAddr);
		bool	isListening() const
		{ return listening; }
};