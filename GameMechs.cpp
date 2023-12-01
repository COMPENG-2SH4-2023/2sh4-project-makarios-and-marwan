#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{
    // default constructor
    boardSizeX = 30;
    boardSizeY = 15;
    exitFlag = false;
    loseFlag = false;
    input = 0;
    score = 0;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    // special constructor which allows programmer to set the x and y size of the board
    boardSizeX = boardX;
    boardSizeY = boardY;
    exitFlag = false;
    loseFlag = false;
    input = 0;
    score = 0;
}

// do you need a destructor?

bool GameMechs::getExitFlagStatus()
{
    // returns exit flag
    return exitFlag;
}

void GameMechs::setExitTrue()
{
    // sets exit flag to true which is used to break out of the program loop and print the exit message
    exitFlag = true;
}

bool GameMechs::getLoseFlagStatus()
{
    // returens the lose flag
    return loseFlag;
}

void GameMechs::setLoseFlag()
{
    // sets exit flag to true which is used to break out of the program loop and print the losing message
    loseFlag = true;
}

void GameMechs::readInput()
{
    // checks if user has made a keyboard input and set the input attribute equal to that char
    // if there is no keyboard input then set the attribute to null
    if (MacUILib_hasChar())
    {
        setInput(MacUILib_getChar());
    }
    else
    {
        clearInput();
    }
}

char GameMechs::getInput()
{
    // returns input attribute
    return input;
}

void GameMechs::setInput(char this_input)
{
    // sets the input attribute to the char passed into this method
    input = this_input;
}

void GameMechs::clearInput()
{
    // sets input to 0
    input = 0;
}

int GameMechs::getBoardSizeX()
{
    // returns the horizontal size of the board
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    // returns the vertical size of the board
    return boardSizeY;
}

int GameMechs::getScore()
{
    // returns the score
    return score;
}

void GameMechs::incrementScore()
{
    // increments the score
    score++;
}

void GameMechs::generateFood(objPosArrayList blockedPositions)
{
    // Initialize candidate coordinates and temporary position object
    int candidateX, candidateY;
    objPos tempPos;

    // Initialize bit vectors for X and Y coordinates
    int xCoordinateBitVector[boardSizeX-2] = {0};
    int yCoordinateBitVector[boardSizeY-2] = {0};

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
        candidateX = rand() % (boardSizeX - 2) + 1;
        candidateY = rand() % (boardSizeY - 2) + 1;
    } while (xCoordinateBitVector[candidateX-1] == 1 || yCoordinateBitVector[candidateY-1] == 1);

    // Set the food position to the unblocked position
    foodPos.setObjPos(candidateX, candidateY, 'O');
}

void GameMechs::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos.x, foodPos.y, 'O');
}