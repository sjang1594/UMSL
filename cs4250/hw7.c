#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000

void f1(){
        //Define the local array of char values
        char array1[SIZE];
        char array2[SIZE];
        //Static int n that increments the number of activation records
        static int n = 0;

        //Addr that stores the starting address of the array;
        long int addr1 = (long int)&array1[0];
	long int addr2 = (long int)&array2[0];
        if(n <= 10){
            printf("Call #%d\t\t at %p\n", n, &array1);
            addr1 = (long int)&array1[n];
	    addr2 = (long int)&array2[n];
            printf("AR Size \t #%d\t is %ld\n", n, ((addr1 - addr2)*sizeof(long int)));
            n++;
            f1();
        }
}

void f2(){
	//Define the local array of char values 
	char array1[SIZE];
	char array2[SIZE];
	static int n = 0;

	long int addr1 = (long int)&array1[0];
	long int addr2 = (long int)&array2[0];
	if(1){
	   printf("Call #%d\t\t at %p\n", n, &array1);
	   addr1 = (long int)&array1[n];
	   addr2 = (long int)&array2[n];
	   printf("AR Size \t #%d\t is %ld\n", n, ((addr1 - addr2)*sizeof(long int)));
	   n++;
	   f2();
        }
}

void f3(){
	char *array1;
	char *array2;
	array1 = malloc(sizeof(char)*SIZE);
	array2 = malloc(sizeof(char)*SIZE);
	static int n = 0;
	long int addr1 = (long int)&array1[0];
	printf("bytes %ld\n", (addr1*sizeof(long int)));
	long int addr2 = (long int)&array2[0];
	printf("bytes1 %ld\n", (addr2*sizeof(long int)));
	if(n <= 10){
	   printf("Call #%d\t\t at %p\n", n ,  &array1);
	   addr1 = (long int)&array1[n];
	   addr2 = (long int)&array2[n];
	   printf("AR Size \t #%d\t is %ld\n", n, ((addr1 - addr2)*sizeof(long int)));
	   n++;
	   free(array1);
	   free(array2);
	   f3();
	}
}

int main(){
    //f1();
    //f2();
    f3();
	return 0;
}
