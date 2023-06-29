#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "dev/IPC/ShareMem.h" // Include the header file you created

int main() {
    int sharedMemoryId = 1234;
    int sharedMemorySize = 1024;

    IPCMemoryShare instance1(sharedMemoryId, sharedMemorySize);
    IPCMemoryShare instance2(sharedMemoryId, sharedMemorySize);

    if (instance1.create()) {
        std::cout << "Instance 1 created shared memory segment." << std::endl;
        sleep(1);

        if (instance2.attach()) {
            std::cout << "Instance 2 attached to shared memory segment." << std::endl;

            std::cout << "Instance 1 initial content: " << instance1.read() << std::endl;
            std::cout << "Instance 2 initial content: " << instance2.read() << std::endl;

            instance2.write("Hello from instance 2!");

            std::cout << "Instance 1 after modification by instance 2: " << instance1.read() << std::endl;
            std::cout << "Instance 2 after modification: " << instance2.read() << std::endl;

            instance1.write("Hello from instance 1!");

            std::cout << "Instance 1 after modification: " << instance1.read() << std::endl;
            std::cout << "Instance 2 after modification by instance 1: " << instance2.read() << std::endl;

            instance2.detach();
        }

        instance1.destroy();
        std::cout << "Instance 1 destroyed shared memory segment." << std::endl;
    }

    return 0;
}
