#include <iostream>
#include "stack_list.h"
#include "postfix.h"

int main(){

    char postfix[256];
    getPostfixFromInfix("( 1 + 2 )*(4+5)-6", postfix);
    std::cout<<postfix<<"\n";

}