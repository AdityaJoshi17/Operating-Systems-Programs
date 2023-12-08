#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    char *shared_memory = (char *)shmat(shmid, nullptr, 0);

    std::cout << "Write data to shared memory: ";
    std::cin.getline(shared_memory, 1024); // Using std::cin.getline to read a line of input

    std::cout << "Data written to shared memory: " << shared_memory << std::endl;

    shmdt(shared_memory);

    return 0;
}
