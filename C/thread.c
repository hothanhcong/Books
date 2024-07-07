#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h> 

//share memory each other

int x = 0;
void *myThreadFun(void *vargp) 
{ 
    x += 5;
    sleep(1); 
    printf("Printing GeeksQuiz from Thread x= %d\n", x); 
    return NULL; 
}

void *myThreadFun2 (void *vargp) 
{ 
    sleep(1); 
    printf("Printing GeeksQuiz from x= %d\n", x); 
    return NULL; 
} 

   
int main() 
{ 
    pthread_t thread_id, thread_id2; 
    printf("Before Thread\n"); 
    pthread_create(&thread_id, NULL, myThreadFun, NULL); 
    pthread_create(&thread_id2, NULL, myThreadFun2, NULL); 
    pthread_join(thread_id, NULL); 
    pthread_join(thread_id2, NULL); 
    printf("After Thread\n"); 
    exit(0); 
}