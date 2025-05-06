#ifndef ELEMENTDOUBLELIST_HPP
#define ELEMENTDOUBLELIST_HPP
#include "Pixel.hpp"
#include <iostream>
using namespace std;

class ElementDoubleList
{
    Pixel* pixel;
    ElementDoubleList* next;
    ElementDoubleList* previous;
public:
    ElementDoubleList();
    ElementDoubleList(Pixel* px, ElementDoubleList* n, ElementDoubleList* p);
    ~ElementDoubleList();

    void setPixel(Pixel* px);
    Pixel* getPixel();
    
    ElementDoubleList* getNext();
    void setNext(ElementDoubleList* p);
    
    ElementDoubleList* getPrev();
    void setPrev(ElementDoubleList* p);
};

#endif // ELEMENTDOUBLELIST_HPP
