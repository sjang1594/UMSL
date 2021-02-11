//Name          : Seungho Jang
//Date          : 4/8/2019
//Description   : The header files were modified and created from original front.h
//              : This header files is like menu where all the classes and token codes.

#ifndef FRONT_H_
#define FRONT_H_

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
//This is the token codes for the equal operation and the symbol codes for semi-colon
#define EQ_OP 27
#define SEMI_COL 28

int lex();

#endif /* FRONT_H_ */
