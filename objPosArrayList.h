#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 200

#include "objPos.h"

class objPosArrayList
{
private:
    objPos *aList;
    int sizeList;
    int sizeArray;

public:
    // Constructor, Copy Constructor, Destructor
    objPosArrayList();
    objPosArrayList(const objPosArrayList &objPosArrayListToCopy);
    ~objPosArrayList();
    void copy(const objPosArrayList &objPosArrayListToCopy);

    int getSize();
    void insertHead(objPos thisPos);
    void insertTail(objPos thisPos);
    void removeHead();
    void removeTail();

    void getHeadElement(objPos &returnPos);
    void getTailElement(objPos &returnPos);
    void getElement(objPos &returnPos, int index);
};

#endif