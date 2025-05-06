#ifndef ELEMENTSTACK_HPP
#define ELEMENTSTACK_HPP

class ElementStack
{
    char content;
    ElementStack* nextElem;
public:
    ElementStack();
    ElementStack(char x, ElementStack* next);
    ~ElementStack();
    
    ElementStack*getNext();
    void setContent(char c);
    char getContent();
    void setNext(ElementStack *p);

};

#endif // ELEMENTSTACK_HPP
