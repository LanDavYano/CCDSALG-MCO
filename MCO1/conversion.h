#ifndef CONVERSION_H
#define CONVERSION_H
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"
#include "queue.h"


typedef char str256[257];

bool isOperator(str256 token);
bool isOperand(str256 token);
int getPrecedence(str256 operator);
bool hasHigherEqualPriority(str256 op1, str256 op2);
bool isLeftAssociative(str256 operator);
int getNextToken(const char* input, int startPos, str256 token);
int tokenizeInput(const char* input, str256 tokens[], int maxTokens);
bool readInput(str256 tokens[], int tokenCount);

#endif

