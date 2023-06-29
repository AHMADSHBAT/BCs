#pragma once

#include "SocketBase.h"
#include "ClientInet.h"
#include <thread>
#include <cstring>
#include <functional>
#include <vector>
#define BUFFER_SIZE 4096


class Server_INET : public SocketBase
{
public:
    std::function<void(Client_INET*)> onConnectionEvent = [&](Client_INET* sock){FDR_UNUSED(sock)};
    explicit Server_INET();

    // Bind the custom address & port of the Server_INET.
    void Bind(const char* address, uint16_t port);

    // Bind the address(0.0.0.0) & port of the Server_INET.
    void Bind(uint16_t port);

    // Start listening for incoming connections.
    void Listen();


private:
    static void Accept(Server_INET* Server_INET);
    std::vector<int> m_clients;
    bool async_mod;
};


