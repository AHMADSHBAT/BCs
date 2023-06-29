
#pragma once

#include "SocketBase.h"
#include "ClientInet.h"
#include <thread>
#include <cstring>
#include <functional>
#include <vector>
#include <sys/un.h>

#define BUFFER_SIZE 4096


class Client_UNIX : public SocketBase
{
public:
    std::function<void(std::string)> onMessageReceived;
    std::function<void(const char*, ssize_t)> onRawMessageReceived;
    std::function<void(int)> onSocketClosed;

    explicit Client_UNIX(int socketId = -1) : SocketBase(UNIX, socketId) {}

    ssize_t SendBytes(const char* bytes, size_t byteslength);
    ssize_t SendMessage(const std::string& message);

    void Connect(const std::string &socketFilePath, std::function<void()> onConnected);

    void Listen();

    void SetAddress(sockaddr_un addr);
    sockaddr_un GetAddress();

    bool deleteAfterClosed = false;

private:
    static void Receive_un(Client_UNIX* socket);
    bool async_mod;
    void SetTimeout(int seconds);
};