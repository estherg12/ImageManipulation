#include "Core.hpp"
#include <iostream>
using namespace std;

using std::string;

Core::Core()
{
    queuePx = nullptr;
    width = 0;
    height = 0;
    counter = 0;
    file_name = "";
}

Core::~Core()
{
}

void Core::start()
{
    this->queuePx = new QueuePixel(); //inicialize the queue so that front is nullptr
    InputOutput* io = nullptr;
    file_name = io->askName();
    loadImage(file_name); //calls a Core method to load the image with the name provided by the user
    StackOperations* st = io->askOper(); //stack with the characters of the operation that must be executed
    //cout<<"Got the full stack"<<endl;
    while(!(st->isEmpty()))
    {
        //cout<<st->top()<<endl;
        //gets the char introduced by the user in the stack one by one and calls the operation method in each case
        switch(st->top())
        {
            case 'R': reverse(this->queuePx, this->width, this->height, file_name);//calls reverse with the queue created in loadImage
            break;
            case 'S': sort(this->queuePx);//calls sort with the queue created in loadImage
            break;
            case 'V': flip(this->queuePx, this->width, this->height);//calls flip with the queue created in loadImage
            break;
            case 'H': flop(this->queuePx, this->width, this->height);//calls flop with the queue created in loadImage
            break;
            case 'O': darken(this->queuePx);//calls darken with the queue created in loadImage
            break;
        }
        st->pop(); //deletes the element used, so that it can have access to the next
        this->counter++; //increases the counter value for each operation asked so that there wont be image with the same name
    }
}
void Core::loadImage(string file_name)
{
    //string file_name;//call IO method which shows the posible images to choose
    Image* img = new Image(file_name + ".bmp");
    cout<<"Image well created"<<endl;
    img->loadImageFromDisk();
    cout<<"Image loaded from the disk"<<endl;
    
    if(img->isValid())
    {
        cout<<"Image is valid"<<endl;
        for (int x=0; x<img->getWidth(); x++)
        {
            for (int y=0; y<img->getHeight(); y++)
            {
                Pixel* pp = new Pixel(x,y);
            
                // load RGB values from raw image data loaded with malloc
                pp->getFromRaw(img->getImagePointertoInternal(),img->getWidth(),img->getHeight(),x,y); // pointer to pixel class
                if (pp->isNotBlack()) 
                {
                    queuePx->enqueue(pp);
                    //cout<<"Is queuePx empty (0): "<<queuePx->isEmpty()<<endl;
                }
            }
        }
        
        //save the width and height of the image in the variable of the class so that other methods have access to them
        width = img->getWidth();  
        height = img->getHeight();
    }
    else
    {
        cout<<"Could not load the image: "<<img->getInternalError()<<endl;
    }
}

