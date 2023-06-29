#include "ClientInet.h"


/* send bytes to the fd using send func from std socket lib*/
ssize_t Client_INET::SendBytes(const char* bytes, size_t bytesLength)
{
    return send(this->sock, bytes, bytesLength, 0);
}


/* send strings to the fd using Client_INET::Send func */
ssize_t Client_INET::SendMessage(const std::string& message)
{
    return this->SendBytes(message.c_str(), message.length());
}

/* Connecting the curr client sock to the ip & port from para
   Note: the last para of this func is to give users of DEV framework
   space to insert any kind of code/logic right after successful connection
   with the server ;)*/
void Client_INET::Connect(uint32_t ipv4, uint16_t port, std::function<void()> onConnected)
{
    this->address.sin_family = AF_INET;
    this->address.sin_port = htons(port);
    this->address.sin_addr.s_addr = ipv4;

    this->SetTimeout(5);

    /* Try to connect. */
    int status = connect(this->sock, (const sockaddr*)&this->address, sizeof(sockaddr_in));
    if (status == -1)
    {
        printf("Connection failed to the host. %d", errno);
        /*successful connection -> no need for timing out*/
        this->SetTimeout(0);
        return;
    }

    this->SetTimeout(0);

    // Connected to the server, fire the event.
    onConnected();

    // Start listening from the server.
    this->Listen();
}

void Client_INET::Connect(const char* host, uint16_t port, std::function<void()> onConnected)
{
    /*  addrinfo is a Structure to contain information about address of a service provider.*/
    struct addrinfo hints /* The filter*/    , *res /* The results struct*/   , *it /* interator*/;
    memset(&hints, 0, sizeof(hints));

    /* Setting up the filters to get the spicific info from the address: IPV4 and socket_stream type */
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    /* Getting the address info from the host and filtering those info by "hints" vaiable*/
    int status = getaddrinfo(host, NULL, &hints, &res);
    if (status != 0)
    {
        printf("Invalid address: %s erro: %d ", std::string(gai_strerror(status)), errno);
        return;
    }


    /* a loop that iterates over the linked list of address structures (res) returned by 
    the getaddrinfo function. It searches for the first address structure with 
    the address family (ai_family) set to AF_INET, which represents IPv4 addresses
    */
    for (it = res; it != NULL; it = it->ai_next)
    {
        if (it->ai_family == AF_INET)
        { 
            /* Getting the ipv4 add and store it in the class mamber "address" to be
               used later */
            memcpy((void*)(&this->address), (void*)it->ai_addr, sizeof(sockaddr_in));
            break;
        }
    }

    freeaddrinfo(res);

    this->Connect((uint32_t)this->address.sin_addr.s_addr, port, onConnected);
}

void Client_INET::Connect(const std::string& host, uint16_t port, std::function<void()> onConnected)
{
    this->Connect(host.c_str(), port, onConnected);
}

void Client_INET::Listen()
{
    std::thread t(&Client_INET::Receive, this);
    t.detach();
}



/* This func is kind of abstract func, because its structure 
   is for using the para socket to send/receive data*/
void Client_INET::Receive(Client_INET* client)
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
void Client_INET::SetAddress(sockaddr_in addr)
{
    this->address = addr;
}

/* Getting the address that the socket is connected to (you're good to go!)*/
sockaddr_in Client_INET::GetAddress() const
{
    return this->address;
}

void Client_INET::SetTimeout(int seconds)
{
    struct timeval tv;
    tv.tv_sec = seconds;    /*number of seconds to wait*/
    tv.tv_usec = 0;         /*number of microSeconds to wait*/

    /* Setting the client socket timeout for receiveing msgs (SO_RCVTIMEO) and sending msgs (SO_SNDTIMEO)*/
    setsockopt(this->sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(tv));
    setsockopt(this->sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&tv, sizeof(tv));
};



/*********************************************************************************************************************************/
/*********************************************************************************************************************************/
/*********************************************************************************************************************************/
/*********************************************************************************************************************************/
/*********************************************************************************************************************************/


