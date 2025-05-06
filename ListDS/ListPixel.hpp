#ifndef LISTPIXEL_HPP
#define LISTPIXEL_HPP
#include "ElementList.hpp"
#include "Pixel.hpp"

class ListPixel
{
    ElementList* header;
public:
    ListPixel();
    ~ListPixel();
    
    void insert(Pixel* p, ElementList* e);
    void insertPos(Pixel* p, int pos);
    void insertFirst(Pixel* p);
    void insertLast(Pixel* p);
    
    void deleteP(ElementList* p);
    void deletePos(int pos);
    
    ElementList* locate(Pixel* p);//returns pointer
    int locatePos(Pixel* p);//returns position
    
    Pixel* retrieve(int pos);//returns item (pixel)
    
    ElementList* next(ElementList* p);
    ElementList* getPrev(ElementList* p);
    
    
    void makenull();
    bool empty();
    
    ElementList* findPosition(int pos);
    int getSize();//returns how many elements
    Pixel* getLast();//returns the last element
    ElementList* getHeader();
};

#endif // LISTPIXEL_HPP
