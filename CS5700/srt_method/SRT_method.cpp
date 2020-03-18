#include <iostream>
#include <string>
#include "SRT_method.h"

using namespace std;

//Check the overflow for the division.
string error_check(string a, string b){
    string new_string = "";

    //Check to see if length AQ is larger than B.
    if(a.length() < 2*b.length()){
        int compared_length = 2*b.length() - a.length();

        for(int i = 0; i < compared_length; i++){
            new_string = new_string.insert(0, "0");
        }
        new_string = new_string.append(a);
        return new_string;
    }
    //If not just print AQ.
    else
        return a;
}

//This is to check whether it is binary number.
//1 is the binary number, 0 is hexadecimal.
//The portion of code can be found in http://www.cplusplus.com/forum/general/54757/
bool binary_checker(string a){
    for (int i = 0 ; i < a.length(); i++){
        if(a.at(i)=='1' || a.at(i) == '0'){
            cout<<"This is Binary Number"<<endl;
            return true;
        }
        else{
            cout<<"This is not a Binary Number "<<endl;
            return false;
        }
    }

}

//Hexa Number to Binary Number.
string Hextobinary(string a) {
    int checker = binary_checker(a);
    //Binary Number
    string bNum = ".";

    //Check if input is binary Number
    if (checker) {
        return a.substr(0, a.length() - 8);
    }

    //The part of code was taken and modified from
    //https://www.geeksforgeeks.org/program-to-convert-hexadecimal-number-to-binary/
    for (int i = 1; i < a.length(); i++) {
        switch (a[i]) {
            case '0' :
                bNum = bNum.append("0000");
                break;
            case '1' :
                bNum = bNum.append("0001");
                break;
            case '2' :
                bNum = bNum.append("0010");
                break;
            case '3' :
                bNum = bNum.append("0011");
                break;
            case '4' :
                bNum = bNum.append("0100");
                break;
            case '5' :
                bNum = bNum.append("0101");
                break;
            case '6' :
                bNum = bNum.append("0110");
                break;
            case '7' :
                bNum = bNum.append("0111");
                break;
            case '8' :
                bNum = bNum.append("1000");
                break;
            case '9' :
                bNum = bNum.append("1001");
                break;
            case 'A':
                //case 'a':
                bNum = bNum.append("1010");
                break;
            case 'B':
                //case 'b':
                bNum = bNum.append("1011");
                break;
            case 'C':
                //case 'c':
                bNum = bNum.append("1100");
                break;
            case 'D':
                //case 'd':
                bNum = bNum.append("1101");
                break;
            case 'E':
                //case 'e':
                bNum = bNum.append("1110");
                break;
            case 'F':
                //case 'f':
                bNum = bNum.append("1111");
                break;
            default:
                cout << "\n Invalid Hexadecimal digit" << bNum[i];
                return 0;
        }
    }
    return bNum;
}

//Complement Converter
string complement_converter(string a){
    int i, length, carry_bit= 0;
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
                carry_bit = 1;
            }
        }
        else{
            if(carry_bit == 1 && b[i] == '0'){
                b[i] = '1';
                carry_bit = 0;
            }
            else if(carry_bit == 1 && b[i] == '1'){
                b[i] = '0';
                carry_bit =0;
            }
        }
    }
    b[length] = '\0';

    return b;
}

//This function returns the structure of normalized string and delay time.
Srt norm(string a){

    Srt record;
    int delay =0;
    string temp = a;
    int shift = 0;
    for(int i = 0; i < a.length(); i++){
        if(a[i] == '0'){
            temp.push_back('0');
            temp = temp.substr(1);
            shift++;
        }
        else
            break;
    }

    //update the #shift
    record.shift = shift;

    //Convert number to normalized number
    string temp1 = temp;
    string comp1 = complement_converter(temp1);

    //update that string
    record.str = comp1;

    //Count the delay
    delay = delay + shift * 3;
    delay = delay + a.length();

    //update that delay
    record.delay = delay;
    return record;
}

//This function returns the adjusted AQ, also updating the delay time when there is a shift
string adjustAQ(string a, Srt &record){
    int delay=0;
    string adjust_AQ = a;
    for(int i = 0; i < a.length(); i++){
        if(a[i] == '0' && record.shift > 0 ){
            adjust_AQ.push_back('*');
            adjust_AQ = adjust_AQ.substr(1);
            record.shift--;
            delay+=1;
        }
    }
    record.delay = record.delay + delay * 3;
    return adjust_AQ;
}