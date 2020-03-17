/*
 * Name         : Seungho Jang
 * Course       : CS5700
 * Description  : SRT Division Algorithm
 */

#include <iostream>
#include <iomanip>
#include "SRT_method.h"
using namespace std;

//To record the number of shift
int total_num_shift = 0;

string QUOTIENT, REMAINDER;

int main(int argc, char** argv){
    //Error Checking
    if(argc < 3){
        cout << "------Help Message------"<<endl;
        cout << "Please insert two inputs"<<endl;
        cout << "1. Insert Dividend"<<endl;
        cout << "2. Insert Divisor"<<endl;
        return -1;
    }
    //First Argument is the Dividend
    //Second Argument is the Divisor
    string AQ = argv[1];
    string B = argv[2];

    cout<< AQ <<endl;
    cout<< B <<endl;

    //Remove the "."
    AQ = AQ.substr(1, AQ.length());
    B = B.substr(1, B.length());

    cout<< AQ <<endl;
    cout<< B <<endl;

    //Check how many shifts should be done.
    AQ = error_check(AQ, B);
    cout << AQ << endl;
    cout<< setw(10) <<"The dividend length: "<<AQ.length()<<endl;
    cout<< setw(10) <<"The divisor length : "<<B.length()<<endl;



    return 0;
}