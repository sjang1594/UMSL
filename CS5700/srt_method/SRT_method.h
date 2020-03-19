//These are the all functional prototypes that computes for SRT_method.

#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

//This structure is to determine when to end this algorithm.
//This is very important thing to know when to exit out the program.
struct Shift{
    int total_num_shift = 0;
};

//The Structure to store the delay and strings(normB), and shift.
//This Structure is to store the original B, which it is not normalized.
//This also has flag which it will help for printing the output of result

struct Srt{
    int delay;
    int shift;

    //Original B.
    string original_B;

    //Normalized B(2's complement of B)
    string str;

    //Checking bit
    string str1;

    int flag = 0;

};

//This function is to check whether it overflows or not.
string error_check(string , string );

//This function is to convert the one's complement and two's complement
string complement_converter(string );

//This function is to check whether the input string is binary or not
int binary_checker(string );

//This function is to convert hexadecimal to binary number
//First to check if it is binary number, then leave as it is
//If it is hexadecimal, convert it to binary number.
string Hextobinary(string );

//This function returns the structure of normalized string and delay time.
Srt norm(string ,Srt &);

//This function return the adjusted AQ
string adjustAQ(string, Srt &);

//This function return the adjusted AQ(by shifting of 0's)
string shiftAQ(string , Srt &, Shift &);

//This function return the adjusted AQ(by shifting of 1's)
string shiftAQ_ONE(string, Srt &, Shift &);

//This returns the string of 4 bits(half) of AQ.
string get_string(string );

//This function return the string values of result.
string srt_operation(string , string, Shift &, Srt &, Srt &);

//This function return the string after addition.
string add(string, string, Srt &);

string add_helper(string , string , Srt &);

//This function return the string after subtraction.
string subtract(string, string, Srt &);

//Output Function for Remainder
string print_remainder(string );

//void print_result(string, string, string, B &, Srt &);