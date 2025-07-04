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

int evaluation(Queue *queue, str256 token){

    //local stack OPERAND 
    StackOperand stackOperand;
    createStackOperator(stackOperand);

    //dequeing and putting into STACK
    if(dequeue(queue, token)){

        for(int i=0;i<token.length;i++){

            int flagFound = false;

            //check if it is an operator
            while(operators && flagFound == false){
                if(operators[i] == token[i]){
                    flagFound = true;
                }
                int i++;
            }

            if(flagFound == true){

                //pop pop from the stack
                //then evaluate if numbers in stack is 2 or more
                //if it is then evaluate the expression then push to stack
                bool first_pop = popOperand(stackOperand, token[i]);
                bool second_pop = popOperand(stackOperand, token[i+1]);

                if(first_pop && second_pop){

                    int left_number = stackOperand[i];
                    int right_number = stackOperand[i+1];
                    char current_op = token[i];
                    char curr_result[20];  // Make sure it's large enough
                    sprintf(curr_result, "%d%c%d", left_number, current_op, right_number);
                    pushOperand(stackOperand,curr_result);
                }

            }else{
                //push to stack
                int push_num = charToInt(token[i]);
                pushOperand(stackOperand, push_num);
            }
        }
    }
}