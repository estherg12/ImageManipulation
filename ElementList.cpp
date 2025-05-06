#include "ElementList.hpp"

ElementList::ElementList(Pixel* p, ElementList* n)
{
    this->pixel = p;
    this->next = n;
}

ElementList::ElementList()
{
    this->pixel = nullptr;
    this->next = nullptr;
}

ElementList::~ElementList()
{
}

Pixel* ElementList::getPixel()
{
    return pixel;
}

void ElementList::setPixel(Pixel* px)
{
    pixel = px;
}

ElementList* ElementList::getNext()
{
    return next;
}

void ElementList::setNext(ElementList* n)
{
    this->next = n;
}