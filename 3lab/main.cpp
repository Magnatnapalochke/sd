#include <iostream>
#include <cstring>
#include "queue_vector.h"
#include "postfix.h"
#include "stack_list.h"

void testStackList()
{
    std::cout << "=== StackList Test ===\n";
    StackList<int> s;
    
    s.push(10);
    s.push(20);
    s.push(30);
    
    std::cout << "Pop: " << s.pop() << " (expected 30)\n";
    std::cout << "Pop: " << s.pop() << " (expected 20)\n";
    std::cout << "Pop: " << s.pop() << " (expected 10)\n";
    std::cout << "Empty: " << (s.isEmpty() ? "Yes" : "No") << "\n\n";
    
    
    try {
        s.pop();
        std::cout << "ERROR: No exception\n";
    } catch (const StackUnderflow& e) {
        std::cout << "Exception caught: " << e.what() << "\n\n";
    }
}

void testQueueVector()
{
    std::cout << "=== QueueVector Test ===\n";
    QueueVector<int> q(2);
    
    q.enQueue(1);
    q.enQueue(2);
    q.enQueue(3); 
    
    std::cout << "Dequeue: " << q.deQueue() << " (expected 1)\n";
    std::cout << "Dequeue: " << q.deQueue() << " (expected 2)\n";
    std::cout << "Dequeue: " << q.deQueue() << " (expected 3)\n";
    std::cout << "Empty: " << (q.isEmpty() ? "Yes" : "No") << "\n\n";
    
    try {
        q.deQueue();
        std::cout << "ERROR: No exception\n";
    } catch (const QueueOverflow& e) {
        std::cout << "Exception caught: " << e.what() << "\n\n";
    }
}

void testPostfix()
{
    std::cout << "=== Postfix Test ===\n";
    
    const char* expr = "3+4*2";
    char result[100];
    
    getPostfixFromInfix(expr, result);
    std::cout << "Infix: " << expr << "\n";
    std::cout << "Postfix: " << result << " (expected: 342*+)\n";
    
    if (strcmp(result, "342*+") == 0)
        std::cout << "Result: PASS\n\n";
    else
        std::cout << "Result: FAIL\n\n";
    
    std::cout << "Error test (invalid expression):\n";
    try {
        getPostfixFromInfix("(3+4", result);
        std::cout << "ERROR: No exception\n";
    } catch (const std::runtime_error& e) {
        std::cout << "Exception caught: " << e.what() << "\n";
    }
}

int main()
{
    std::cout << "========== DATA STRUCTURES TEST ==========\n\n";
    
    testStackList();
    testQueueVector();
    testPostfix();
    
    std::cout << "\n========== TEST COMPLETE ==========\n";
    return 0;
}