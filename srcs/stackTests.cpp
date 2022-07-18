#include <iostream>
#ifndef STD
#include "../includes/stack.hpp"
namespace opt=ft;
#else
#include <stack>
#include <deque>
namespace opt=std;
#endif

void popPushStack(void){
    opt::stack<int> stack1;
    std::cout << "created an empty stack" << std::endl;
    if (stack1.empty())
        std::cout << "stack1 is empty" << std::endl;
    std::cout << "stack1 size: " << stack1.size() << std::endl;
    std::cout << "adding 10 elements to stack1 using push" << std::endl;
    for(int i = 0; i < 10; i++)
        stack1.push(i);
    std::cout << "stack2 = stack1" << std::endl;
    opt::stack<int> stack2 = stack1;
    std::cout << "stack2 size: " << stack2.size() << std::endl;
    std::cout << "printing and removing all elements to stack2 using push" << std::endl;
    while (!stack2.empty()){
        std::cout << stack2.top() << std::endl;
        stack2.pop();
    }
    std::cout << "stack2 size: " << stack2.size() << std::endl;
}

void nonMemberstack(void){
    opt::stack<int> stack1;
    opt::stack<int> stack2;
    std::cout << "adding 10 elements from 0-9 to stack1 using push" << std::endl;
    for(int i = 0; i < 10; i++)
        stack1.push(i);
    std::cout << "adding 10 elements from 10-19 to stack1 using push" << std::endl;
    for(int i = 10; i < 20; i++)
        stack1.push(i);
    if (stack1 == stack2)
        std::cout << "stack1 == stack2" << std::endl;
    else 
        std::cout << "NOT TRUE: stack1 == stack2" << std::endl;
    if (stack1 != stack2)
        std::cout << "stack1 != stack2" << std::endl;
    else 
        std::cout << "NOT TRUE: stack1 != stack2" << std::endl;
    if (stack1 < stack2)
        std::cout << "stack1 < stack2" << std::endl;
    else 
        std::cout << "NOT TRUE: stack1 <= stack2" << std::endl;
    if (stack1 <= stack2)
        std::cout << "stack1 <= stack2" << std::endl;
    else 
        std::cout << "NOT TRUE: stack1 ,= stack2" << std::endl;
    if (stack1 > stack2)
        std::cout << "stack1 > stack2" << std::endl;
    else 
        std::cout << "NOT TRUE: stack1 > stack2" << std::endl;
     if (stack1 >= stack2)
        std::cout << "stack1 >= stack2" << std::endl;
    else 
        std::cout << "NOT TRUE: stack1 >= stack2" << std::endl;
    std::cout << "stack2 = stack1" << std::endl;
    stack2 = stack1;
    if (stack1 == stack2)
        std::cout << "stack1 == stack2" << std::endl;
    else 
        std::cout << "NOT TRUE: stack1 == stack2" << std::endl;
    if (stack1 != stack2)
        std::cout << "stack1 != stack2" << std::endl;
    else 
        std::cout << "NOT TRUE: stack1 != stack2" << std::endl;
    if (stack1 < stack2)
        std::cout << "stack1 < stack2" << std::endl;
    else 
        std::cout << "NOT TRUE: stack1 <= stack2" << std::endl;
    if (stack1 <= stack2)
        std::cout << "stack1 <= stack2" << std::endl;
    else 
        std::cout << "NOT TRUE: stack1 ,= stack2" << std::endl;
    if (stack1 > stack2)
        std::cout << "stack1 > stack2" << std::endl;
    else 
        std::cout << "NOT TRUE: stack1 > stack2" << std::endl;
     if (stack1 >= stack2)
        std::cout << "stack1 >= stack2" << std::endl;
    else 
        std::cout << "NOT TRUE: stack1 >= stack2" << std::endl;
    std::cout << "stack1.pop()" << std::endl;
    stack1.pop();
    if (stack1 == stack2)
        std::cout << "stack1 == stack2" << std::endl;
    else 
        std::cout << "NOT TRUE: stack1 == stack2" << std::endl;
    if (stack1 != stack2)
        std::cout << "stack1 != stack2" << std::endl;
    else 
        std::cout << "NOT TRUE: stack1 != stack2" << std::endl;
    if (stack1 < stack2)
        std::cout << "stack1 < stack2" << std::endl;
    else 
        std::cout << "NOT TRUE: stack1 <= stack2" << std::endl;
    if (stack1 <= stack2)
        std::cout << "stack1 <= stack2" << std::endl;
    else 
        std::cout << "NOT TRUE: stack1 ,= stack2" << std::endl;
    if (stack1 > stack2)
        std::cout << "stack1 > stack2" << std::endl;
    else 
        std::cout << "NOT TRUE: stack1 > stack2" << std::endl;
     if (stack1 >= stack2)
        std::cout << "stack1 >= stack2" << std::endl;
    else 
        std::cout << "NOT TRUE: stack1 >= stack2" << std::endl;
    std::cout << "stack2.pop() * 2" << std::endl;
    stack2.pop();
    stack2.pop();
    if (stack1 == stack2)
        std::cout << "stack1 == stack2" << std::endl;
    else 
        std::cout << "NOT TRUE: stack1 == stack2" << std::endl;
    if (stack1 != stack2)
        std::cout << "stack1 != stack2" << std::endl;
    else 
        std::cout << "NOT TRUE: stack1 != stack2" << std::endl;
    if (stack1 < stack2)
        std::cout << "stack1 < stack2" << std::endl;
    else 
        std::cout << "NOT TRUE: stack1 <= stack2" << std::endl;
    if (stack1 <= stack2)
        std::cout << "stack1 <= stack2" << std::endl;
    else 
        std::cout << "NOT TRUE: stack1 ,= stack2" << std::endl;
    if (stack1 > stack2)
        std::cout << "stack1 > stack2" << std::endl;
    else 
        std::cout << "NOT TRUE: stack1 > stack2" << std::endl;
     if (stack1 >= stack2)
        std::cout << "stack1 >= stack2" << std::endl;
    else 
        std::cout << "NOT TRUE: stack1 >= stack2" << std::endl;
}