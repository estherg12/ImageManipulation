#ifndef STACKOPERATIONS_HPP
#define STACKOPERATIONS_HPP
#include "ElementStack.hpp"

#include <iostream>
using namespace std;

class StackOperations
{
    ElementStack* stackTop;
public:
    StackOperations();
    ~StackOperations();
    
    bool isEmpty();
    void push(char elem);
    char pop();
    char top();
    void makenull();
};

#endif // STACKOPERATIONS_HPP
