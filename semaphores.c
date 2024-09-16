#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

/*  Implement a program in concurrent C language using Pthreads and semaphores that creates three threads:
    ● The first thread loops indefinitely, and for each iteration, it generates an atom of Chlorine (Cl) in a time
    range varying from 0 to 5 seconds; then it waits for the finish of the task of the third thread.
    ● The second thread loops indefinitely, and for each iteration, it generates an atom of Sodium (Na) in a
    time range varying from 0 to 5 seconds; then it waits for the finish of the task of the third thread.
    ● The third thread produces a sodium chloride molecule (NaCl) whenever a Sodium (Na) atom and a
    Chlorine (Cl) atom are available. Once the molecule is generated, it allows the entire process to
    repeat/restart.
    The random wait can be obtained with the following function sleep(rand()%6).
    Once a molecule of NaCl is created, the entire process restarts.
    Simulate the generation of the Na and Cl atoms, and of the NaCl molecule by printing the strings “Na”, “Cl” and
    “NaCl” when they are generated.
*/

sem_t s1, s2, s3;

void* tA (void *arg) {
    while (1) {
        sem_wait(&s1);
        sleep(rand()%6);
        printf("Cl\n");
        sem_post(&s3);
    }
    return NULL;
}
void* tB (void *arg) {
    while (1) {
        sem_wait(&s2);
        sleep(rand()%6);
        printf("Na\n");
        sem_post(&s3);
    }
    return NULL;
}
void* tC (void *arg) {
    while (1) {
        sem_wait(&s3);
        sem_wait(&s3);
        printf("NaCl\n");
        sem_post(&s1);
        sem_post(&s2);
    }
    return NULL;
}

int main () {
    sem_init(&s1, 0, 1);
    sem_init(&s2, 0, 1);
    sem_init(&s3, 0, 0);
    
    pthread_t t1,t2,t3;
    
    pthread_create(&t1, NULL, tA, NULL);
    pthread_create(&t2, NULL, tB, NULL);
    pthread_create(&t3, NULL, tC, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    sem_destroy(&s1);
    sem_destroy(&s2);
    sem_destroy(&s3);

    return 0;
}
