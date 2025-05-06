#ifndef QUEUEPIXEL_HPP
#define QUEUEPIXEL_HPP
#include "ElementQueue.hpp"
#include "Pixel.hpp"
#include <iostream>
using namespace std;

class QueuePixel
{
    ElementQueue* front;
    ElementQueue* rear;
public:
    QueuePixel();
    ~QueuePixel();
    
    void enqueue(Pixel* p);
    Pixel* dequeue();
    Pixel* getFront();
    Pixel* getRear();
    void makenull();
    bool isEmpty();
    
};

#endif // QUEUEPIXEL_HPP
