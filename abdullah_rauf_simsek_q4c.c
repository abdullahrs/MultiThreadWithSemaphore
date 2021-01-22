#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

// Olusturulacak thread sayisi
#define thread_count 3
// Thread arrayi
pthread_t threads[thread_count];
// Senkronizasyonu saglayan lock ve dongu degiskenini korumak icin
// gerekli lock
sem_t mutex;
int mutex_counter;
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
    // Eger mutex_counter 10 olursa tum blocklar isletilmis olur
    while (mutex_counter < 10)
    {
        if (mutex_counter == 1)
        {
            yazdir("A1");
            sem_post(&mutex);
        }

        if (mutex_counter == 4)
        {
            yazdir("A2");
            sem_post(&mutex);
        }

        if (mutex_counter == 7)
        {
            yazdir("A3");
            sem_post(&mutex);
        }
        sem_getvalue(&mutex, &mutex_counter);
    }
}
void *threadB(void *d)
{
    // B4 degeri icin mutex_counter < 11 yapiyoruz.
    while (mutex_counter < 11)
    {
        if (mutex_counter == 2)
        {
            yazdir("B1");
            sem_post(&mutex);
        }
        if (mutex_counter == 5)
        {
            yazdir("B2");
            sem_post(&mutex);
        }
        if (mutex_counter == 8)
        {
            yazdir("B3");
            sem_post(&mutex);
        }
        if (mutex_counter == 10)
        {
            yazdir("B4");
            sem_post(&mutex);
        }
        sem_getvalue(&mutex, &mutex_counter);
    }
}
void *threadC(void *d)
{
    while (mutex_counter < 10)
    {
        if (mutex_counter == 3)
        {
            yazdir("C1");
            sem_post(&mutex);
        }
        if (mutex_counter == 6)
        {
            yazdir("C2");
            sem_post(&mutex);
        }
        if (mutex_counter == 9)
        {
            yazdir("C3");
            sem_post(&mutex);
        }
        sem_getvalue(&mutex, &mutex_counter);
    }
}
