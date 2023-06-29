#include "dev/IPC/ServerUnix.h"
#include "dev/IPC/ClientUnix.h"
#include <iostream>

using namespace std;

int main()
{
    // Initialize socket.
    Client_UNIX socket;
/* Call traces:--------|
                       |                    if (socketId == -1)
                       |                         {
                       |---------------------------> this->sock = socket(AF_INET, sockType, 0);
                                                    
                                                    if ( this->sock == -1 )
                                                    {
                                                        printf("Socket creating error.");
                                                    }
                                                }
                                                else
                                                {
                                                    this->sock = socketId;
                                                }
*/
    /* Injecting the following lambda func to be triggered on receiving msgs event */
    socket.onRawMessageReceived = [](const char* message, int length) {
        cout << "Message from the Server: " << message << "   (" << length << ")" << endl;
    };

   
    /* Injecting the following lambda func to be triggered on Event of socket closed:*/
    socket.onSocketClosed = [](int errorCode){
        cout << "Connection closed: " << errorCode << endl;
    };

    /* Note: The following func tirgger: separate thread for receiveing msgs from the server & */
    socket.Connect("./sock", [&] {
        cout << "Connected to the server successfully." << endl;
/*  Call Traces:
                        void Client_UNIX::Connect(const char* host, uint16_t port, std::function<void()> onConnected)
                        {
                            int status = connect(this->sock, (const sockaddr*)&this->address, sizeof(sockaddr_in));
                            this->SetTimeout(0);

                            onConnected();

                            this->Listen(); ------>Call Traces:
                                                    std::thread t(&Client_UNIX::Receive, this); -------->Call Traces:
                                                    t.detach();                                                  while ((messageLength = recv(client->sock, tempBuffer, BUFFER_SIZE, 0)) > 0)
                                                                                                                {
                                                                                                                    tempBuffer[messageLength] = '\0';
                                                                                                                    if (client->onMessageReceived)
                                                                                                                        client->onMessageReceived(std::string(tempBuffer, messageLength));

                                                                                                                    if (client->onRawMessageReceived)
                                                                                                                        client->onRawMessageReceived(tempBuffer, messageLength);
                                                                                                                }

                        
*/

        // Send String:
        socket.SendMessage("Hello Server!");
    });

    // You should do an input loop, so the program won't terminate immediately
    string input;
    getline(cin, input);
    while (input != "exit")
    {
        socket.SendMessage(input);
        getline(cin, input);
    }

    socket.Close();

    return 0;
}