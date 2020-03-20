/*
 * Name         : Seungho Jang
 * Course       : CS5700
 * Description  : SRT Division Algorithm
 */

#include "SRT_method.h"
using namespace std;

int main(int argc, char** argv) {
    Shift shift;
    Srt record;

    //Error Checking
    if (argc < 3) {
        cout << "------Help Message------" << endl;
        cout << "Please insert two inputs" << endl;
        cout << "1. Insert Dividend" << endl;
        cout << "2. Insert Divisor" << endl;
        return -1;
    }

    //First Argument is the Dividend
    //Second Argument is the Divisor
    string AQ = argv[1];
    string B = argv[2];

    //Check to see what is the AQ and B.
    cout << "The Input Argument is " << endl;
    cout << "AQ : " << AQ << "   " << "B :" << B << endl;

    //Need to convert Hexadecimal to Binary Number
    AQ = Hextobinary(AQ);
    B = Hextobinary(B);
    cout << "Convert it to Binary Number " << endl;
    cout << "AQ : " << AQ << "   " << "B : " << B << endl;

    //Store B into structure

    //Remove the "."
    AQ = AQ.substr(1, AQ.length());
    B = B.substr(1, B.length());

    //Compare the length of AQ and B
    AQ = error_check(AQ, B);

    cout << setw(10) << "The dividend length: " << AQ.length() << endl;
    cout << setw(10) << "The divisor length : " << B.length() << endl;

    //Struct Initialization
    record.delay = 0;
    shift.total_num_shift = 0;
    record.shift = 0;

    norm(B, record);
    cout << setw(10) << "----------------------------------------" << endl;
    cout << setw(10) << "AQ                    : " << "." << AQ.substr(0, AQ.length() / 2) << "  "
         << AQ.substr(AQ.length() / 2, AQ.length()) << endl;
    cout << setw(10) << "B                     : " << "." << B << endl;
    cout << setw(10) << "Normalized B          : " << "." << record.original_B << endl;
    cout << setw(10) << "2's Complement Norm B : " << record.str.substr(0,1) << "." << record.str.substr(1, record.str.length())<<endl;
    cout << setw(10) << "Delay Time : " << record.delay << "Δt" << endl;

    cout << setw(10) << "----------------------------------------" << endl;
    string adj_aq = AQ;
    adj_aq = adjustAQ(AQ, record);
    cout << setw(10) << "Adjusted AQ           : " << "." << AQ.substr(0, adj_aq.length() / 2) << "  "
         << AQ.substr(AQ.length() / 2, AQ.length()) << endl;
    cout << setw(10) << "Delay Time : " << record.delay << "Δt" << endl;
    AQ = adj_aq;

    adj_aq = shiftAQ(AQ, record, shift);
    AQ = adj_aq;
    string result;
    char pos_result = '0';

    string temp = record.original_B;

    //Loop until the shift is all used.
    while (shift.total_num_shift <= B.length()) {
        if (pos_result == '0') {
            result = subtract(AQ, temp, record);
        }
        else {
            result = add(AQ, temp, record);
        }

        //Negative Result
        if (result.substr(0, 1) == "1") {
            cout << setw(20) << "Negative Result        : " << result.substr(0, 1) << "."
                 << result.substr(1, result.length() / 2) << " "<< result.substr(result.length() / 2 + 1, result.length()) << endl;
            cout << setw(20) << "The Delay time         : " << record.delay << "Δt" << endl;
            cout << setw(20) << "----------------------------------------" << endl;
        }
        //Positive Result
        else {
            cout << setw(30) << "Positive Result        :" << result.substr(0, 1) << "." <<result.substr(1, result.length() / 2)
            << " " << result.substr(result.length() / 2 + 1, result.length())<< endl;
            cout << setw(20) << "The Delay time         : " << record.delay << "Δt" << endl;
            cout << setw(20) << "----------------------------------------" << endl;
        }

        pos_result = result[0];
        result = result.substr(1);

        //If it is positive result then,
        if (pos_result == '0') {
            result.push_back('1');
            result = result.substr(1);

            record.delay = record.delay + 3;
            shift.total_num_shift += 1;
            cout << setw(30) << "Shift AQ left         : " << "." << result.substr(0, result.length() / 2);

            cout << " "<< result.substr(result.length()/ 2, result.length()) << "q0 = 1" << endl;
            cout << setw(20) << "The Delay Time        : " << record.delay << "Δt" << endl;

            result = shiftAQ(result, record, shift);
            if (shift.total_num_shift > (int) result.length()/2) {
                AQ = result;
                break;
            }
            AQ = result;
        }
        //When result AQ is negative.
        else if (pos_result == '1') {
            result.push_back('0');
            result = result.substr(1);

            //Update Delay and Total number of shift.
            record.delay = record.delay + 3;
            shift.total_num_shift += 1;

            cout << setw(20) << "Shift AQ left          : " << "1" << "." << result.substr(0, result.length() / 2)
                 << " " << result.substr(result.length() / 2, result.length())<<setw(20) << "q0 = 0" << endl;
            cout << setw(20) << "The Delay Time         : " << record.delay << "Δt" << endl;

            result = shiftAQ_ONE(result, record, shift);
            if (shift.total_num_shift > (int) B.length()) {
                AQ = result;
                break;
            }
            AQ = result;
        }
    }

    //the result of A is = 1; this means that I have to correct the remainder.
    if (pos_result == '1') {
        string final_result = AQ.substr(AQ.length() / 2);
        string half_AQ = get_string(AQ.insert(0, "1"));
        string correct_string = half_AQ;
        correct_string = correct_string.substr(0, half_AQ.length() - 1);
        record.delay += 3;
        cout << setw(20) << "----Correction is required----" << endl;
        cout << setw(20) << "    Correct Remainder     : " << "1." << correct_string << endl;
        cout << setw(20) << "    The Delay Time        : " << record.delay << "Δt" << endl;
        cout << setw(20) << "    Shift A and Add B     : " << "0." << record.original_B << endl;
        correct_string = add_helper(correct_string, record.original_B, record);
        cout << setw(20) << "    SUM of A and B        : " << "0." << correct_string << endl;
        cout << setw(20) << "    The Delay Time        : " << record.delay << "Δt" << endl;

        record.flag = 1;
        string empty = " ";
        print_result(correct_string, final_result, empty, record);
    }
    //Correction does not required.
    else {
        record.flag = 0;
        string empty = " ", emtpy1 = " ";
        print_result(empty, emtpy1, AQ, record);
    }
    return 0;
}