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
pthread_t philos[count];
int state[count];

#define THINKING 0
#define HUNGRY 1
#define EATING 2

const char *philosophers[count] = {"Schopenhauer","Kant","Heidegger","Hume","Hegal"};
// think bubbles
const char *thinks[count] = {"Life","The Universe","Everything","Eternal Verities","Spaghettification"};

void* philosopher(void* );
void get_fork(int, int, int);

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

void get_fork(int phil, int f1, int f2)
{

    if(state[(phil+4)%count]!=EATING && state[(phil+1)%count]!=EATING && state[phil] == HUNGRY)
    {
        pthread_mutex_lock(&forks[(phil+4)%count]);
        pthread_mutex_lock(&forks[(phil+1)%count]);
        printf("Philosopher %s has got the forks.\n", philosophers[phil]);
        sleep(1);
        printf("Philosopher %s is now eating.\n", philosophers[phil]);
        sleep(1);
        printf("Philosopher %s has now released the forks.\n", philosophers[phil]);
        sleep(1);
        pthread_mutex_unlock(&forks[(phil+4)%count]);
        pthread_mutex_unlock(&forks[(phil+1)%count]);
        printf("Philosopher %s is now thinking about %s.\n", philosophers[phil], thinks[(rand())%count]);
        sleep(1);
    }
}

void* philosopher(void* i)
{
    int id, right_fork, left_fork;
    id = (int)i;

    state[id] = THINKING;
    printf("Philosopher %s is now thinking about %s.\n", philosophers[id], thinks[(rand())%count]);
    sleep(1);

    right_fork = (id+1)%count;
    left_fork = (id+(count-1))%count;
    for(;;)
    {

        get_fork(id, left_fork, right_fork);
        printf("Philosopher %s is now hungry.\n", philosophers[id]);
        sleep(1);
        state[id] = HUNGRY;
    }

    return NULL;


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
