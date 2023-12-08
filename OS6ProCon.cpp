#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5 // Size of the shared buffer

int buffer[BUFFER_SIZE]; // Shared buffer
sem_t empty, full;        // Semaphores for empty and full slots in the buffer
pthread_mutex_t mutex;    // Mutex for buffer access
int in = 0;               // Index for adding data to the buffer
int out = 0;              // Index for removing data from the buffer

void *producer(void *arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        item = rand() % 100; // Generate a random item
        sem_wait(&empty);     // Wait for an empty slot in the buffer
        pthread_mutex_lock(&mutex); // Lock the buffer
        buffer[in] = item;           // Add item to the buffer
        std::cout << "Producer produced item " << item << std::endl;
        in = (in + 1) % BUFFER_SIZE; // Update the index
        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&full);               // Signal that a slot is full
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item;
    for (int i = 0; i < 10; i++) {
        sem_wait(&full);            // Wait for a full slot in the buffer
        pthread_mutex_lock(&mutex); // Lock the buffer
        item = buffer[out];         // Remove item from the buffer
        std::cout << "Consumer consumed item " << item << std::endl;
        out = (out + 1) % BUFFER_SIZE; // Update the index
        pthread_mutex_unlock(&mutex);  // Unlock the buffer
        sem_post(&empty);               // Signal that a slot is empty
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);            // Initialize the full semaphore
    pthread_mutex_init(&mutex, NULL); // Initialize the mutex

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
