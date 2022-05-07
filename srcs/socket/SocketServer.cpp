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

SocketServer::~SocketServer()
{
    popFd(sock);
}

void	SocketServer::onConnection(int connectionFd, sockaddr_in& address)
{
    (void)address;
    #ifdef DEBUG
        std::cout << "New connection from " << inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port) << std::endl;
    #endif
    pushFd(connectionFd, POLLIN | POLLHUP);
}

void	SocketServer::onDisconnection(Connection& connection)
{
    (void)connection;
    #ifdef DEBUG
        std::cout << "Disconnection from " << connection.getAddr()<< ":" << connection.getPort() << std::endl;
    #endif
    popFd(connection.getSock());
    delete &connection;
}

void	SocketServer::onMessage(Connection& connection, std::string const& message)
{
    (void)connection;
    if (message.empty())
        return;
    #ifdef DEBUG
        std::cout << "Message from " << connection.getAddr() << ":" << connection.getPort() << ": " << message << std::endl;
    #endif
}

void SocketServer::start()
{
    bind(this->hostname, this->service);
    listen();
    isRunning = true;
    while (isRunning)
    {
        
        poll();
        try
        {
            std::vector<pollfd>::iterator ite = pollFds.end();
            for (std::vector<pollfd>::iterator it = pollFds.begin(); it != ite; ++it)
            {
                if (it->revents & POLLHUP)
                {
                    Connection *connection = fdConnectionMap.at(it->fd);
                    if (connection)
                        onDisconnection(*connection);
                }
                else if (it->revents & POLLIN)
                {
                    if (it->fd == sock)
                    {
                        int connectionFd = accept(addr);
                        if (connectionFd != -1)
                        {
                            onConnection(connectionFd, addr);

                        }
                    }
                    else
                    {
                        Connection* connection = fdConnectionMap[it->fd];
                        receiveAndSend(*connection);
                    }
                }
            }
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

void SocketServer::receiveAndSend(Connection &connection)
{
    try
    {
        std::string message;
        connection >> message;
        for (size_t i = 0; i < message.size(); i++)
        {
            if (message[i] == '\n')
            {
                onMessage(connection, message.substr(0, i));
                message = message.substr(i + 1);
                i = 0;
            }
        }
        message.clear();
    }
    catch (SocketException const& e)
    {
        std::cerr << e.what() << std::endl;
    }
    try
    {
        connection.flush();
    }
    catch (SocketException const& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void SocketServer::pushFd(int fd, int events)
{
    pollfd pollfd;
    pollfd.fd = fd;
    pollfd.events = events;
    pollFds.push_back(pollfd);
}

void SocketServer::popFd(int fd)
{
    for (std::vector<pollfd>::iterator it = pollFds.begin(); it != pollFds.end(); ++it)
    {
        if (it->fd == fd)
        {
            pollFds.erase(it);
            break;
        }
    }
}

void SocketServer::poll()
{
    int ret = ::poll((pollfd *)&pollFds[0], pollFds.size(), -1);
    if (ret == -1)
        throw SocketException("poll");
}