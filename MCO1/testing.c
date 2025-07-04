#include "conversion.h"

int main()
{
    // test with any user input
    str256 input;
    str256 tokens[100];
    int pos = 0;
    printf("Enter an expression: ");
    scanf("%s", input);
    int tokenCount = tokenizeInput(input, tokens, 100);
    printf("Token count: %d\n", tokenCount);
    for (int i = 0; i < tokenCount; i++)
    {
        printf("Token at index %d: %s\n", i, tokens[i]);
    }
}