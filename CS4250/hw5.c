//Name          : Seungho Jang
//Date          : 4/8/2019
//Description   : The code was modified from the front.c and front.h
//              : The assignment was to do read after the semi-colon until it hits null terminator.
//              : So the code that I changed from front.c is to put semi-colon and equal operator in lookup table.
//              : then do the same procedure as well as other arithmetic operation.
//              : also, update the header file, so that it can show the token number(27,28) and the operation name.
//              : Also, there is a part to skip the comment. if the first character found the / then second character *
//              : Then parse until the first character found the * and second character /. Then update the first character to
//              : read the rest of code. (I changed the variable next character to first character for readability.
//              : Input file is the following.
//              : /* comment */
//              : x=(sum+47)/total;

/* hw5.c - a lexical analyzer system for simple arithmetic expressions */

//Call the library that we need to reference.
#include <stdio.h>
#include <ctype.h>

#include "front.h"

/* Global Variable */
int nextToken;

/* Local Variables */
static int charClass;
static char lexeme [100];
static char firstChar;
static char secondChar;
static int lexLen;
static FILE *in_fp;

/* Local Function declarations */
static void addChar();
static void getChar();
static void getNonBlank();

/******************************************************/
/* main driver */
int main()
{
    /* Open the input data file and process its contents */
    if ((in_fp = fopen("input.txt", "r")) == NULL) {
        printf("ERROR - cannot open input.txt \n");
    } else {
        getChar();
        do {
            lex();
        } while (nextToken != EOF);
    }

    return 0;
}

/*****************************************************/
/* lookup - a function to lookup operators and parentheses and return the
 * token */

// this lookup function is important in this project because it has to recognize
// what symbols(operations) is used in the text file as well as reading that symbols and put it into array.
static int lookup(char ch) {
    switch (ch) {
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '+':
            addChar();
            nextToken = ADD_OP;
            break;
        case '-':
            addChar();
            nextToken = SUB_OP;
            break;
        case '*':
            addChar();
            nextToken = MULT_OP;
            break;

        //This portion is indicating that equal operation is used in this case
        case '=':
            addChar();
            nextToken = EQ_OP;
            break;
        //This portion is indicating that semi-colon symbol is used in this case.
        case ';':
            addChar();
            nextToken = SEMI_COL;
            break;

        case '/':
            addChar();
            nextToken = DIV_OP;
            break;

        default:
            addChar();
            nextToken = EOF;
            break;
    }
    return nextToken;
}

/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
static void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = firstChar;
        lexeme[lexLen] = 0;
    } else {
        printf("Error - lexeme is too long \n");
    }
}

/*****************************************************/
//This part is important part to skip the comments.
static void getChar() {
    if ((firstChar = getc(in_fp)) != EOF) {

    //find the first character and make a second character to read second one.
    if (firstChar == '/'){
        secondChar = getc(in_fp);

    if(secondChar == '*'){
        //go to while loop to check the */ in the comment
        while(1){

        secondChar = getc(in_fp);
        //if it found then break
        if(firstChar == '*' && secondChar == '/'){
        break;}

        //then make the first character to second character to swap.
        firstChar = secondChar;
        }
    }
    //then update that first character to read other code.
    firstChar = getc(in_fp);
    }
        if (isalpha(firstChar))
            charClass = LETTER;
        else if (isdigit(firstChar))
            charClass = DIGIT;
        else charClass = UNKNOWN;
    }
    else {
        charClass = EOF;
    }
}

/*****************************************************/
/* getNonBlank - a function to call getChar until it returns a non-whitespace
 * character */
static void getNonBlank() {
    while (isspace(firstChar)) getChar();
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic expressions */
int lex() {
    lexLen = 0;
    getNonBlank();

    switch (charClass) {
        /* Parse identifiers */
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = IDENT;
            break;

        /* Parse integer literals */
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = INT_LIT;
            break;

        /* Parentheses operator, and comma */
        case UNKNOWN:
            lookup(firstChar);
            getChar();
            break;

        /* EOF */
        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
    } /* End of switch */

    printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
    return nextToken;
} /* End of function lex */
