#include <iostream>
#include "stack_list.h"

int main(){
    StackList<int> stack1;
    stack1.push(1);
    stack1.push(5);
    stack1.push(1488);
    std::cout<<stack1.pop()<< " " << stack1.pop()<< " " << stack1.pop() << "\n";

    StackList<std::string> stack2;
    stack2.push("Ivan");
    stack2.push("Andrey");
    stack2.push("Evgen");
    try
    {
        std::cout<<stack2.pop()<<std::endl;
        std::cout<<stack2.pop()<<std::endl;
        std::cout<<stack2.pop()<<std::endl;
        std::cout<<stack2.pop()<<std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

}