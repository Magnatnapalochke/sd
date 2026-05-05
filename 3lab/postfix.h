#ifndef POSTFIX_H
#define POSTFIX_H
#include "stack_list.h"
#include <cctype>

void checkParanthesesBalance(const char* infix){
    int balance = 0;
    for(int i = 0; infix[i] != '\0'; ++i){
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

int getPriority(char op){
    switch(op){
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        default: return 0;
    }

}

bool isOperator(char c){
    return c == '+' || c == '-' || c == '*' || c == '/';
};

void getPostfixFromInfix(const char* infix, char* postfix){
    StackList<char> operators;
    checkParanthesesBalance(infix);
    bool expectOperand = true;
    int postfixIndex = 0;
    for(int i = 0; infix[i] != '\0'; ++i){
        char c = infix[i];
        if(std::isspace(c)) {
            continue;
        }
        if(c == '('){
            if(!expectOperand){
                throw std::runtime_error("Error: parantheses can't go after operand");
            }
            operators.push(c);
            expectOperand = true;
        }
        else if (c == ')'){
            if (expectOperand){
                throw std::runtime_error("Error: closing parantheses can't go after operator");
            }
            char op = operators.pop();
            while (op != '('){
                postfix[postfixIndex++]= op;
                op = operators.pop();
            }
        }
        else if(isOperator(c)){
            if(expectOperand){
                throw std::runtime_error("Error: Operator must go after operand");
            }
            expectOperand = true;
            while (!operators.isEmpty() && operators.top()!= '('
            && (getPriority(operators.top())>=getPriority(c))){
                postfix[postfixIndex++]= operators.pop();
            }
            operators.push(c);
        }
        else{
            if(!expectOperand){
                throw std::runtime_error("Error: Operand cannot go after another operand");
            }
            postfix[postfixIndex++]= c;
            expectOperand = false;
        }
        
        
    }
    while (!operators.isEmpty()){
        postfix[postfixIndex++]= operators.pop();
    }
    postfix[postfixIndex]= '\0';
};

#endif