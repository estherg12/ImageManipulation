#ifndef DOUBLELISTPIXEL_HPP
#define DOUBLELISTPIXEL_HPP
#include "ElementDoubleList.hpp"

class DoubleListPixel
{
    ElementDoubleList* header;
public:
    DoubleListPixel();
    ~DoubleListPixel();
    
    void insert(Pixel* p, ElementDoubleList* e);
    void insertPos(Pixel* p, int pos);
    void insertFirst(Pixel* p);
    void insertLast(Pixel* p);
    
    void deleteP(ElementDoubleList* p);
    void deletePos(int pos);
    
    ElementDoubleList* locate(Pixel* p);
    int locatePos(Pixel* p);
    
    Pixel* retrievePx(int pos);
    ElementDoubleList* retrieve(int pos);
    
    ElementDoubleList* next(ElementDoubleList* p);
    ElementDoubleList* previous(ElementDoubleList* p);
    
    void makenull();
    bool empty();
    
    ElementDoubleList* findPosition(int pos);
    int getSize();
    ElementDoubleList* getLast();
    ElementDoubleList* getHeader();
};

#endif // DOUBLELISTPIXEL_HPP
