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
/*int binary_checker(string a){
    if(a.at(a.length() -2 ) == '1'){
        return 1;
    }
    return 0;
}*/

//Hexa Number to Binary Number.
//Here is some error situation could happen when it comes to binary, then you have to switch the if statement back
string Hextobinary(string a) {
    //int checker = binary_checker(a);
    //Binary Number
    string bNum = ".";

    //Check if input is binary Number
    if(a.at(a.length() -2 ) == 'y') {
        return a.substr(0, a.length() - 8);
    }
    //You have to erase it if it is binary number otherwise it will throw an error
    if(a.at(a.length() -2 ) == '1'){
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
                carry_bit = 1;
            }
        }
    }
    b[length] = '\0';

    return b;
}

//This function returns the structure of normalized string and delay time.
Srt norm(string a, Srt &record){
    int length = a.length();
    int delay =0;
    string temp = a;
    int shift = 0;
    for(int i = 0; i < length; i++){
        if(a[i] == '0'){
            temp.push_back('0');
            temp = temp.substr(1);
            shift++;
        }
        else
            break;
    }
    //Store the normalized B.
    record.original_B = temp;

    //update the #shift
    record.shift = shift;

    //Convert number to normalized number
    string temp1 = temp;
    string comp1 = complement_converter(temp1.insert(0, "0"));
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
    int length = a.length();
    int delay=0;
    string adjust_AQ = a;
    for(int i = 0; i < length; i++){
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

//This function is to shift zeros by checking how many shift left
string shiftAQ(string a, Srt &record, Shift &shift){
    int length = a.length();
    int delay = 0;
    string str = a;
    int num_shift = 0;
    //Loop until it finds the '1'
    for(int i = 0; i < length; i++){
        int result_length = str.length()/2;
        if(shift.total_num_shift > result_length){
            break;
        }
        else if(a[i] == '0'){
            str.push_back('0');
            str = str.substr(1);
            shift.total_num_shift++;
            delay++;
            num_shift++;
        }
        else
            break;
    }
    //Increment the delay
    if(num_shift > 0) {
        record.delay = record.delay + delay * 3;
        cout << setw(20) << "Shift Over 0's        :" << " 0." << str.substr(0, str.length() / 2) << " " <<
             str.substr(str.length() / 2, str.length()) << endl;
        cout << setw(20) << "Delay Time            : " << record.delay << "Δt" << endl;
    }
    return str;
}

//This function is to shift ones by checking how many shift left
string shiftAQ_ONE(string a, Srt &record, Shift &shift){
    int length = a.length();
    int delay = 0;
    string str = a;
    int num_shift = 0;
    for(int i = 0; i < length; i++){
        int result_length = str.length()/2;
        if(shift.total_num_shift > result_length){
            break;
        }
        else if(a[i] == '1') {
            str.push_back('1');
            str = str.substr(1);
            shift.total_num_shift++;
            delay++;
            num_shift++;
        }
        else
            break;
    }
    if(num_shift > 0) {
        record.delay = record.delay + delay * 3;
        cout << setw(20) << "Shift Over 1's         :" << " 1." << str.substr(0, str.length() / 2) << " " <<
             str.substr(str.length() / 2, str.length()) << endl;
        cout << setw(20) << "The Delay Time         :" << record.delay << "Δt" << endl;
    }
    return str;
}

string add(string a, string b, Srt &record){
    string result = get_string(a.insert(0, "1"));
    result = add_helper(result, b.insert(0, "0"), record);
    cout<<setw(20) <<"Add B                  :"<<"."<<b.substr(1, b.length())<<endl;
    result = result.append(a.length()/2 + 1, a.length());
    return result;
}

//This function is to get a half of the string in register AQ.
string get_string(string a){
    return a.substr(0, a.length()/2 + 1);
}

//This function actually adding a numbers by checking each bit-wise of two strings.
string add_helper(string a, string b, Srt &record){
    string result;
    int carry_bit = 0;
    for(int i = a.length() -1; i >= 0 ; i--){
        if(a.at(i) == '*' || b.at(i) == '*'){
            result = result + '*';
            carry_bit = 0;
        }
        else{
            //Bit wise track the bit of each 4 bits in register
            //If do - '0' which is the ascii codecout<<b_comp.length()<<endl; 48, then 48 - 48 will become 0.
            //If do - '1' which is the ascii code 49, then 49 - 48 will leave as the character '1'
            int track_bitA = a.at(i) - '0';
            int track_bitB = b.at(i) - '0';

            //Using XOR gate to get the summation of bits together as following.
            //If sum_bit consist of 1, 0, 0, it will return as 1.
            //If sum_bit consist of 1, 1, 0, it will return as 0.
            //If sum_bit consist of 1, 1, 1, it will return as 1.
            int sum_bit = (track_bitA ^ track_bitB ^ carry_bit) + '0';

            //Then cast the ascii code back to character.
            result = (char)sum_bit + result;

            //Carry bit can be decided by looking at each bits, but design it such that
            //carry bit to be three 'and' gate and two 'or' gate at the last. (like full adder).
            carry_bit = (track_bitA & track_bitB) | (track_bitB & carry_bit) | (track_bitA & carry_bit);
        }
    }

    record.delay = record.delay + ((a.length()/2 - 1) * 2 + 6);
    return result;
}

//This function will be done in the first step after adjusting AQ.
//In order to subtract better, I insert 0 in the front, so that we can check
//how the operation(addition/subtraction) can be done for first 4 bits in A.
string subtract(string a, string b, Srt &record){
    string result = get_string(a.insert(0, "0"));
    string b_comp = complement_converter(b.insert(0, "0"));
    cout<< setw(10) <<"subtract B            : "<<b_comp.substr(0,1)<<"."<<b_comp.substr(1, b_comp.length())<<endl;
    cout<< setw(10) <<"----------------------------------------"<<endl;
    result = add_helper(result, b_comp, record);
    result = result.append(a.substr(a.length()/2 + 1, a.length()));
    return result;
}

//This is utility function for printing remainder.
string print_remainder(string a){
    int count = 0;
    int len = 2 * a.length();
    string Rem = "";
    for(int i = 0 ; i < len/2; i++){
        if(a[i] == '*')
            break;
        else
            Rem = Rem + a[i];
        count++;
    }

    string Zeros ="";
    for(int i = count; i < len; i++){
        Zeros.append("0");
    }

    Rem = Zeros.append(Rem);
    return Rem;
}

//This function returns the result of Quotient and Remainder.
void print_result(string a, string b, string c, Srt &record){
    if(record.flag == 1){
        cout << setw(10) << "<--Result Logs-->" << endl;
        cout << setw(10) << " Remainder " << "." << print_remainder(a) << endl;
        cout << setw(10) << " Quotient  " << "." << b << endl;
        cout << setw(10) << " Delay     " << record.delay << "Δt" << endl;
    }
    else{
        string remainder = print_remainder(c.substr(0, c.length()/2));
        cout << setw(10) << "<--Result Logs-->" << endl;
        cout << setw(10) << " Remainder " << "." << remainder <<endl;
        cout << setw(10) << " Quotient  " << "." << c.substr(c.length()/2, c.length())<<endl;
        cout << setw(10) << " Delay     " << record.delay << "Δt" << endl;
    }
}

//This function returns whether input string has overflow.
int overflow_checker(string a, string b){
    bool zeros = true;

    for(int i = 0; i < b.length(); i++){
        if(b[i] == '1'){
            zeros = false;
            break;
        }
    }
    if(zeros == true)
        return -1;

    string ovflow = a.substr(0, a.length()/2);
    if(a.compare(b) >= 0){
        return -2;
    }
    return 0;
}