#include "ElementDoubleList.hpp"

ElementDoubleList::ElementDoubleList()
{
    this->pixel = nullptr;
    this->next = nullptr;
    this->previous = nullptr;
}

ElementDoubleList::ElementDoubleList(Pixel* px, ElementDoubleList* n, ElementDoubleList* p)
{
    this->pixel = px;
    this->next = n;
    this->previous = p;
}

ElementDoubleList::~ElementDoubleList()
{
}

Pixel* ElementDoubleList::getPixel()
{
    return pixel;
}

void ElementDoubleList::setPixel(Pixel* px)
{
    pixel = px;
}

ElementDoubleList* ElementDoubleList::getNext()
{
    //cout<<"got to get next"<<endl;
    return next;
}

void ElementDoubleList::setNext(ElementDoubleList* p)
{
    next = p;
}

ElementDoubleList* ElementDoubleList::getPrev()
{
    return previous;
}

void ElementDoubleList::setPrev(ElementDoubleList* p)
{
    previous = p;
}
