#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define thread_count  3

pthread_t threads[thread_count];

void *threadA(void *data);
void *threadB(void *data);
void *threadC(void *data);
void yazdir(char *data);

int main(int argc, char const *argv[])
{
    pthread_create(&threads[0],NULL,threadA,"A");
    pthread_create(&threads[1],NULL,threadB,"B");
    pthread_create(&threads[2],NULL,threadC,"C");
    
    int i = 0;
    for ( i ; i < thread_count; i++)
    {
        pthread_join(threads[i],NULL);
    }

    return 0;
}

void yazdir(char *data){
    int i = 0;
    for(i;i<5;i++){
        write(STDOUT_FILENO,data,strlen(data));
        sleep(3);
    }
}

void *threadA(void *d){
    yazdir("A1");

    yazdir("A2");

    yazdir("A3");
}
void *threadB(void *d){
    yazdir("B1");

    yazdir("B2");

    yazdir("B3");

    yazdir("B4");
}
void *threadC(void *d){
    yazdir("C1");

    yazdir("C2");

    yazdir("C3");
}
