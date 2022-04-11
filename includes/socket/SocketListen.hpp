#pragma once

#include <string> // using std::string

#include <socket/Socket.hpp> // using Socket

class SocketListener	:	public Socket
{
protected:
	bool	listening;

public:
	SocketListener() throw();
	~SocketListener() throw();

	SocketListener(std::string const& hostname, std::string const& service, int type = SOCK_STREAM, int opt = SOCK_NONBLOCK, int proto = IPPROTO_IP) throw();

	void			bind(std::string const& hostname, std::string const& service, int type = SOCK_STREAM, int opt = SOCK_NONBLOCK, int proto = IPPROTO_IP) throw();

	void			listen() throw();

	virtual int		accept(sockaddr &clientAddr) const;

	virtual void	close() throw();

	bool	isListening() const throw()
	{ return listening; }
};