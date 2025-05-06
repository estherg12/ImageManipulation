#include "StackOperations.hpp"

StackOperations::StackOperations()
{
    stackTop = nullptr; //initialize top to null
}

StackOperations::~StackOperations()
{
}

char StackOperations::pop()
{
    char v = ' ';
    if(!isEmpty())
    {
        ElementStack* aux;//pointer
        aux=stackTop;
        stackTop=stackTop->getNext(); //we change the top to the next pointer
        v=aux->getContent();//store the value in the next element
        delete (aux);
    }
    return v;
}

void StackOperations::push(char elem) //elem is the content of the data we want to store
{
    ElementStack* element = new ElementStack(elem, nullptr);
    if(!(isEmpty()))
    {
        element->setNext(stackTop);
    }
    stackTop = element;
}

bool StackOperations::isEmpty() //returns true if stack is empty, false otherwise
{
    return stackTop == nullptr;
}

void StackOperations::makenull()
{
    while (stackTop != nullptr) 
    {
        pop();
    }
}

char StackOperations::top()
{
    char result = ' ';
    if (!isEmpty())
    { //so that the top returns smt when the stack is empty
        result = stackTop->getContent();;
    }
    return result;
}
