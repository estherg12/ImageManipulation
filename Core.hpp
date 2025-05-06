#ifndef CORE_HPP
#define CORE_HPP
#include <string>
using std::string;

#include "Image.hpp"
#include "StackOperations.hpp"
#include "QueuePixel.hpp"
#include "ListPixel.hpp"
#include "DoubleListPixel.hpp"
#include "Pixel.hpp"
#include "ElementList.hpp"
#include "ElementStack.hpp"
#include "ElementQueue.hpp"
#include "ElementDoubleList.hpp"
#include "InputOutput.hpp"

class Core
{
    QueuePixel* queuePx = nullptr;
    int width = 0;
    int height = 0;
    int counter = 0;
    string file_name;
public:
    Core();
    ~Core();
    
    void start();
    void loadImage(string file_name);
    void createStack();
    void readStackOperations(StackOperations* op);
    void reverse(QueuePixel* qOriginal, int w, int h, string file_name);
    void sort(QueuePixel* qOriginal);
    void flip(QueuePixel* qOriginal, int w, int h);
    void flop(QueuePixel* qOriginal, int w, int h);
    void darken(QueuePixel* qOriginal);
};

#endif // CORE_HPP
