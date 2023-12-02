#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;


class Food
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    private:
        objPos foodPos;

    public:
        Food();
        ~Food();

        void generateFood(objPosArrayList blockedPositions, int sizeX, int sizeY);
        void getFoodPos(objPos &returnPos);
};

#endif