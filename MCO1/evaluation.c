#include "evaluation.h"

int charToInt(char singleDigit)
{
    if (isdigit(singleDigit))
    {
        return singleDigit - '0';
    }

    return -1;
}

char intToChar(int singleDigit)
{
    if (singleDigit >= 0 && singleDigit <= 9)
    {
        return singleDigit + '0';
    }

    return -1; // Return -1 if the input is not a valid single digit
}

int stringToInt(char *multipleDigit)
{
    return atoi(multipleDigit);
}

int performOperation(int firstNumber, int secondNumber, char op) 
{
    switch (op) 
    {
        case '+':
            return firstNumber + secondNumber;
        case '-':
            return firstNumber - secondNumber;
        case '*':
            return firstNumber * secondNumber;
        case '/':
            if (secondNumber != 0) 
            {
                return firstNumber / secondNumber;
            } 
            else 
            {
                printf("Division by zero error!\n");
                return 0; 
            }
        case '^':
        {
            return (int)pow(firstNumber, secondNumber); // math.h
        }
        case '%':
            if (secondNumber != 0) 
            {
                return firstNumber % secondNumber;
            } 
            else 
            {
                return -1; 
            }
        default:
            return -1;
    }

    return -1;
}