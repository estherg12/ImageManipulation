#include "ElementQueue.hpp"

ElementQueue::ElementQueue()
{
    next=nullptr;
    pixel=nullptr;
}

ElementQueue::~ElementQueue()
{
}

ElementQueue::ElementQueue(Pixel* p)
{
    pixel = p;
    next=nullptr;
}

ElementQueue::ElementQueue(Pixel* p, ElementQueue* n)
{
    pixel=p;
    next=n;
}

Pixel* ElementQueue::getFresh()
{//creates and returns and instance/copy of the object RGBPixelXY stored in the ElemRGBPixelXY object
    return new Pixel(pixel->getX(),pixel->getY(),pixel->getR(),pixel->getG(),pixel->getB());
}

Pixel* ElementQueue::getPixel()
{
    return pixel;
}

ElementQueue* ElementQueue::getNext()
{
    return next;
}

void ElementQueue::setNext(ElementQueue* p_next)
{
    next=p_next;
}
