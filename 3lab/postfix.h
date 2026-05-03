#ifndef POSTFIX_H
#define POSTFIX_H
#include "stack_list.h"
#include <cctype>

void checkParanthesesBalance(const char* infix){
    int balance = 0;
    for(int i = 0; infix[i] != '/0'; ++i){
        if(infix[i] == '(') balance++;
        else if(infix[i] == ')') balance--;
        if(balance < 0){
            throw std::runtime_error("Error: Unmatched closing paranthesis");
        }
    }
    if (balance != 0){
        throw std::runtime_error("Error: wrong parantheses balance");
    }
};

bool isOperator(char c){
    return c == '+' || c == '-' || c == '*' || c == '/';
};

void getPostfixFromInfix(const char* infix, char* postfix){
    StackList<char> operators;
    checkParanthesesBalance(infix);
    bool previousOperand = false;
    for(int i = 0; infix[i] != '\0'; ++i){
        char c = infix[i];
        if(std::isspace(c)) {
            continue;
        }
        if(isOperator(c) && !previousOperand){
            throw std::runtime_error("Error: Operator must go after operand");
        }
        
    }
};

#endif