void Core::reverse(QueuePixel* qOriginal, int w, int h, string file_name)
{
    /*cout<<"Pixel value R: "<<static_cast<int>(qOriginal->getFront()->getR())<<endl;
    cout<<"Pixel value G: "<<static_cast<int>(qOriginal->getFront()->getG())<<endl;
    cout<<"Pixel value B: "<<static_cast<int>(qOriginal->getFront()->getB())<<endl;*/
    
    QueuePixel* qReverse = new QueuePixel(); //this queue will be manipulated
    QueuePixel* qSame = new QueuePixel(); //this queue will be the auxiliar to restore the original queue
    //cout<<"Reversed queue created"<<endl;
    //cout<<"Queue empty?: "<<qOriginal->isEmpty()<<endl;
    
    //this while gets pixel by pixel from the queue loaded and enqueues this pixel in the copy that will restore the original when this is modified
    //and modifies the values of RGB pixels and store pixel by pixel in the reversed queue
    while(!(qOriginal->isEmpty()))
    {
        //cout<<"Entered the while"<<endl;
        Pixel* originalPx = qOriginal->getFront();
        //cout<<"Pixel created"<<endl;
        qSame->enqueue(originalPx);
        //cout<<"Pixel enqueued in qSame"<<endl;
        
        //modification of each RGB value
        unsigned char newR = static_cast<unsigned char>(255 - static_cast<int>(originalPx->getR()));
        unsigned char newG = static_cast<unsigned char>(255 - static_cast<int>(originalPx->getG()));
        unsigned char newB = static_cast<unsigned char>(255 - static_cast<int>(originalPx->getB()));
        
        //cout<<"newR inizialiced and modified"<<endl;
        
        Pixel* newPx = new Pixel(originalPx->getX(), originalPx->getY(), newR, newG, newB);
        //cout<<"Creation of the new pixel with modified values done"<<endl;
        qReverse->enqueue(newPx);
        //cout<<"enqueued in the qReverse the new Pixel"<<endl;
        
        qOriginal->dequeue();
        //cout<<"Dequeued qOriginal"<<endl;
    }
    
    //cout<<"Queue reversed"<<endl;
    
    //Create the new image with the reversed queue
    unsigned char* imageRaw = (unsigned char *)malloc(sizeof(unsigned char) * this->width * this->height * 3);
    
    //this while set into raw pixel by pixel from the reversed queue in the new created image
    while(!qReverse->isEmpty()){
        Pixel* pp = qReverse->getFront(); //gets the pixel from the first element
        int x = pp->getX();
        int y = pp->getY();
        pp->setIntoRaw(imageRaw,this->width,this->height,x,y);
        qReverse->dequeue();//dequeue so that in the next iteration we can access the next element
    }
    Image* myImg= new Image("");
    myImg->setNewImagePointerWithOldRemoval(imageRaw,this->width,this->height);
    //saves the new image with the same file name, the counter of the operations that have been done in the execution, and the letter that represents this operation
    myImg->saveImageToDisk(file_name + to_string(this->counter) + "R.bmp");
    cout<<"Reversed image saved"<<endl;
    
    //restore the original queue with the qSame
    while(!qSame->isEmpty())
    {
        Pixel* samePx = qSame->getFront();
        qOriginal->enqueue(samePx);
        qSame->dequeue();
    }
}

