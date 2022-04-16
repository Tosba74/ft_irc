#include "socket/SocketServer.hpp"

SocketServer::SocketServer(std::string const& hostname, int service): SocketListener(), isRunning(false), hostname(hostname), service(service), timeout(TIMEOUT)
{
    pollFds[0].fd = sock;
    pollFds[0].events = POLLIN;
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

void	SocketServer::onDisconnection(Connection* connection)
{
    std::cout << "Disconnection from " << connection->getAddr()<< ":" << connection->getPort() << std::endl;
    for(ConnectionMap::iterator it = fdConnectionMap.begin(); it != fdConnectionMap.end(); ++it)
    {
        if (it->second == connection)
        {
            fdConnectionMap.erase(it);
            break;
        }
    }
    delete connection;
}

void	SocketServer::onMessage(Connection* connection, std::string const& message)
{
    if (message.empty())
        return;
    std::cout << "Message from " << connection->getAddr() << ":" << connection->getPort() << ": " << message << std::endl;
}

void SocketServer::start()
{
    bind(this->hostname, this->service);
    listen();
    isRunning = true;
    while (isRunning)
    {
        poll(pollFds, pollFdsSize, timeout);
        try
        {
            for (ConnectionMap::iterator it = fdConnectionMap.begin(); it != fdConnectionMap.end(); ++it)
            {
                threadConnection(it->second);
            }
            int connectionFd = accept(addr);
            Connection* connection = onConnection(connectionFd, addr);
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

void SocketServer::threadConnection(Connection *connection)
{
    try
    {
        std::string buffer;
        *connection >> buffer;
        onMessage(connection, buffer);
    }
    catch (SocketException const& e)
    {
        std::cerr << e.what() << std::endl;
    }
    try
    {
        connection->flush();
    }
    catch (SocketException const& e)
    {
        std::cerr << e.what() << std::endl;
    }
}