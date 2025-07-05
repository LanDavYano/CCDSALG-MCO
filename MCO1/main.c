#include <stdio.h>
#include "conversion.h"
#include "evaluation.h"

int main()
{
    str256 userInput = "", token = "";
    Queue postfixQueue;


    bool done = false;

    while (!done){
        scanf("%s", userInput);

        if (strcmp("QUIT", userInput) == 0){
            done = true;
        }

        else if (runInfixToPostfix(userInput, &postfixQueue)){
            while (!queueEmpty(&postfixQueue)){
                dequeue(&postfixQueue, token);
                printf("%s ", token);
            }
            if(!(hasZeroDivision(userInput, &postfixQueue))){
                int result = runPostfixtoEvaluation(userInput, &postfixQueue);
                if(result != -1) {
                    printf("\n%d\n", result);
                } else {
                    printf("\nError in evaluation\n");
                }
            }else{
                printf("\nDivision by zero error!\n");
            }
        }
    }

    
    
    return 0;
}