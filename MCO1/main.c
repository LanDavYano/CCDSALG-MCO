#include <stdio.h>
#include "conversion.h"

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
            printf("\n");
            // 
            // if (/*runEvaluationOfPostfix*/){
            //     // Process of Evaluation of Postfix
            // }

            // else{
            //     printf("Division by zero error!\n");
            // }
        }
    }

    
    
    return 0;
}