void Core::sort(QueuePixel* qOriginal)
{
    //cout<<"got to sort method"<<endl;
    //1. Create a LIST with the same elements as a queue, and a SAME QUEUE to use it as a copy and a way to keep the original queue
    QueuePixel* qSame = new QueuePixel();//this queue will be the auxiliar to restore the original queue
    ListPixel* list = new ListPixel(); //this list will be the one in which the order of the pixels will be modified
    
    //cout<<"about to enter the 1st while"<<endl;
    
    //insert pixel by pixel in the new list and in the queue Same
    while(!(qOriginal->isEmpty()))
    {
        Pixel* px = qOriginal->getFront();
        Pixel* pxCopy = new Pixel(px->getX(), px->getY(), px->getR(), px->getG(), px->getB());
        list->insertLast(pxCopy);
        qSame->enqueue(pxCopy);
        qOriginal->dequeue();
        
        //cout<<"x: "<<pxCopy->getX()<<" y: "<<pxCopy->getY()<<endl;
    }
    //cout<<"finished the 1st while"<<endl;
    
    //2. SORT THE LIST: BUBBLE sort
    int size = list->getSize();
    
    //the two fors to go through the list the times needed until sorted
    //should take size of the queue squared
    for(int i=0; i<size-1; i++) 
    {
        //cout<<"Iteration "<<i<<" of the first for"<<endl;
        for(int j=0; j<size-i-1; j++)
        {
            ElementList* tempS = list->findPosition(j);
            
            //Sum of the RGB values of the pixel tempS
            Pixel* tempPx = tempS->getPixel();
            
            //access the values rgb from tempPx
            unsigned char tempR = tempPx->getR();
            unsigned char tempG = tempPx->getG();
            unsigned char tempB = tempPx->getB();
            
            //change temp RGB values to int into another variables so taht we can do the sum
            int intR = (int) tempR;
            int intG = (int) tempG;
            int intB = (int) tempG;
            
            int sumTemp = intR+intG+intB; //sum
            
            //Sum of the RGB values of the pixel tempS+1
            ElementList* tempNext = tempS->getNext();
            Pixel* tempNextPx = tempNext->getPixel();
            
            //acces the values RGBfrom tempNextPx
            unsigned char nextR = tempNextPx->getR();
            unsigned char nextG= tempNextPx->getG();
            unsigned char nextB = tempNextPx->getB();
            
            //change tempNext RGB values to int
            int intR2 = (int) nextR;
            int intG2 = (int) nextG;
            int intB2 = (int) nextB;
            
            int sumTempNext = intR2+intG2+intB2;
            
            //if the sum of the RGB values of the temp element is smaller than the sum from the next element
            if(sumTemp < sumTempNext)
            {
                //create new pixels with the RGB values interchanged
                Pixel* newLeft = new Pixel(tempPx->getX(), tempPx->getY(), nextR, nextG, nextB);//create a new pixel for the left with the RGB values of the right
                Pixel* newRight = new Pixel(tempNextPx->getX(), tempNextPx->getY(), tempR, tempG, tempB);//create a new pixel for the left with the RGB values of the right
                
                //set the new pixels
                tempS->setPixel(newLeft);
                tempNext->setPixel(newRight);
                
                /*
                 * CHANGING THE WHOLE ELEMENT -does not work
                //Case: first element
                if(tempS != list->getHeader())
                {
                    ElementList* tempPrev = list->getPrev(tempS);
                    tempPrev->setNext(tempNext);
                }
                //General case
                tempS->setNext(tempNext->getNext());
                tempNext->setNext(tempS);
                 */
            }
        }
    }
        
    /*
    QUICK SORT: -does not work: not needed
    ElementDoubleList* first = list->getHeader();
    ElementDoubleList* last = list->getLast();
    ElementDoubleList* newFirst = recursiveQuickSort(first, last);
    
    DoubleListPixel* sortedList = new DoubleListPixel();
    ElementDoubleList* temp = newFirst;
    while(temp != nullptr)
    {
        sortedList->insertLast(temp->getPixel());
        temp = temp->getNext();
    }
    */
    
    //3. Create a new queue with the elements of the sorted list
    ElementList* aux = list->getHeader();
    QueuePixel* qSort = new QueuePixel(); //this queue will have the sorted pixels and will be used to create the new image
    
    //go through the list and enqueue each pixel in qSort
    while(aux != nullptr)
    {
        Pixel* pxS = aux->getPixel();
        qSort->enqueue(pxS);
        aux=aux->getNext();
    }

    //4. Create the new image with the reversed queue
    unsigned char* imageRaw = (unsigned char *)malloc(sizeof(unsigned char) * this->width * this->height * 3);
    //insert each pixel from qSort in the new image
    while(!qSort->isEmpty()){
        Pixel* pp = qSort->getFront();
        int x = pp->getX();
        int y = pp->getY();
        pp->setIntoRaw(imageRaw,this->width,this->height,x,y);
        qSort->dequeue();
    }
    Image* myImg= new Image("");
    myImg->setNewImagePointerWithOldRemoval(imageRaw,this->width,this->height);
    //saves the new image with the same file name, the counter of the operations that have been done in the execution, and the letter that represents this operation
    myImg->saveImageToDisk(file_name + to_string(this->counter) + "S.bmp");
    cout<<"Sorted image saved"<<endl;
    
    //5. Restore the original queue with the qSame
    while(!qSame->isEmpty())
    {
        Pixel* samePx = qSame->getFront();
        qOriginal->enqueue(samePx);
        qSame->dequeue();
    }
}

