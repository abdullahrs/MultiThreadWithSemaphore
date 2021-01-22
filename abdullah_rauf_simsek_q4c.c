#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

// Olusturulacak thread sayisi
#define thread_count 3

// Prosesleri uygun sirada cagirmak icin gerekli counter
int counter = 1;
// Thread arrayi
pthread_t threads[thread_count];
// Senkronizasyonu saglayan lock ve dongu degiskenini korumak icin
// gerekli lock
sem_t mutex, counter_mutex;
// Thread fonksiyonlari
void *threadA(void *data);
void *threadB(void *data);
void *threadC(void *data);
// Write ile yazdiran write fonksiyonu
void yazdir(char *data);

int main(int argc, char const *argv[])
{
    // Semaphore initialization'lari
    sem_init(&mutex, 1, 1);
    sem_init(&counter_mutex, 1, 1);
    // Thread olusturulmasi
    pthread_create(&threads[2], NULL, threadC, "C");
    pthread_create(&threads[1], NULL, threadB, "B");
    pthread_create(&threads[0], NULL, threadA, "A");
    // Thread'lerin joinlenmesi
    int i = 0;
    for (i; i < thread_count; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

void yazdir(char *data)
{
    int i = 0;
    for (i; i < 5; i++)
    {
        // STDOUT_FILENO degiskeni ile stdout'a yazabiliyoruz
        write(STDOUT_FILENO, data, strlen(data));
        sleep(1);
    }
}
void *threadA(void *d)
{
    // Tum blocklar isletilene kadar dongu calisiyor
    // Eger counter 10 olursa tum blocklar isletilmis olur
    while (counter < 10)
    {
        sem_wait(&mutex);
        sem_wait(&counter_mutex);

        if (counter == 1)
        {
            yazdir("A1");
            counter++;
        }

        if (counter == 4)
        {
            yazdir("A2");
            counter++;
        }

        if (counter == 7)
        {
            yazdir("A3");
            counter++;
        }

        sem_post(&counter_mutex);
        sem_post(&mutex);
    }
}
void *threadB(void *d)
{
    while (counter < 10)
    {
        sem_wait(&mutex);
        sem_wait(&counter_mutex);

        if (counter == 2)
        {
            yazdir("B1");
            counter++;
        }
        if (counter == 5)
        {
            yazdir("B2");
            counter++;
        }
        if (counter == 8)
        {
            yazdir("B3");
            counter++;
        }
        if (counter == 10)
        {
            yazdir("B4");
            counter++;
        }

        sem_post(&counter_mutex);
        sem_post(&mutex);
    }
}
void *threadC(void *d)
{
    while (counter < 10)
    {
        sem_wait(&mutex);
        sem_wait(&counter_mutex);
        if (counter == 3)
        {
            yazdir("C1");
            counter++;
        }
        if (counter == 6)
        {
            yazdir("C2");
            counter++;
        }
        if (counter == 9)
        {
            yazdir("C3");
            counter++;
        }

        sem_post(&counter_mutex);
        sem_post(&mutex);
    }
}
