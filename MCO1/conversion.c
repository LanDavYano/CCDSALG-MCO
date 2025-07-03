#include "conversion.h"


const str256 operators[] = {"+", "-", "*", "/", "^", "%", "(", ")", 
    ">", "<", ">=", "<=", "==", "!=", "&&", "||", "!"};

int getNextToken(const char* input, int startPos, str256 token){
    int pos = startPos;
    int tokenIndex = 0;
    
    while (input[pos] == ' ' || input[pos] == '\t') {
        pos++;
    }
    
    if (input[pos] == '\0') {
        token[0] = '\0';
        return pos;
    }
    
    if (input[pos] == '>' && input[pos + 1] == '=') {
        strcpy(token, ">=");
        return pos + 2;
    }
    else if (input[pos] == '<' && input[pos + 1] == '=') {
        strcpy(token, "<=");
        return pos + 2;
    }
    else if (input[pos] == '=' && input[pos + 1] == '=') {
        strcpy(token, "==");
        return pos + 2;
    }
    else if (input[pos] == '!' && input[pos + 1] == '=') {
        strcpy(token, "!=");
        return pos + 2;
    }
    else if (input[pos] == '&' && input[pos + 1] == '&') {
        strcpy(token, "&&");
        return pos + 2;
    }
    else if (input[pos] == '|' && input[pos + 1] == '|') {
        strcpy(token, "||");
        return pos + 2;
    }

    else if (input[pos] == '+' || input[pos] == '-' || input[pos] == '*' || 
             input[pos] == '/' || input[pos] == '%' || input[pos] == '^' ||
             input[pos] == '(' || input[pos] == ')' || input[pos] == '>' ||
             input[pos] == '<' || input[pos] == '!' || input[pos] == '=') {
        token[0] = input[pos];
        token[1] = '\0';
        return pos + 1;
    }

    else if (isdigit(input[pos])) {
        while (isdigit(input[pos])) {
            token[tokenIndex++] = input[pos++];
        }
        token[tokenIndex] = '\0';
        return pos;
    }
    
    token[0] = input[pos];
    token[1] = '\0';
    return pos + 1;
}

int tokenizeInput(const char* input, str256 tokens[], int maxTokens){
    int pos = 0;
    int tokenCount = 0;
    
    while (input[pos] != '\0' && tokenCount < maxTokens) {
        pos = getNextToken(input, pos, tokens[tokenCount]);
        if (tokens[tokenCount][0] != '\0') { 
            tokenCount++;
        }
    }
    
    return tokenCount;
}

bool isOperator(str256 token){
    for (int i = 0; i < sizeof(operators) / sizeof(operators[0]); i++)
    {
        if (strcmp(token, operators[i]) == 0)
        {
            return true;
        }
    }
    return false;
}
bool isOperand(str256 token)
{
    return (token[0] >= '0' && token[0] <= '9');
}

int getPrecedence(str256 operator){
    if (strcmp(operator, "!") == 0 ||
        strcmp(operator, "&&") == 0 ||
        strcmp(operator, "||") == 0)
    {
        return 1;
    }
    else if (strcmp(operator, ">") == 0 ||
             strcmp(operator, "<") == 0 ||
             strcmp(operator, ">=") == 0 ||
             strcmp(operator, "<=") == 0 ||
             strcmp(operator, "==") == 0 ||
             strcmp(operator, "!=") == 0)
    {
        return 2;
    }
    else if (strcmp(operator, "+") == 0 ||
             strcmp(operator, "-") == 0)
    {
        return 3;
    }
    else if (strcmp(operator, "*") == 0 ||
             strcmp(operator, "/") == 0 ||
             strcmp(operator, "%") == 0)
    {
        return 4;
    }
    else if (strcmp(operator, "^") == 0)
    {
        return 5;
    }
    else if (strcmp(operator, "(") == 0 || strcmp(operator, ")") == 0)
    {
        return 6; 
    }
    
    return 0; 
}

bool hasHigherEqualPriority(str256 op1, str256 op2){
    return getPrecedence(op1) >= getPrecedence(op2);
}

bool isLeftAssociative(str256 operator) {
    if (strcmp(operator, "^") == 0 || strcmp(operator, "!") == 0) {
        return false;
    }

    return true;
}

bool shouldPop(){
    // Check if top operator has higher or equal precedence to operator in tokens[]
}

bool readInput(str256 tokens[], int tokenCount){
    int i = 0;
    while (tokens[i][0] != '\0' && i < tokenCount){
        if (isOperator(tokens[i])){
            // Check precedence
            // Push into stack or enqueue
        }
        else if (isOperand(tokens[i])){
            // Process operand
            // Enqueue 
        }
        i++;
    }
    return true;
}
