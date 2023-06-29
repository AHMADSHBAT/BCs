#include "dev/IPC/ServerInet.h"
#include "dev/IPC/ClientInet.h"
#include <iostream>

using namespace std;

int main()
{
    // Initialize server socket..
    Server_INET Server_INET; /*Call Traces: this->sock = socket(AF_INET, sockType, 0);*/

    //capturing the client instance from lambda func
    /* NOTE: by this mechanism, the framework gives the user space to alter the behavior/structure of the logic
       by using lambda funcs*/
    Client_INET gClient;
    /* Injecting our lambda funcs and assosiat it to connection event
       Note: all the lambda funcs inside onConnectionEvent func are to inject
       a custom code into the client instance*/
    Server_INET.onConnectionEvent = [&gClient](Client_INET *newClient) {
        cout << "New client: [";
        cout << newClient->remoteAddress() << ":" << newClient->remotePort() << "]" << endl;

        newClient->onMessageReceived = [newClient](string message) {
            cout << newClient->remoteAddress() << ":" << newClient->remotePort() << " => " << message << endl;
            newClient->SendMessage("OK! I've got your message Mr.Server");
        };

        gClient = *newClient;
        
        newClient->onSocketClosed = [newClient](int errorCode) {
            cout << "Socket closed:" << newClient->remoteAddress() << ":" << newClient->remotePort() << " -> " << errorCode << endl;
            cout << flush;
        };
    };


    // Bind the server to a port.
    Server_INET.Bind(8888);

    // Start Listening the server.
    Server_INET.Listen();
    /* Call traces:
                    std::thread t(&Server_INET::Accept, this); Call traces: ------------> void Server_INET::Accept(Server_INET* server)
                                                                                        {
                                                                                            sockaddr_in newSocketInfo;
                                                                                            socklen_t newSocketInfoLength = sizeof(newSocketInfo);

                                                                                            int newFd = -1;
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

                                                                                                Client_INET* newClient = new Client_INET(newFd);
                                                                                                newClient->deleteAfterClosed = true;
                                                                                                newClient->SetAddress(newSocketInfo);
                                                                                                server->onConnectionEvent(newClient);
                                                                                                newClient->Listen();
                                                                                            }
                                                                                        }
                    
                    
                    
                    
                    
                    
                    
                    */

    // You should do an input loop, so the program won't terminate immediately
    string input;
    getline(cin, input);
    while (input != "exit")
    {
        //using the captured instance to send msgs from the server to the client
        gClient.SendMessage(input);
        getline(cin, input);
    }

    // Close the server before exiting the program.
    Server_INET.Close();

    return 0;
}