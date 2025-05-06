#include "DoubleListPixel.hpp"

DoubleListPixel::DoubleListPixel()
{
    //constructor sets header to null
    header = nullptr;
}

DoubleListPixel::~DoubleListPixel()
{
    makenull();
}

void DoubleListPixel::insert(Pixel* px, ElementDoubleList* pnt)
{
    ElementDoubleList* element = new ElementDoubleList(px, nullptr, nullptr);
    
    //Case 1: If list is empty
    //Case 2: at beginning
    if(header==nullptr||header==pnt)
    {
        insertFirst(px);
    }
    
    //Case 3: Before element pnt
    ElementDoubleList* temp = header;
    while(temp!=nullptr && temp->getNext() != pnt)
    {
        temp=temp->getNext();
    }
    
    if(temp!=nullptr)
    {
        element->setNext(pnt);
        pnt->setPrev(element);
        element->setPrev(temp);
        temp->setNext(element);
    }
    else
    {//Case 4: pnt is nullptr, insert at the end
        insertLast(px);
    }
}

void DoubleListPixel::insertPos(Pixel* px, int pos)
{
    if (pos>=0)
    {
        ElementDoubleList* element = new ElementDoubleList(px, nullptr, nullptr);
        
        //Case 1: First position
        if((header==nullptr) || (pos==0))
        {
            insertFirst(px);
        }
        else
        {
            ElementDoubleList* prevNew = findPosition(pos-1);//find the element just before the position where the new element should be inserted
        
            //Case 3: position out of range
            if(!prevNew)
            {
                delete element;
            }
            
            //Case 4: General case
            ElementDoubleList* n = prevNew->getNext();
            element->setNext(n);
            n->setPrev(element);
            element->setPrev(prevNew);
            prevNew->setNext(element);
        }
    }
}

void DoubleListPixel::insertFirst(Pixel* px)
{
    ElementDoubleList* element = new ElementDoubleList(px, nullptr, nullptr);
    element->setNext(header);
    element->setPrev(nullptr);
    header = element;
}

void DoubleListPixel::insertLast(Pixel* px)
{
    if(empty())//Case 0: empty
    {
        insertFirst(px);
    }
    
    else 
        {
            //Case 1: only 1 element
            ElementDoubleList* element = new ElementDoubleList(px, nullptr, nullptr);
            ElementDoubleList* temp = header;
            if(header->getNext()==nullptr)
        
            {
                header->setNext(element);
                element->setPrev(header);
                element->setNext(nullptr);
            }
            else
            {
                //Case 2: Last position
                while (temp->getNext())//while next(temp)!=nullptr
                {//find the last element: temp->getNext()==nullptr
                    temp=temp->getNext();
                }
                temp->setNext(element);
                element->setPrev(temp);
                element->setNext(nullptr);
            }
        }
}

void DoubleListPixel::deleteP(ElementDoubleList* p)
{
    //Case 1: null pointer exception
    if(p!=nullptr)
    {
        //Case 2: first and only
        if(header==p && p->getNext()==nullptr)
        {
            delete(header);
            header=nullptr;
        }
        //Case 3: Last one
        if (p->getNext()==nullptr)
        {
            delete(p);
        }
        else{
            //Case 4: general case
            ElementDoubleList* temp = p->getNext();
            p->setNext(temp->getNext());
            
            delete(temp);
        }
    }
    
}

void DoubleListPixel::deletePos(int pos)
{
    if(!empty())//Case 1: invalid position or empty list
    {
        ElementDoubleList* temp = findPosition(pos);
        
        if(temp)//Case 2: element does not exist
        {
            ElementDoubleList* n = temp->getNext();
            ElementDoubleList* prev = temp->getPrev();
            //Case 3: first element
            if(temp==header)
            {
                delete(temp);
                header = n;//if there was only an element, now header is null
            }
            else
            {
                prev->setNext(n);
                n->setPrev(prev);
                delete(temp);
            }
        }
    }
}

ElementDoubleList* DoubleListPixel::locate(Pixel* px)
{
    ElementDoubleList* result = nullptr;
    ElementDoubleList* temp = header;
    while (temp!=nullptr)
    {
        if(temp->getPixel()==px)
        {
            result = temp;
        }
        else
        {
            temp = temp->getNext();
        }
    }
    return result;
}

int DoubleListPixel::locatePos(Pixel* px)
{
    ElementDoubleList* temp = header;
    int pos=0;
    int result = -1;
    
    while(temp!=nullptr)
    {
        if(temp->getPixel()==px)
        {
            result = pos;
        }
        temp=temp->getNext();
        pos++;
    }
    return result;//not found
}

Pixel* DoubleListPixel::retrievePx(int pos)
{
    Pixel* result = nullptr;
    ElementDoubleList* temp = findPosition(pos);
    if(temp!=nullptr)
    {
        result = temp->getPixel();
    }
    return result;
}

ElementDoubleList* DoubleListPixel::retrieve(int pos)
{
    ElementDoubleList* result = nullptr;
    ElementDoubleList* temp = findPosition(pos);
    if(temp!=nullptr)
    {
        result = temp;
    }
    return result;
}

ElementDoubleList* DoubleListPixel::next(ElementDoubleList* p)
{
    ElementDoubleList* result = nullptr;
    if(p!=nullptr)
    {
        result = p->getNext();
    }
    return result;
}

ElementDoubleList* DoubleListPixel::previous(ElementDoubleList* p)
{
    ElementDoubleList* result = nullptr;
    if(p!=nullptr)
    {
        result = p->getPrev();
    }
    return result;
}

void DoubleListPixel::makenull()
{
    while(!empty())
    {
        deletePos(0);
    }
}

bool DoubleListPixel::empty()
{
    return header==nullptr;
}

ElementDoubleList* DoubleListPixel::findPosition(int pos)
{
    ElementDoubleList* result = nullptr;
    if(pos>=0)
    {
        ElementDoubleList* temp = header;
        while(temp!=nullptr && pos>0)
        {
            temp=temp->getNext();
            pos--;
        }
        result = temp;
    }
    return result;
}

ElementDoubleList* DoubleListPixel::getLast()
{
    ElementDoubleList* result = nullptr;
    if(!empty())
    {
        ElementDoubleList* temp = header;
        while(temp->getNext()!=nullptr)
        {//get to the last element
            temp=temp->getNext();
        }
        result = temp;
    }
    return result;
}

int DoubleListPixel::getSize()
{
    int pos = -1;
    if(!empty())
    {
        int pos=1; //counter
        ElementDoubleList* temp = header;
        while(temp->getNext()!=nullptr)
        {
            temp=temp->getNext();
            pos++;
        }
    }
    
    return pos;
}

ElementDoubleList* DoubleListPixel::getHeader()
{
    return header;
}