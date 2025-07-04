#ifndef EVALUATION_H
#define EVALUATION_H
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "queue.h"
#include "stack.h"
#include "conversion.h"

int charToInt(char singleDigit);
char intToChar(int singleDigit);
int stringToInt(char *multipleDigit);
int performOperation(int firstNumber, int secondNumber, char op);
int evaluation(Queue *queue, str256 token, StackOperand *stack );

#endif