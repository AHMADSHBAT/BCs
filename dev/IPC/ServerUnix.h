


#pragma once

#include "SocketBase.h"
#include <thread>
#include <cstring>
#include <functional>
#include <vector>
#include "ClientUnix.h"


#define BUFFER_SIZE 4096


class Server_UNIX : public SocketBase


{
public:
    explicit Server_UNIX();
    void Bind(const std::string& socketFilePath);
    void Listen();

    // Event handler for new client connections
    std::function<void(Client_UNIX*)> onConnectionEvent = [&](Client_UNIX* sock){FDR_UNUSED(sock)};

private:
    static void Accept_un(Server_UNIX* server);
    sockaddr_un address;
    std::vector<Client_UNIX*> m_clients;
};