void Core::flip(QueuePixel* qOriginal, int w, int h)
{
    //1. Create a list with the same elements as a queue
    DoubleListPixel* list = new DoubleListPixel();//in this list, the pixels will be modified
    QueuePixel* qSame = new QueuePixel();//this queue will be the auxiliar to restore the original queue
    cout<<"qSame created. Is qOriginal empty? (0): "<<qOriginal->isEmpty()<<endl;
    
    //goes through the original queue to insert the first element into the new list and the qSame queue
    while(!qOriginal->isEmpty())
    {
        Pixel* px0 = qOriginal->getFront();
        //cout<<"x: "<<px0->getX()<<" y: "<<px0->getY()<<endl;
        list->insertLast(px0->clone());
        qSame->enqueue(px0->clone());
        qOriginal->dequeue();
    }
    cout<<"list created"<<endl;
    
    cout<<"W: "<<w<<endl;
    cout<<"H: "<<h<<endl;
    
    
    //2. Flip the list
    
    //go through the list: see the box diagrams
    
    //does the same iterations as the height
    for(int i=0; i<h; i++)
    {
        int m = 0; //medium column of the image
        if((w%2)==0)//even number of columns
        {
            m = w/2; //if width is 6, medium column is 3
            for(int j=0; j<m; j++)
            {
                //where h: height, w: width, i represents the coord y, j represents the coord x
                int posLeft = (j*(h)) + i; //get the position of the element from the left of the middle column
                int posRight = ((w-j-1)*(h)) + i; //get the position of the element from the right of the middle column
                
                //cout<<"L: "<<posLeft<<" R: "<<posRight<<endl;
                ElementDoubleList* tempLeft = list->findPosition(posLeft); //element in the position posLeft in the list
                ElementDoubleList* tempRight = list->findPosition(posRight);//element in the position posRight in the list
                
                Pixel* pixelLeft = tempLeft->getPixel();//gets the pixel from the element in the left so that we can access the RGB values
                Pixel* pixelRight = tempRight->getPixel();//gets the pixel from the element in the right so that we can access the RGB values
                
                //access the values from the l&r
                unsigned char leftR = pixelLeft->getR();
                unsigned char leftG = pixelLeft->getG();
                unsigned char leftB = pixelLeft->getB();
                
                unsigned char rightR = pixelRight->getR();
                unsigned char rightG = pixelRight->getG();
                unsigned char rightB = pixelRight->getB();
                
                Pixel* newLeft = new Pixel(pixelLeft->getX(), pixelLeft->getY(), rightR, rightG, rightB);//create a new pixel for the left with the RGB values of the right
                Pixel* newRight = new Pixel(pixelRight->getX(), pixelRight->getY(), leftR, leftG, leftB);//create a new pixel for the left with the RGB values of the right
                
                //set the new pixels into the elements
                tempLeft->setPixel(newLeft);
                tempRight->setPixel(newRight);
            }
        }
        else{//odd number of columns
            m = (w/2) +1;//if width is 5, medium column is 3
            for(int j=1; j<m; j++)
            {
                //where h: height, w: width, i represents the coord y, j represents the coord x
                int posLeft = (j*(h)) + i; //get the position of the element from the left of the middle column
                int posRight = ((w-j-1)*(h)) + i; //get the position of the element from the right of the middle column
                
                //cout<<"L: "<<posLeft<<" R: "<<posRight<<endl;
                ElementDoubleList* tempLeft = list->findPosition(posLeft); //element in the position posLeft in the list
                ElementDoubleList* tempRight = list->findPosition(posRight);//element in the position posRight in the list
                
                Pixel* pixelLeft = tempLeft->getPixel();//gets the pixel from the element in the left so that we can access the RGB values
                Pixel* pixelRight = tempRight->getPixel();//gets the pixel from the element in the right so that we can access the RGB values
                
                //access the values from the l&r
                unsigned char leftR = pixelLeft->getR();
                unsigned char leftG = pixelLeft->getG();
                unsigned char leftB = pixelLeft->getB();
                
                unsigned char rightR = pixelRight->getR();
                unsigned char rightG = pixelRight->getG();
                unsigned char rightB = pixelRight->getB();
                
                Pixel* newLeft = new Pixel(pixelLeft->getX(), pixelLeft->getY(), rightR, rightG, rightB);//create a new pixel for the left with the RGB values of the right
                Pixel* newRight = new Pixel(pixelRight->getX(), pixelRight->getY(), leftR, leftG, leftB);//create a new pixel for the left with the RGB values of the right
                
                //set the new pixels into the elements
                tempLeft->setPixel(newLeft);
                tempRight->setPixel(newRight);
            }
        }
        cout<<"M: "<<m<<endl;
        //goes until the middle column x.e. if the middle column is 
        
    }
    //CHANGING THE WHOLE ELEMENTS -does not work
    //ElementDoubleList* aux = list->getHeader();
    //while(aux->getNext()!=nullptr)
    /*
    for(int i=0; i<=this->height; i++)
    {
        ElementDoubleList* aux = list->retrieve(i);
        Pixel* px = list->retrievePx(i);
        //gets the column in the middle
        if(px->getX() == m)
        {
            //cout<<m<<endl;
            for(unsigned int n=0; n<m; n++)
            {
                //cout<<n<<endl;
                if((w%2)==0)//even
                {
                    //gets the element and the previous
                    aux->getPrev()->setNext(aux->getNext());
                    aux->setNext(aux->getPrev());
                    aux->getNext()->setPrev(aux->getPrev());
                    aux->setPrev(aux->getNext());
                }
                else
                {//odd
                    //gets the elements next to the middle (previous and next)
                    aux->getPrev()->setNext(aux->getNext());
                    aux->setNext(aux->getPrev());
                    aux->getNext()->setPrev(aux->getPrev());
                    aux->setPrev(aux->getNext()); 
                }
            }
            //cout<<"for ended"<<endl;
        }
        
        //aux = aux->getNext();
        count++;
        //cout<<count<<endl;
    }
    //cout<<count<<endl;
    */
    cout<<"Pixels changed"<<endl;
     
    //3. Create a new queue with the elements of the sorted list
    ElementDoubleList* aux2 = list->getHeader();
    QueuePixel* qFlip = new QueuePixel();
    cout<<"Queue flip created"<<endl;
    
    //go through the list and enqueue each pixel in qFlip
    while(aux2->getNext() != nullptr)
    {
        Pixel* pxS = aux2->getPixel();
        qFlip->enqueue(pxS);
        aux2 = aux2->getNext();
    }
    cout<<"enqueued qFlip"<<endl;
    list->makenull();

    //4. Create the new image with the flipped queue
    unsigned char* imageRaw = (unsigned char *)malloc(sizeof(unsigned char) * this->width * this->height * 3);
    
    //insert each pixel from qFlip in the new image
    while(!qFlip->isEmpty())
    {
        Pixel* pp = qFlip->getFront();
        int x = pp->getX();
        int y = pp->getY();
        pp->setIntoRaw(imageRaw,this->width,this->height,x,y);
        qFlip->dequeue();
    }
    cout<<"Set pixels into the imageRaw"<<endl;
    Image* myImg= new Image("");
    myImg->setNewImagePointerWithOldRemoval(imageRaw,this->width,this->height);
    //saves the new image with the same file name, the counter of the operations that have been done in the execution, and the letter that represents this operation
    myImg->saveImageToDisk(file_name + std::to_string(this->counter) + "V.bmp"); //saves the new image to disk
    cout<<"Flipped image saved"<<endl;
    
    //5. Restore the original queue with the qSame
    while(!qSame->isEmpty())
    {
        Pixel* samePx = qSame->getFront();
        qOriginal->enqueue(samePx);
        qSame->dequeue();
    }
    cout<<"retored the original queue"<<endl;
}

