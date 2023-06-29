#include "ClientUnix.h"

/* send bytes to the fd using send function from std socket lib */
ssize_t Client_UNIX::SendBytes(const char* bytes, size_t bytesLength)
{
    return send(this->sock, bytes, bytesLength, 0);
}

/* send strings to the fd using Client_UNIX::Send func */
ssize_t Client_UNIX::SendMessage(const std::string& message)
{
    return this->SendBytes(message.c_str(), message.length());
}

/* Connecting the current client sock to the UNIX socket file path */
void Client_UNIX::Connect(const std::string& socketFilePath, std::function<void()> onConnected)
{
    memset(&this->address_un, 0, sizeof(sockaddr_un));
    this->address_un.sun_family = AF_UNIX;
    strncpy(this->address_un.sun_path, socketFilePath.c_str(), sizeof(this->address_un.sun_path) - 1);

    /* Try to connect. */
    int status = connect(this->sock, (const sockaddr*)&this->address_un, sizeof(sockaddr_un));
    if (status == -1)
    {
        printf("Connection failed to the host. %d", errno);
        return;
    }

    // Connected to the server, fire the event.
    onConnected();

    // Start listening from the server.
    this->Listen();
}

void Client_UNIX::Listen()
{
    std::thread u(&Client_UNIX::Receive_un, this);
    u.detach();
}

/* This func is kind of an abstract func because its structure 
   is for using the given socket to send/receive data */
void Client_UNIX::Receive_un(Client_UNIX* client)
{
    char tempBuffer[BUFFER_SIZE];
    ssize_t messageLength;

    while ((messageLength = recv(client->sock, tempBuffer, BUFFER_SIZE, 0)) > 0)
    {
        tempBuffer[messageLength] = '\0';
        if (client->onMessageReceived)
            client->onMessageReceived(std::string(tempBuffer, messageLength));

        if (client->onRawMessageReceived)
            client->onRawMessageReceived(tempBuffer, messageLength);
    }

    client->Close();
    if (client->onSocketClosed)
        client->onSocketClosed(errno);

    if (client->deleteAfterClosed && client != nullptr)
        delete client;
}

/* Setting */
void Client_UNIX::SetAddress(sockaddr_un addr)
{
    this->address_un = addr;
}

/* Getting the address that the socket is connected to (you're good to go!) */
sockaddr_un Client_UNIX::GetAddress()
{
    return this->address_un;
}

void Client_UNIX::SetTimeout(int seconds)
{
    struct timeval tv;
    tv.tv_sec = seconds;    /* number of seconds to wait */
    tv.tv_usec = 0;         /* number of microseconds to wait */

    /* Setting the client socket timeout for receiving msgs (SO_RCVTIMEO) and sending msgs (SO_SNDTIMEO) */
    setsockopt(this->sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(tv));
    setsockopt(this->sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&tv, sizeof(tv));
}

