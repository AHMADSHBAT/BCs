#include "transport_server.h"

Server_INET::Server_INET()
{
    int opt = 1;
    this->m_clients = {0};
    setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
    setsockopt(this->sock, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(int));
}

void Server_INET::Bind(const char* address, uint16_t port)
{
    int status = inet_pton(AF_INET, address, &this->address.sin_addr);
    switch (status)
    {
        case -1:
            printf("Invalid address. Address type not supported. Error code: %d\n", errno);
            return;
        case 0:
            printf("AF_INET is not supported. Please send a message to the developer. Error code: %d\n", errno);
            return;
        default:
            break;
    }



    this->address.sin_family = AF_INET;
    this->address.sin_port = htons(port);

    if (bind(this->sock, (const sockaddr*)&this->address, sizeof(this->address)) == -1)
    {
        printf("Cannot bind the socket. Error code: %d\n", errno);
        return;
    }
}

void Server_INET::Bind(uint16_t port)
{
    this->Bind("0.0.0.0", port);
}

void Server_INET::Listen()
{
    if (listen(this->sock, 20) == -1)
    {
        printf("Error: Server_INET cannot listen to the socket. Error code: %d\n", errno);
        return;
    }

    std::thread t(&Server_INET::Accept, this);
    t.detach();
}

void Server_INET::Accept(Server_INET* server)
{
    sockaddr_in newSocketInfo;
    socklen_t newSocketInfoLength = sizeof(newSocketInfo);

    int newFd = -1;

    /* Accepting 20 max client connections by this loop*/
    while (true)
    {
        newFd = accept(server->sock, (sockaddr*)&newSocketInfo, &newSocketInfoLength);
        if (newFd == -1)
        {
            if (errno == EBADF || errno == EINVAL)
                return;

            printf("Error while accepting a new connection. Error code: %d\n", errno);

            return;
        }

        /* In the main server thread we assosiat a new client instance
           to the file discriptor newFd and we insert the connected address to
           it as well as the lambda func to the conn event
           And finally creating a separate thread of Listen()-> Receiving msgs*/
        Client_INET* newClient = new Client_INET(newFd);
        newClient->deleteAfterClosed = true;
        newClient->SetAddress(newSocketInfo);
        server->onConnectionEvent(newClient);
        newClient->Listen();
    }
}