void Core::flop(QueuePixel* qOriginal, int w, int h)
{
    //1. Create a list with the same elements as a queue
    DoubleListPixel* list = new DoubleListPixel();//this list will be modified
    QueuePixel* qSame = new QueuePixel();//this queue will be the auxiliar to restore the original queue
    
    //go through the qOriginal to insert all her elements into a list that will be modified and a queue
    while(!qOriginal->isEmpty())
    {
        Pixel* px0 = qOriginal->getFront();
        list->insertLast(px0);
        qSame->enqueue(px0);
        qOriginal->dequeue();//so thath we can access the next element
    }
    
    cout<<"W: "<<w<<endl;
    cout<<"H: "<<h<<endl;
    int m = 0; //medium row of the image
    if((h%2)==0)//even number of rows
    {
        m = h/2; //if width is 6, medium row is 3
    }
    else{//odd number of rows
        m = (h/2) +1;//if width is 5, medium row is 3
    }
    
    //2. Flop the list
    //does the same iterations as the height
    for(int i=0; i<w; i++)
    {
        //goes until the middle column x.e. if the middle column is 
        for(int j=0; j<m; j++)
        {
            //where h: height, w: width, i represents the coord y, j represents the coord x
            int posUp = (h*i)+j; //get the position of the element from the upper part of the middle column
            int posDown = (w*(i+1))-(j+1); //get the position of the element from the down part of the middle column
            
            //cout<<"L: "<<posUp<<" R: "<<posDown<<endl;
            ElementDoubleList* tempUp = list->findPosition(posUp); //element in the position posUp in the list
            ElementDoubleList* tempDown = list->findPosition(posDown);//element in the position posDown in the list
            
            Pixel* pixelUp = tempUp->getPixel();//gets the pixel from the element in the upper part so that we can access the RGB values
            Pixel* pixelDown = tempDown->getPixel();//gets the pixel from the element in the down part so that we can access the RGB values
            
            //access the values from the upper and down part
            unsigned char leftR = pixelUp->getR();
            unsigned char leftG = pixelUp->getG();
            unsigned char leftB = pixelUp->getB();
            
            unsigned char rightR = pixelDown->getR();
            unsigned char rightG = pixelDown->getG();
            unsigned char rightB = pixelDown->getB();
            
            Pixel* newUp = new Pixel(pixelUp->getX(), pixelUp->getY(), rightR, rightG, rightB);//create a new pixel for the left with the RGB values of the right
            Pixel* newDown = new Pixel(pixelDown->getX(), pixelDown->getY(), leftR, leftG, leftB);//create a new pixel for the left with the RGB values of the right
            
            tempUp->setPixel(newUp);
            tempDown->setPixel(newDown);
        }
    }
    
    /*CHANGING THE WHOLE ELEMENTS -does not work
    ElementDoubleList* aux = list->getHeader();
    
    //go through the list: see the box diagrams
    while(aux->getNext()!=nullptr)
    {
        Pixel* px = aux->getPixel();
        if(px->getY() == m)
        {
            //gets the row in the middle
            for(unsigned int n=1; n<m; n++)
            {
                if((h%2)==0)//even
                {
                    //gets the element and the previous
                    aux->getPrev()->setNext(aux->getNext());
                    aux->setNext(aux->getPrev());
                    aux->getNext()->setPrev(aux->getPrev());
                    aux->setPrev(aux->getNext());
                }
                else
                {//odd
                    //gets the elements next to the middle (previous and next)
                    aux->getPrev()->setNext(aux->getNext());
                    aux->setNext(aux->getPrev());
                    aux->getNext()->setPrev(aux->getPrev());
                    aux->setPrev(aux->getNext()); 
                }
            }
        }
        aux = aux->getNext();
    }*/
    
    //3. Create a new queue with the elements of the flopped list
    ElementDoubleList* aux2 = list->getHeader();
    QueuePixel* qFlop = new QueuePixel();
    
    //goes through the list and enqueue each pixel in qFlop
    while(aux2 != nullptr)
    {
        Pixel* pxS = aux2->getPixel();
        Pixel* newPx = new Pixel(pxS->getX(),pxS->getY(),pxS->getR(),pxS->getG(),pxS->getB());
        qFlop->enqueue(newPx);
        aux2=aux2->getNext();
    }

    //4. Create the new image with the flopped queue
    unsigned char* imageRaw = (unsigned char *)malloc(sizeof(unsigned char) * this->width * this->height * 3);
    
    //insert each pixel from qFlop in the new image
    while(!qFlop->isEmpty()){
        Pixel* pp = qFlop->getFront();
        int x = pp->getX();
        int y = pp->getY();
        pp->setIntoRaw(imageRaw,this->width,this->height,x,y);
        qFlop->dequeue();
    }
    
    Image* myImg= new Image("");
    myImg->setNewImagePointerWithOldRemoval(imageRaw,this->width,this->height);
    //saves the new image with the same file name, the counter of the operations that have been done in the execution, and the letter that represents this operation
    myImg->saveImageToDisk(file_name + to_string(this->counter) + "H.bmp");//save the image to disk
    cout<<"Flopped image saved"<<endl;
    
    //5. Restore the original queue with the qSame
    while(!qSame->isEmpty())
    {
        Pixel* samePx = qSame->getFront();
        qOriginal->enqueue(samePx);
        qSame->dequeue();
    }
    
}

