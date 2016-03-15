#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <time.h>
int randGen(int *x, int *y, int *z, int *r);

char keypress;

#define count 5
int philosopherIndexes[]={0,1,2,3,4};
//diners
const char *philosophers[count] = {"Schopenhauer","Kant","Heidegger","Hume","Hegal"};
// think bubbles
const char *thinks[count] = {"Life","The Universe","Everything","Eternal Verities","Spaghettification"};

static pthread_mutex_t forks[count] = {
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER
};

static pthread_mutex_t screen[count] = {
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER
};

void* philosopher(void* i)
{
    int id;
    id = (int)i;

}

// simple control thread that allows us to exit the program
void *exit_thread(void *param) {
    for(;;){
        keypress=getchar();
        printf("%c",keypress);
        if(keypress=='q') {
            exit(0);
        }
    }
};
