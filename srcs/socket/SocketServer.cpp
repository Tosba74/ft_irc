#include "socket/SocketServer.hpp"

SocketServer::SocketServer(std::string const& hostname, int service): SocketListener(), isRunning(false), hostname(hostname), service(service)
{
}

SocketServer::SocketServer(SocketServer const &src): SocketListener(src)
{
}

SocketServer &SocketServer::operator=(SocketServer const &rhs)
{
    SocketListener::operator=(rhs);
    return *this;
}

SocketServer::~SocketServer() throw()
{
}

SocketConnection*	SocketServer::onConnection(int connectionFd, sockaddr_in& address)
{
    std::cout << "New connection from " << inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port) << std::endl;
    return new SocketConnection(connectionFd, address);
}

void	SocketServer::onDisconnection(connection* connection)
{
    std::cout << "Disconnection from " << connection->getAddr()<< ":" << connection->getPort() << std::endl;
    delete connection;
}

void	SocketServer::onMessage(connection* connection, std::string const& message)
{
    std::cout << "Message from " << connection->getAddr() << ":" << connection->getPort() << ": " << message << std::endl;
}

void SocketServer::start()
{
    bind(this->hostname, this->service);
    listen();
    isRunning = true;
    while (isRunning)
    {
        try
        {
            int connectionFd = accept(addr);
            if (connectionFd == -1)
                throw SocketException("Socket accept failed");
            connection* connection = onConnection(connectionFd, addr);
            
            fdConnectionMap[connectionFd] = connection;
        }
        catch (SocketException const& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}

void SocketServer::stop()
{
    isRunning = false;
}