void Core::darken(QueuePixel* qOriginal)
{
    QueuePixel* qDarken = new QueuePixel();//this queue will be manipulated
    QueuePixel* qSame = new QueuePixel();//this queue will be the auxiliar to restore the original queue
    
    //goes through the qOriginal and modifies the element's pixels to insert them into a darken queue
    while(!(qOriginal->isEmpty()))
    {
        Pixel* originalPx = qOriginal->getFront();
        
        qSame->enqueue(originalPx);//enqueue the exactly same pixel so that we can later restore the original queue without modifications
        
        //get the RGB values of the pixel
        int intR = (int) originalPx->getR();
        int intG = (int) originalPx->getG();
        int intB = (int) originalPx->getB();
        
        //calculate the avarage
        int total = (intR + intG + intB)/3;
        
        //modification of each RGB value
        unsigned char newR = static_cast<unsigned char>(total);
        unsigned char newG = static_cast<unsigned char>(total);
        unsigned char newB = static_cast<unsigned char>(total);
        
        Pixel* newPx = new Pixel(originalPx->getX(), originalPx->getY(), newR, newG, newB);//create a new pixel with new RGB values
        qDarken->enqueue(newPx);//enqueue this pixel into the darken queue (modified one)
        
        qOriginal->dequeue();//dequeue so that we can access the next element
    }
    
    //Create the new image with the darkened queue
    unsigned char* imageRaw = (unsigned char *)malloc(sizeof(unsigned char) * this->width * this->height * 3);
    
    //insert each pixel from qDarken in the new image
    while(!qDarken->isEmpty()){
        Pixel* pp = qDarken->getFront();
        int x = pp->getX();
        int y = pp->getY();
        pp->setIntoRaw(imageRaw,this->width,this->height,x,y);
        qDarken->dequeue();
    }
    Image* myImg= new Image("");
    myImg->setNewImagePointerWithOldRemoval(imageRaw,this->width,this->height);
    
    //saves the new image with the same file name, the counter of the operations that have been done in the execution, and the letter that represents this operation
    myImg->saveImageToDisk(file_name + to_string(this->counter) + "O.bmp");
    cout<<"Darken image saved"<<endl;
    
    //restore the original queue with the qSame
    while(!qSame->isEmpty())
    {
        Pixel* samePx = qSame->getFront();
        qOriginal->enqueue(samePx);
        qSame->dequeue();
    }
}


