#include "ListPixel.hpp"

ListPixel::ListPixel()
{
    header = nullptr;
}

ListPixel::~ListPixel()
{
    makenull();
}

void ListPixel::insert(Pixel* px, ElementList* pnt)
{
    ElementList* element = new ElementList(px, nullptr);
    
    //Case 1: If list is empty
    //Case 2: at beginning
    if(header==nullptr||header==pnt)
    {
        insertFirst(px);
    }
    
    //Case 3: Before element pnt
    ElementList* temp = header;
    while((temp!=nullptr) && (temp->getNext() != pnt))
    {
        temp=temp->getNext();
    }
    
    if(temp!=nullptr)
    {
        element->setNext(pnt);
        temp->setNext(element);
    }
    else
    {//Case 4: pnt is nullptr, insert at the end
        insertLast(px);
    }
}

void ListPixel::insertPos(Pixel* px, int pos)
{
    if (pos>=0)
    {
        ElementList* element = new ElementList(px, nullptr);
        
        //Case 1: First position
        if((header==nullptr) || (pos==0))
        {
            insertFirst(px);
        }
        else
        {
            ElementList* prevNew = findPosition(pos-1);//find the element just before the position where the new element should be inserted
        
            //Case 3: position out of range
            if(!prevNew)
            {
                delete element;
            }
            
            //Case 4: General case
            ElementList* n = prevNew->getNext();
            element->setNext(n);
            prevNew->setNext(element);
        }
    }
}

void ListPixel::insertFirst(Pixel* px)
{
    ElementList* element = new ElementList(px, nullptr);
    element->setNext(header);
    header = element;
}

void ListPixel::insertLast(Pixel* px)
{
    if(empty())//Case 0: empty
    {
        insertFirst(px);
    }
    else
    {
        ElementList* element = new ElementList(px, nullptr);
        ElementList* temp = header;
        
        //Case 1: only 1 element
        if(header->getNext()==nullptr)
        {
            header->setNext(element);
        }
        else
        {
            //Case 2: Last position
            while (temp->getNext())//while next(temp)!=nullptr
            {//find the last element: temp->getNext()==nullptr
                temp=temp->getNext();
            }
            temp->setNext(element);
        }
    }
}

void ListPixel::deleteP(ElementList* p)
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
            ElementList* temp = p->getNext();
            p->setNext(temp->getNext());
            delete(temp);
        }
    }
    
}

void ListPixel::deletePos(int pos)
{
    if(!empty())//Case 1: invalid position or empty list
    {
        ElementList* prev = findPosition(pos);
        ElementList* temp = findPosition(pos);
        
        if(temp)//Case 2: element does not exist
        {
            ElementList* auxN = temp->getNext();
            //Case 3: first element
            if(temp==header)
            {
                delete(temp);
                header = auxN;//if there was only an element, now header is null
            }
            else
            {
                prev->setNext(auxN);
                delete(temp);
            }
        }
    }
}

ElementList* ListPixel::locate(Pixel* px)
{
    ElementList* result = nullptr;
    ElementList* temp = header;
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

int ListPixel::locatePos(Pixel* px)
{
    int result = -1;
    ElementList* temp = header;
    int pos=0;
    
    while(temp!=nullptr)
    {
        if(temp->getPixel()==px)
        {
            result = pos;
        }
        temp=temp->getNext();
        pos++;
    }
    return result;//not found if still -1
}

Pixel* ListPixel::retrieve(int pos)
{
    Pixel* result = nullptr;
    ElementList* temp = findPosition(pos);
    if(temp!=nullptr)
    {
        result = temp->getPixel();
    }
    return result;
}

ElementList* ListPixel::next(ElementList* p)
{
    ElementList* result = nullptr;
    if(p!=nullptr)
    {
        result = p->getNext();
    }
    return result;
}

ElementList* ListPixel::getPrev(ElementList* p)
{
    ElementList* result = nullptr;
    ElementList* temp = header;
    //Case 1: first element
    if(header != p)
    {
        while (temp->getNext() != nullptr)
        {
            if(temp->getNext() == p)
            {
                result = p; //found
            }
            temp = temp->getNext();
        }
    }
    return result;
}

void ListPixel::makenull()
{
    while(!empty())
    {
        deletePos(0);
    }
}

bool ListPixel::empty()
{
    return header==nullptr;
}

ElementList* ListPixel::findPosition(int pos)
{
    ElementList* temp = nullptr;
    if(pos>=0)
    {
        temp = header;
        while(temp!=nullptr && pos>0)
        {
            temp=temp->getNext();
            pos--;
        }
    }
    
    
    return temp;
}

Pixel* ListPixel::getLast()
{
    ElementList* temp = nullptr;
    if(!empty())
    {
        temp = header;
        while(temp->getNext()!=nullptr)
        {//get to the last element
            temp=temp->getNext();
        }
    }
    
    return temp->getPixel();
}

int ListPixel::getSize()
{
    int result = -1;
    if(!empty())
    {
        int pos=1; //counter
        ElementList* temp = header;
        while(temp->getNext()!=nullptr)
        {
            temp=temp->getNext();
            pos++;
            result = pos;
        }
    }
    
    return result;
}

ElementList* ListPixel::getHeader()
{
    return header;
}