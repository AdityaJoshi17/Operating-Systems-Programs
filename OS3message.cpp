#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <mqueue.h>

int main() {
    mqd_t mq;
    struct mq_attr attr;
    char buffer[1024];

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 1024;
    attr.mq_curmsgs = 0;

    mq = mq_open("/my_queue", O_CREAT | O_RDWR, 0644, &attr);

    if (mq == -1) {
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    std::cout << "Enter a message: ";
    std::cin.getline(buffer, sizeof(buffer)); // Using std::cin.getline to read a line of input

    mq_send(mq, buffer, strlen(buffer), 0);
    mq_receive(mq, buffer, sizeof(buffer), NULL);

    std::cout << "Received: " << buffer << std::endl;

    mq_close(mq);
    mq_unlink("/my_queue");

    return 0;
}
