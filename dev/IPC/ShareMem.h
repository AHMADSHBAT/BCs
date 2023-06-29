#ifndef IPC_MEMORY_SHARE_H
#define IPC_MEMORY_SHARE_H

class IPCMemoryShare {
public:
    IPCMemoryShare(int id, int size);

    bool create();
    bool attach();
    bool detach();
    bool destroy();

    void write(const char* message);
    const char* read();

private:
    int id_;
    int size_;
    int shmid_;
    void* data_;
};

#endif // IPC_MEMORY_SHARE_H
