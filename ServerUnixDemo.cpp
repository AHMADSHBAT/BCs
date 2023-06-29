#include "dev/IPC/ServerUnix.h"
#include "dev/IPC/ServerUnix.h"
#include <iostream>

using namespace std;

int main()
{
    // Initialize server socket..
    Server_UNIX Server_UNIX; /*Call Traces: this->sock = socket(AF_INET, sockType, 0);*/

    //capturing the client instance from lambda func
    /* NOTE: by this mechanism, the framework gives the user space to alter the behavior/structure of the logic
       by using lambda funcs*/
    Client_UNIX gClient;
    /* Injecting our lambda funcs and assosiat it to connection event
       Note: all the lambda funcs inside onConnectionEvent func are to inject
       a custom code into the client instance*/
    Server_UNIX.onConnectionEvent = [&gClient](Client_UNIX *newClient) {
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
    Server_UNIX.Bind("./sock");

    // Start Listening the server.
    Server_UNIX.Listen();
    /* Call traces:
                    std::thread t(&Server_UNIX::Accept, this); Call traces: ------------> void Server_UNIX::Accept(Server_UNIX* server)
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

                                                                                                Client_UNIX* newClient = new Client_UNIX(newFd);
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
    Server_UNIX.Close();

    return 0;
}