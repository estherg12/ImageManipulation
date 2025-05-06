#include "ElementStack.hpp"

ElementStack::ElementStack()
{
}

ElementStack::~ElementStack()
{
}

ElementStack::ElementStack(char content, ElementStack* nextElem)
{
    this->content = content;
    this->nextElem = nextElem;
}

//Getters & Setters
ElementStack* ElementStack::getNext()
{
    return nextElem;
}

char ElementStack::getContent()
{
    return content;
}

void ElementStack::setNext(ElementStack *p)
{
    nextElem=p;
}