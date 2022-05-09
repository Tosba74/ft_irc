/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SocketListener.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emenella <emenella@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 23:30:15 by bmangin           #+#    #+#             */
/*   Updated: 2022/05/09 16:08:22 by emenella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <socket/Socket.hpp>

class SocketListener : public Socket
{
	private:
		virtual void close();
	protected:
		bool	listening;

	public:
		virtual ~SocketListener();
		SocketListener(int type = AF_INET, int opt = SOCK_STREAM, int proto = IPPROTO_IP);
		void bind(std::string const& hostname, int service, int type = AF_INET);
		virtual void listen();
		virtual int accept(sockaddr_in &clientAddr);
		bool	isListening() const
		{ return listening; }
};