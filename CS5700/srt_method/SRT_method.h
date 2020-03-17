//These are the all functional prototypes that computes for SRT_method.

#pragma once

using namespace std;

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
