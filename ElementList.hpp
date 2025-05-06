#ifndef ELEMENTLIST_HPP
#define ELEMENTLIST_HPP
#include "Pixel.hpp"

class ElementList
{
    Pixel* pixel;
    ElementList* next;
public:
    ElementList();
    ElementList(Pixel* p, ElementList* next);
    ~ElementList();
    
    Pixel* getPixel();
    void setPixel(Pixel* px);
    
    ElementList* getNext();
    void setNext(ElementList* p);

};

#endif // ELEMENTLIST_HPP
