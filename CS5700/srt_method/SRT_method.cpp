#include <iostream>
#include <string>
#include "SRT_method.h"

using namespace std;

//Check the overflow for the division.
string error_check(string a, string b){
    int i = 0;
    string new_string = "";

    if(a.length() < 2*b.length()){
        int compared_length = 2*b.length() - a.length();

        for(i = 0; i < compared_length; i++){
            new_string = new_string.insert(0, "0");
        }
        new_string = new_string.append(a);
    }
    a = new_string;

    return a;
}


string complement_converter(string a){
    int i, length, check_bit= 0;
    char b[24];

    //Read the length of the string
    length = a.length();

    //If this is one's complement
    for(i=length-1; i>=0; i--){
        if(a[i] == '0')
            b[i] = '1';
        else
            b[i] = '0';
    }

    //If this is two's complement
    for(i=length-1; i>=0; i--){
        if(i==length-1){
            if(b[i] == '0')
                b[i] == '1';
            else{
                b[i] = '0';
                check_bit = 1;
            }
        }
        else{
            if(check_bit == 1 && b[i] == '0'){
                b[i] = '1';
                check_bit = 0;
            }
            else if(check_bit == 1 && b[i] == '1'){
                b[i] = '0';
                check_bit =0;
            }
        }
    }
    b[length] = '\0';

    return b;
}
