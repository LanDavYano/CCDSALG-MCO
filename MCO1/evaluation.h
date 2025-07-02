#ifndef EVALUATION_H
#define EVALUATION_H
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

int charToInt(char singleDigit);
char intToChar(int singleDigit);
int stringToInt(char *multipleDigit);
int performOperation(int firstNumber, int secondNumber, char op);


#endif