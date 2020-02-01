// Author		: Seungho Jang
// Date			: 5/9/2019
// Description		: The concept : IPC
// 			: What 'mater' do is to get a command line argument option to put -h for help, -n for number. 
// 			: if -n is entered, then you will have a default set number as 100, otherwise put a number.
// 			: Then get the shared memory, fork the process, child processor will exec(execute) the worker.
// 			: If it's finished then, it should print out that shared memory, and set the shared memory eqaul to zero.

//Call all the library
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>

#define SHM_KEY 9527

int main(int argc, char*argv[]) {

    int flag, op;
    int number;
    int shmid;
    int *shmp;
    int status;

    flag = 0;
    while ((op = getopt(argc, argv, "hn:")) != -1) {
        switch (op) {
            case 'h':
                fprintf(stdout, "Usage 	: %s takes an arguments as following name\n", argv[0]);
		printf(stdout, "	: You are supposed to put an arguments -n/-h and number\n");
	        printf("		: -h, help [-n/-h] [number]\n");
                exit(EXIT_FAILURE);
            case 'n':
                flag = 1;
                //printf("The number conversion of argv[2] is %d\n", atoi(argv[2]));
                number = atoi(argv[2]);
                break;
            default:
                flag = 1;
                //Default to 100
                number = 100;
                //fprintf(stderr, "Usage : %s [-t nsecs] [-n] name\n", argv[0]);
                break;
        }
    }

    if (flag == 1) {

        shmid = shmget((key_t) SHM_KEY, sizeof(int), IPC_CREAT | 0664);
        printf("Master Output : Shared Memory ID is %d\n", shmid);

        //Error Checking for the shared memory key
        if (shmid == -1) {
            perror("Master Output : Error Occured while creating the shared memory\n");
            return 1;
        }

        //Get the shared memory Segment & Set to 0.
        shmp = (int *) shmat(shmid, NULL, 0);
        printf("Master Output : The shared memory set to %d\n", *shmp);
	    printf("Master Output : Argument(Number) that was passed into Master is %d\n", atoi(argv[2]));
	
        if (shmp == (int *) -1) {
            perror("Master Output : Error Occured while shared memory attach\n");
            return 1;
        }

        pid_t pid;
        int status;
        pid = fork();
        char pidStr[10];
        sprintf(pidStr, "%d", number);
	    printf("Master Output : Fork Started\n");

        //Error Checking for pid & Create Child Process
        if(pid == -1){
            perror("Fork Failed");
        }
        else if (pid == 0) {
            printf("Master Output : Child is executing the worker\n");
            char *argument[4] = {"./worker", "op", pidStr, NULL};
            execvp("./worker", argument);
            sleep(5);
            printf("Master Output : Child is Done or terminated");
        }
        //Parent Process
        else {
            printf("Master Output : Parent is waiting.. \n");
            waitpid(pid, &status, 0);
            printf("Master Output : The number passed from the worker is %d\n", *shmp);
            *shmp = 0;
            printf("Master Output : The number set to %d\n", *shmp);

            shmdt(shmp);

            if (shmctl(shmid, IPC_RMID, 0) == -1) {
                printf("Master Output : Failed to Erase shared memory\n");
            } else {
                printf("Master Output : Success to Erase shared memory\n");
            }

            if (WIFEXITED(status)) {
                printf("Master Output : The Program Terminated Normally\n");
            } else if (WIFSIGNALED(status)) {
                printf("Master Output : Signal Received\n");
                printf("Master Output : Signal Number %d\n", WTERMSIG(status));
            }
        }
        return 0;
    }
}
