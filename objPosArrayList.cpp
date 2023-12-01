#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];
    sizeList = 0;
    sizeArray = ARRAY_MAX_CAP;
}

// copy constructor
objPosArrayList::objPosArrayList(const objPosArrayList &objPosArrayListToCopy)
{
    sizeList = objPosArrayListToCopy.sizeList;
    sizeArray = objPosArrayListToCopy.sizeArray;
    aList = new objPos[sizeArray];
    for (int i = 0; i < sizeList; i++)
    {
        aList[i] = objPosArrayListToCopy.aList[i];
    }
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList; // remember to delete [] to free up the the instances of the array
                    // otherwise, only the first instance will be deleted
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    /*
    insertHead:
    1. check if the array is full
        - if yes, do nothing
        - if no, continue
    2. shift all elements to the right by 1
    3. insert the new element at the head
    4. increment sizeList
    */
    if (sizeList >= sizeArray)
    {
        return;
    }
    else
    {
        for (int i = sizeList; i > 0; i--)
        {
            aList[i] = aList[i - 1];
        }
        aList[0] = thisPos;
        sizeList++;
    }
}

void objPosArrayList::insertTail(objPos thisPos)
{
    /*
    insertTail:
    1. check if the array is full
        - if yes, do nothing
        - if no, continue
    2. insert the new element at the tail
    3. increment sizeList
    */
    if (sizeList >= sizeArray)
    {
        return;
    }
    else
    {
        aList[sizeList] = thisPos;
        sizeList++;
    }
}

void objPosArrayList::removeHead()
{
    /*
    removeHead:
    1. check if the array is empty
        - if yes, do nothing
        - if no, continue
    2. shift all elements to the left by 1
    3. decrement sizeList
    */
    if (sizeList <= 0)
    {
        return;
    }
    else
    {
        for (int i = 0; i < sizeList - 1; i++)
        {
            aList[i] = aList[i + 1];
        }
        sizeList--;
    }
}

void objPosArrayList::removeTail()
{
    /*
    removeTail:
    1. check if the array is empty
        - if yes, do nothing
        - if no, continue
    2. remove the element at the tail
    3. decrement sizeList
    */
    if (sizeList <= 0)
    {
        return;
    }
    else
    {
        aList[sizeList - 1] = objPos();
        sizeList--;
    }
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[sizeList - 1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos.setObjPos(aList[index]);
}