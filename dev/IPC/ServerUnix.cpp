#include "ServerUnix.h"



Server_UNIX::Server_UNIX() : SocketBase(UNIX)
{
    int opt = 1;
    this->m_clients = {0};
    setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
}

void Server_UNIX::Bind(const std::string& socketFilePath)
{
    this->address.sun_family = AF_UNIX;
    strncpy(this->address.sun_path, socketFilePath.c_str(), sizeof(this->address.sun_path) - 1);

    if (bind(this->sock, (const sockaddr*)&this->address, sizeof(this->address)) == -1)
    {
        printf("Cannot bind the socket. Error code: %d\n", errno);
        return;
    }
}

void Server_UNIX::Listen()
{
    if (listen(this->sock, 20) == -1)
    {
        printf("Error: Server_UNIX cannot listen to the socket. Error code: %d\n", errno);
        return;
    }
    std::thread r(&Server_UNIX::Accept_un, this);
    r.detach();
}

void Server_UNIX::Accept_un(Server_UNIX* server)
{
    sockaddr_un newSocketInfo;
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

        /* In the main server thread, we associate a new client instance
           to the file descriptor newFd and set the address to the connected socket
           as well as the lambda function for the connection event.
           Finally, create a separate thread for the client to listen for incoming messages. */
        Client_UNIX* newClient = new Client_UNIX(newFd);
        newClient->deleteAfterClosed = true;
        newClient->SetAddress(newSocketInfo);
        server->onConnectionEvent(newClient);
        newClient->Listen();
    }
};