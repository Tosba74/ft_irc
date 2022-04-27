
#pragma once

#include "socket/SocketServer.hpp"
#include "socket/SocketConnection.hpp"

class SocketServer;
class SocketConnection;

class InterPars
{
    virtual int pars() PURE;
};

class ACommand: public InterPars
{
    private:
        SocketServer *      _serv;
        SocketConnection &  _client; 
        std::string         _msg;

    public:
        ACommand(SocketServer *serv, SocketConnection &clicli, std::string msg) : _serv(serv), _client(clicli), _msg(msg) {};
        ACommand(ACommand const& inst)  : _serv(inst._serv), _client(inst._client), _msg(inst._msg) {};
        virtual ~ACommand() {};
};

class NIMP: public ACommand
{
    public:
        NIMP(SocketServer *serv, SocketConnection &clicli, std::string msg) : ACommand(serv, clicli, msg) {this->pars();};
        ~NIMP() {};  
        int pars() {std::cout << "Connard" << std::endl;return 0;};
};


