#pragma once

#if defined(__linux__) || defined(__APPLE__)
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#elif _WIN32
#include <winsock32.h>
#endif

#include <string>
#include <functional>
#include <cerrno>
#include <sys/un.h>

#define FDR_UNUSED(expr){ (void)(expr); } 
#define FDR_ON_ERROR std::function<void(int, std::string)> onError = [](int errorCode, std::string errorMessage){FDR_UNUSED(errorCode); FDR_UNUSED(errorMessage)}

#ifndef AS_DEFAULT_BUFFER_SIZE
#define AS_DEFAULT_BUFFER_SIZE 0x1000 /*4096 bytes*/
#endif

class SocketBase
{
public:
    enum SocketType
    {
        TCP = 1,
        UNIX = 2
    };
    sockaddr_in address;
    sockaddr_un address_un;


    void Close() {
        shutdown(this->sock, SHUT_RDWR);
        close(this->sock);
    }

    std::string remoteAddress() const { return ipToString(this->address); }
    int remotePort() const { return ntohs(this->address.sin_port); }
    int fileDescriptor() const { return this->sock; }

protected:
    int sock = 0;

    // Get std::string value of the IP from a `sockaddr_in` address struct
    static std::string ipToString(const sockaddr_in& addr)
    {
        char ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(addr.sin_addr), ip, INET_ADDRSTRLEN);

        return std::string(ip);
    }  

    SocketBase(SocketType sockType, int socketId = -1)
    {
        if (socketId == -1 && sockType == TCP)
        {
            this->sock = socket(AF_INET, sockType, 0);
            
            if ( this->sock == -1 )
            {
                printf("Socket creating error.");
            }
        }
        else if(socketId == -1 && sockType == UNIX)
        {
            this->sock = socket(AF_UNIX, SOCK_STREAM, 0);
            
            if ( this->sock == -1 )
            {
                printf("Socket creating error.");
            }
        }
        else
        {
            this->sock = socketId;
        }
    }
    virtual ~SocketBase(){}
};