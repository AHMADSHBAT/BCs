#pragma once



#include "SocketBase.h"
#include <string>
#include <functional>
#include <thread>
#include <cstring>
#include <functional>
#include <sys/un.h>

#define BUFFER_SIZE 4096
class Client_INET : public SocketBase
{
public:
    std::function<void(std::string)> onMessageReceived;
    std::function<void(const char*, ssize_t)> onRawMessageReceived;
    std::function<void(int)> onSocketClosed;

    explicit Client_INET(int socketId = -1) : SocketBase(TCP, socketId) {}

    ssize_t SendBytes(const char* bytes, size_t byteslength);
    ssize_t SendMessage(const std::string& message);

    void Connect(uint32_t ipv4, uint16_t port, std::function<void()> onConnected = [](){});
    void Connect(const char* host, uint16_t port, std::function<void()> onConnected = [](){});
    void Connect(const std::string& host, uint16_t port, std::function<void()> onConnected = [](){});

    void Listen();

    void SetAddress(sockaddr_in addr);
    sockaddr_in GetAddress() const;

    bool deleteAfterClosed = false;

private:
    static void Receive(Client_INET* socket);
    bool async_mod;
    void SetTimeout(int seconds);
};


/*********************************************************************************************************************************/
/*********************************************************************************************************************************/
/*********************************************************************************************************************************/
/*********************************************************************************************************************************/
/*********************************************************************************************************************************/


