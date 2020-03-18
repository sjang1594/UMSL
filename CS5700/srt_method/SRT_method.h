//These are the all functional prototypes that computes for SRT_method.

#pragma once
#include <string>
using namespace std;

//The Structure to store the delay and strings.
struct Srt{
    int delay;
    int shift;
    string str;
};

//This function is to check whether it overflows or not.
string error_check(string , string );

//This function is to convert the one's complement and two's complement
string complement_converter(string );

//This function is to check whether the input string is binary or not
bool binary_checker(string );

//This function is to convert hexadecimal to binary number
//First to check if it is binary number, then leave as it is
//If it is hexadecimal, convert it to binary number.
string Hextobinary(string );

//This function returns the structure of normalized string and delay time.
Srt norm(string );

//This function return the adjusted AQ
string adjustAQ(string, Srt &);
