#include "conversion.h"

const str256 operators[] = {"+", "-", "*", "/", "^", "%", "(", ")", 
    ">", "<", ">=", "<=", "==", "!=", "&&", "||", "!"};

int getNextToken(const char* input, int startPos, str256 token){
    int pos = startPos;
    int tokenIndex = 0;
    
    while (input[pos] == ' ' || input[pos] == '\t') {
        pos++; //I think this is not needed since nakalagay sa specs na valid yung input string without any whitespaces or whatnot
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
    return pos + 1; // Can be removed since it might take the unexpected characters as a valid input and hide the bugs
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
    } // can be removed since the open and close parenthesis are just used to signal if it is going to be popped or not
    
    return 0; 
}

bool hasHigherEqualPriority(str256 op1, str256 op2){
    return getPrecedence(op1) >= getPrecedence(op2); // Di ko ginamit so it can be removed
}

bool isLeftAssociative(str256 operator) {
    if (strcmp(operator, "^") == 0 || strcmp(operator, "!") == 0) {
        return false;
    }

    return true;
}

bool shouldPop(str256 oprtrFrmStck, str256 crntOprtr){
    // Check if top operator has higher or equal precedence to operator in tokens[]
    int crntOprtrPrecedence = getPrecedence(crntOprtr),
        oprtrFrmStckPrecedence = getPrecedence(oprtrFrmStck);

    if (oprtrFrmStckPrecedence > crntOprtrPrecedence){
        return true;
    }
    else if (oprtrFrmStckPrecedence == crntOprtrPrecedence && isLeftAssociative(crntOprtr)){
        return true;
    }

    return false;
}

bool readInput(str256 tokens[], int tokenCount, StackOperator *stckOprtrt, Queue *outputQueue){
    int i = 0;
    str256 top, temp;
    bool done, innerDone;

    while (tokens[i][0] != '\0' && i < tokenCount){
        if (isOperand(tokens[i])){
            // Process operand
            // Enqueue
            enqueue(outputQueue, tokens[i]);
        }
        else if (isOperator(tokens[i])){
            // Check precedence
            // Push into stack or enqueue 
            if (strcmp(tokens[i], "(") == 0)
            {
                pushOperator(stckOprtrt, tokens[i]);
            }
            else if (strcmp(tokens[i], ")") == 0){
                done = false;
                while (!StackOperatorEmpty(stckOprtrt) && !done){
                    topOperator(stckOprtrt, top);
                    if (strcmp(top, "(") == 0){
                        popOperator(stckOprtrt, temp);
                        done = true;
                    }
                    else{
                        popOperator(stckOprtrt, temp);
                        enqueue(outputQueue, temp);
                    }
                }
            }
            else{
                innerDone = false;
                while (!StackOperatorEmpty(stckOprtrt) && !innerDone){
                    topOperator(stckOprtrt, top);
                    if (isOperator(top) && shouldPop(top, tokens[i])){
                        popOperator(stckOprtrt, temp);
                        enqueue(outputQueue, temp);
                    }
                    else{
                        innerDone = true;
                    }
                }
                pushOperator(stckOprtrt, tokens[i]);
            }
        }
        i++;
    }

    while (!StackOperatorEmpty(stckOprtrt)){
        popOperator(stckOprtrt, temp);
        enqueue(outputQueue, temp);
    }
    return true;
}