/*
if (myImg->isValid())
    {
        //std::cout << "is valid "<<std::endl;
        unsigned char* image2 = (unsigned char *)malloc(sizeof(unsigned char) * myImg->getWidth() * myImg->getHeight() * 3);
        for (int y=0; y<myImg->getHeight(); y++)
        {
            for (int x=0; x<myImg->getWidth(); x++)
            {
                Pixel *pp = new Pixel(x,y);
            
                // load RGB values from raw image data loaded with malloc
                pp->getFromRaw(myImg->getImagePointertoInternal(),myImg->getWidth(),myImg->getHeight(),x,y); // pointer to pixel class
                pp->normalizeToRedGreenOrBlue();// process image (not needed)
                if (pp->isNotBlack()) 
                {
                    maxDist = max(maxDist,pp->getDistACentro(myImg->getWidth(),myImg->getHeight())); // not needed
                    //std::cout << "new maxDist:  " <<maxDist<< std::endl;
                
                    queuePx->addSorted(pp,myImg->getWidth(),myImg->getHeight());
                }

                // set RGB values in a raw image data to save in disk
                pp->setIntoRaw(image2,myImg->getWidth(),myImg->getHeight(),x,y);
            }
        }

        //std::cout << "save result2: " << tinyimg_save("im-2.bmp",myImg->getWidth(),myImg->getHeight(),TINYIMG_RGB,image2) << std::endl;
        myImg->setNewImagePointerWithOldRemoval(image2,myImg->getWidth(),myImg->getHeight());
        myImg->saveImageToDisk("");
    }
    else
        {
           //std::cout << "is not valid ---- "<< myImg->getInternalError() <<std::endl;
        }
    
    //std::cout << "final maxDist:  " <<maxDist<< std::endl;



ElementDoubleList* Core::partition(ElementDoubleList* first, ElementDoubleList* last)
{
    ElementDoubleList* pivot = last;//pivot is the last element of the list
    ElementDoubleList* small = nullptr;
    ElementDoubleList* temp = first;
    
    //get the sum of the RGB pixel elements of the pivot
    Pixel* pivotPx = pivot->getPixel();
        
    static_cast<int> intR = pivotPx->getR();
    static_cast<int> intG = pivotPx->getG();
    static_cast<int> intB = pivotPx->getB();
        
    int sumPivot = intR+intG+intB;
    
    while(temp != nullptr)
    {
        //get the sum of the RGB values of the pixel of the temporal element
        Pixel* auxPx = temp->getPixel();
        
        static_cast<int> intR = auxPx->getR();
        static_cast<int> intG = auxPx->getG();
        static_cast<int> intB = auxPx->getB();
        
        int sumAux = intR+intG+intB;
        
        //if the sum of the RGB values are less than the pivot's is a small
        if(sumAux < sumPivot)
        {
            //AND small is not already occupied by an element
            if(small==nullptr)
            {
                small = temp;
            }
            
            temp = temp->getNext();
            
        }
        //sumAux >= sumPivot
        else
        {
            //If it doesn't exist yet a smaller RGB element than the pivot's
            //there is no small element to interchange with the bigger
            if(small == nullptr)
            {
                temp = temp->getNext();
            }
            else
            {
                ElementDoubleList* smallPrev = nullptr;
                ElementDoubleList* smallNext = small->getNext();
                ElementDoubleList* tempNext = temp->getNext();
                ElementDoubleList* tempPrev = temp->getPrev();
                
                //if the small element has previous
                if(small != first)
                {
                    smallPrev = small->getPrev();
                    
                    smallPrev->setNext(temp);
                    small->setPrev(tempPrev);
                }
                small->setNext(tempNext);
                smallNext->setPrev(temp);
                
                tempPrev->setNext(small);
                temp->setPrev(smallPrev);
                
                temp->setNext(smallNext);
                tempNext->setPrev(small);
                
                if(tempNext != nullptr)
                {
                    ElementDoubleList* auxSmall = small;
                    small = temp->getNext();
                    temp = auxSmall->getNext();
                }
                
                temp = nullptr; //exit the while
            }
        }
    }
    //if after going through all the list
     //there is no smaller element than the pivot
     
    if(small == nullptr)
    {
        small = pivot;
    }
    
    return pivot;
}

ElementDoubleList* Core::recursiveQuickSort(ElementDoubleList* first, ElementDoubleList* last)
{
    ElementDoubleList* newFirst = first;
    if((first!=nullptr)&&(first!=end))
    {
        //part the list and get the pivot that has been used
        ElementDoubleList* pivot = partition(first, last);
        
        //get new first element
        ElementDoubleList* partitedFirst = pivot;
        while (partitedFirst->getPrev() != nullptr)
        {
            partitedFirst = partitedFirst->getPrev()
        }
        
        //get new last element
        ElementDoubleList* partitedLast = pivot;
        while(partitedLast->getNext() != nullptr)
        {
            partitedLast = partitedLast->getNext();
        }
        
        //LEFT: if there are elements before the pivot
        if(partitedFirst != pivot)
        {
            ElementDoubleList* tempL = partitedFirst;
            while(tempL != pivot)
            {
                tempL = tempL->getNext();
            }
            newFirst = recursiveQuickSort(partitedFirst, tempL);
        }
        
        //RIGTH: if there are elements after the pivot
        if(partitedLast != pivot)
        {
            ElementDoubleList* tempR = pivot->getNext();
            while(tempR != nullptr)
            {
                tempR = tempR->getNext();
            }
            pivot->setNext(recursiveQuickSort(tempR, partitedLast));
        }
    }
    return newFirst;
}
*/