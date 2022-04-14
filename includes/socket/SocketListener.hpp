#pragma once

#include <string> // using std::string

#include <socket/Socket.hpp> // using Socket

class SocketListener	:	public Socket
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