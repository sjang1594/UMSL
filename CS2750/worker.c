// Author 		: Seungho Jang
// Date 		: 5/9/2019
// Description 		: From 'Master.c', the child execute the worker to find the closest prime number less than input argument
// 			: In order for me to do that, as same as 'master', I need to get the same process of creating shared memory as 
// 			: well as attaching the shared memory to the 'worker' process. 
// 			: Then attach that largest prime number into the shared memory. If the process is done, detach it.
// 			: Then master will terminate the child process. 

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

#define SHM_KEY 9527

//Function to find the closest prime number less than input argument
int LargestPrime(int TheNum){
    int FactorCount = 0;
    int i;
    int j;

    for (i = TheNum; i>=2; --i){
        for (j =2; j<i; ++j){
            if (i % j == 0){
                ++FactorCount;
            }
        }

        if(FactorCount == 0){
            return i;
            break;
        }
        FactorCount = 0;
    }
    return 0;
}


int main(int argc, char *argv[]){
    int shmid;
    int *shmp;
    int large_num;
    
    //Get the number that passed from the master.c
    int number = atoi(argv[2]);
    large_num = LargestPrime(number);
    printf("Worker Output : the number is passed %d\n", number);
    //printf("Worker Output : the prime number close to the number wheter the function works, %d\n", large_num);

    shmid = shmget((key_t)SHM_KEY, sizeof(int), IPC_CREAT|0664);
    printf("Worker Output : Shared Memory Id is %d\n", shmid);

    if(shmid == -1){
        perror("Worker Output : Error Occured while creating the shared memory\n");
        return 1;
    }

    shmp = (int*)shmat(shmid, NULL, 0);
    *shmp = 0;
    
    if(shmp == (int *) -1){
        perror("Worker Output : Error Occurred While shared memory attach\n");
        return 1;
    }

    if(*shmp != 0){
        perror("Worker Output : Error Occurred because the shared memory is not set to 0\n");
        return 1;
    }
    else{
        printf("Worker Output : Shared memory is %d\n", *shmp);
        shmp[0] = large_num;
        printf("Worker Output : The number is attached to shared memory with %d\n", *shmp);
    }
    //I was not understanding why I should put a while loop.
    shmdt(shmp);
    
    return 0;
}
