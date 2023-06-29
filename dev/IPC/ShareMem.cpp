#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "ShareMem.h"
#include "ShareMem.h"

IPCMemoryShare::IPCMemoryShare(int id, int size) : id_(id), size_(size), shmid_(-1), data_(nullptr) {}

bool IPCMemoryShare::create() {
    shmid_ = shmget(id_, size_, IPC_CREAT | 0666);
    if (shmid_ == -1) {
        std::cerr << "Failed to create shared memory segment." << std::endl;
        return false;
    }

    data_ = shmat(shmid_, nullptr, 0);
    if (data_ == (void*)-1) {
        std::cerr << "Failed to attach shared memory segment." << std::endl;
        return false;
    }

    std::memset(data_, 0, size_);

    return true;
}

bool IPCMemoryShare::attach() {
    shmid_ = shmget(id_, size_, 0666);
    if (shmid_ == -1) {
        std::cerr << "Failed to access shared memory segment." << std::endl;
        return false;
    }

    data_ = shmat(shmid_, nullptr, 0);
    if (data_ == (void*)-1) {
        std::cerr << "Failed to attach shared memory segment." << std::endl;
        return false;
    }

    return true;
}

bool IPCMemoryShare::detach() {
    if (shmdt(data_) == -1) {
        std::cerr << "Failed to detach shared memory segment." << std::endl;
        return false;
    }

    return true;
}

bool IPCMemoryShare::destroy() {
    if (shmctl(shmid_, IPC_RMID, nullptr) == -1) {
        std::cerr << "Failed to destroy shared memory segment." << std::endl;
        return false;
    }

    return true;
}

void IPCMemoryShare::write(const char* message) {
    std::strcpy(reinterpret_cast<char*>(data_), message);
}

const char* IPCMemoryShare::read() {
    return reinterpret_cast<const char*>(data_);
}

