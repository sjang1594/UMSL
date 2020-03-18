/*
 * Name         : Seungho Jang
 * Course       : CS5700
 * Description  : SRT Division Algorithm
 */

#include <iostream>
#include <iomanip>
#include <string.h>
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

    //Check to see what is the AQ and B.
    cout<< AQ <<endl;
    cout<< B <<endl;

    //Need to convert Hexadecimal to Binary Number
    AQ = Hextobinary(AQ);
    B = Hextobinary(B);

    //Remove the "."
    AQ = AQ.substr(1, AQ.length());
    B = B.substr(1, B.length());

    //Compare the length of AQ and B
    AQ = error_check(AQ, B);

    cout<< setw(10) <<"The dividend length: "<<AQ.length()<<endl;
    cout<< setw(10) <<"The divisor length : "<<B.length()<<endl;

    cout<<B<<endl;

    //First Step : Normalize B.
    Srt record = norm(B);
    cout<< setw(10) << "The normalized B: "<<record.str<<endl;
    cout<< setw(10) << "The Delay time  : "<<record.delay<<"Δt"<<endl;

    //Second Step : Adjust AQ
    string adj_AQ = adjustAQ(AQ, record);
    cout<<setw(10) << "Adjusted AQ  : "<<adj_AQ<<endl;
    cout<<setw(10) << "The Delay time : "<<record.delay<<"Δt"<<endl;


    return 0;
}