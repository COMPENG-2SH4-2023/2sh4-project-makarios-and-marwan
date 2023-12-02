#include "Food.h"
#include "MacUILib.h"

Food::Food()
{
    foodPos.setObjPos(7,7,'o');
}

Food::~Food()
{
    
}

void Food::generateFood(objPosArrayList blockedPositions, int sizeX, int sizeY)
{
    // Initialize candidate coordinates and temporary position object
    int candidateX, candidateY;
    objPos tempPos;

    // Initialize bit vectors for X and Y coordinates
    int xCoordinateBitVector[sizeX-2] = {0};
    int yCoordinateBitVector[sizeY-2] = {0};

    // Mark blocked positions in the bit vectors
    for(int i = 0; i < blockedPositions.getSize(); i++)
    {
        blockedPositions.getElement(tempPos, i);
        xCoordinateBitVector[tempPos.x-1] = 1;
        yCoordinateBitVector[tempPos.y-1] = 1;
    }

    // Generate random candidate coordinates until an unblocked position is found
    do
    {
        candidateX = rand() % (sizeX - 2) + 1;
        candidateY = rand() % (sizeY - 2) + 1;
    } while (xCoordinateBitVector[candidateX-1] == 1 || yCoordinateBitVector[candidateY-1] == 1);

    // Set the food position to the unblocked position
    foodPos.setObjPos(candidateX, candidateY, 'O');
}

void Food::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos.x, foodPos.y, 'O');
}