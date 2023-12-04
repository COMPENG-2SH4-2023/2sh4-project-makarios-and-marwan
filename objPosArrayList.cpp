#include "objPosArrayList.h"

objPosArrayList::objPosArrayList() // default constructor
{
    aList = new objPos[ARRAY_MAX_CAP];
    sizeList = 0;
    sizeArray = ARRAY_MAX_CAP;
}

objPosArrayList::objPosArrayList(const objPosArrayList &objPosArrayListToCopy) // copy constructor (deep copy)
{
    sizeList = objPosArrayListToCopy.sizeList;
    sizeArray = objPosArrayListToCopy.sizeArray;
    aList = new objPos[sizeArray];
    for (int i = 0; i < sizeList; i++)
    {
        aList[i] = objPosArrayListToCopy.aList[i];
    }
}

// copy method (deep copy)
void objPosArrayList::copy(const objPosArrayList &objPosArrayListToCopy)
{
    delete[] aList; // delete the original array

    sizeList = objPosArrayListToCopy.sizeList;
    sizeArray = objPosArrayListToCopy.sizeArray;
    aList = nullptr;
    if (objPosArrayListToCopy.aList != nullptr) {
        aList = new objPos[sizeArray];
        for (int i = 0; i < sizeList; i++)
        {
            aList[i] = objPosArrayListToCopy.aList[i];
        }
    }
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize() // return the size of the array
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