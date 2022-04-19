#include "socket/SocketServer.hpp"

SocketServer::SocketServer(std::string const& hostname, int service): SocketListener(), isRunning(false), hostname(hostname), service(service), timeout(TIMEOUT)
{
   pushFd(sock, POLLIN);
}

SocketServer::SocketServer(SocketServer const &src): SocketListener(src)
{
    pushFd(src.sock, POLLIN);
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
    pushFd(connectionFd, POLLIN);
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
        poll((pollfd*) &pollFds[0], pollFds.size(), timeout);
        try
        {
            for (ConnectionMap::iterator it = fdConnectionMap.begin(); it != fdConnectionMap.end(); ++it)
            {
                receiveAndSend(it->second);
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

void SocketServer::receiveAndSend(Connection *connection)
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

void SocketServer::pushFd(int fd, int events)
{
    pollfd *tmp = new pollfd;
    tmp->fd = fd;
    tmp->events = events;
    pollFds.push_back(tmp);
}
void SocketServer::popFd(int fd)
{
    for (std::vector<pollfd*>::iterator it = pollFds.begin(); it != pollFds.end(); ++it)
    {
        if ((*it)->fd == fd)
        {
            delete *it;
            pollFds.erase(it);
            break;
        }
    }
}