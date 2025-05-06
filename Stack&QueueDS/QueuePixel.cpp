#include "QueuePixel.hpp"

QueuePixel::QueuePixel()
{
    front = nullptr;
    rear = nullptr;
}

QueuePixel::~QueuePixel()
{
    makenull();
}

void QueuePixel::enqueue(Pixel* elem)
{
    ElementQueue* element = new ElementQueue(elem, nullptr);
    if(isEmpty())
    {
        front = element;
        rear = element;
    }
    else
    {
        rear->setNext(element);
        rear=element;
    }
}

Pixel* QueuePixel::dequeue()
{
    Pixel* result = nullptr;
    if(!isEmpty())
    {
        ElementQueue* aux = front;
        Pixel* auxp = front->getPixel();
        front = front->getNext();
        
        delete(aux);
        
        if(front==nullptr)
        {
            rear=nullptr;
        }
        
        result = auxp;
    }
    return result;
}

Pixel* QueuePixel::getFront()
{
    Pixel* result = nullptr;
    if(!isEmpty())
    {
        result= front->getPixel();
    }
    return result;
}

Pixel* QueuePixel::getRear()
{
    Pixel* result = nullptr;
    if(!isEmpty())
    {
        result = rear->getPixel();
    }
    return result;
}

void QueuePixel::makenull()
{
    while(front!=nullptr)
    {
        dequeue();
    }
}

bool QueuePixel::isEmpty()
{
    return front == nullptr;
}