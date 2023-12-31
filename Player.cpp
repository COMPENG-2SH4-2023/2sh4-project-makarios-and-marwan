#include "Player.h"
#include "Food.h"
#include "MacUILib.h"

Player::Player(GameMechs *thisGMRef)
{
    /*
    Player Constructor:
    1. Get the board size
    2. Set the player position to the center of the board
    3. Set the player direction to STOP
    */

    int boardSizeX = thisGMRef->getBoardSizeX();
    int boardSizeY = thisGMRef->getBoardSizeY();

    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    objPos tempPos;
    tempPos.setObjPos(boardSizeX / 2, boardSizeY / 2, '@');

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);
}

Player::~Player()
{
    /*
    Player Destructor:
    1. Delete the playerPosList
    */

    delete playerPosList;
}

// void Player::getPlayerPos(objPosArrayList &returnPos)
// {
//     /*
//     getPlayerPos:
//     1. Return the player position
//     */

//    // Uses the copy constructor to return a copy of the playerPosList
//    // Copy constructor: objPosArrayList::objPosArrayList(const objPosArrayList &objPosArrayListToCopy)

//     returnPos = *playerPosList;
// }

objPosArrayList Player::getPlayerPos()
{
    /*
    getPlayerPos:
    1. Return the player position
    */
    return *playerPosList;
}

void Player::updatePlayerDir()
{
    /*
    updatePlayerDir:
    1. Get the input from the GameMechs object
    2. Update the player direction based on the input
    3. Clear the input in the GameMechs object
    */
    char input = mainGameMechsRef->getInput();

    // WASD keys
    if (input != 0)
    {
        switch (myDir)
        {
        case STOP:
            switch (input)
            {
            case 'w':
                myDir = UP;
                break;
            case 's':
                myDir = DOWN;
                break;
            case 'a':
                myDir = LEFT;
                break;
            case 'd':
                myDir = RIGHT;
                break;
            }
            break;

        case UP:
        case DOWN:
            switch (input)
            {
            case 'a':
                myDir = LEFT;
                break;
            case 'd':
                myDir = RIGHT;
                break;
            }
            break;

        case LEFT:
        case RIGHT:
            switch (input)
            {
            case 'w':
                myDir = UP;
                break;
            case 's':
                myDir = DOWN;
                break;
            }
            break;
        }
    }

    mainGameMechsRef->clearInput();
}

void Player::movePlayer(int sizeX, int sizeY)
{
    /*
    movePlayer:
    1. Update the player position based on the player direction
    2. Wrap around the player position if necessary
    */
    // these are used for determining if the snake head colides with a food object
    objPos foodObjPos, snakeBodyNode;
    foodObj.getFoodPos(foodObjPos);
    playerPosList->getHeadElement(snakeBodyNode);

    objPos curr_head; // holding the pos info of the current head
    playerPosList->getHeadElement(curr_head);

    int BOARD_WIDTH = mainGameMechsRef->getBoardSizeX();
    int BOARD_HEIGHT = mainGameMechsRef->getBoardSizeY();

    switch (myDir)
    {
    case UP:
        if(curr_head.getY() > 1)
            curr_head.setY(curr_head.getY() - 1);
        else
            curr_head.setY(BOARD_HEIGHT-2);
        break;
    case DOWN:
        if(curr_head.getY()< BOARD_HEIGHT - 2)
            curr_head.setY(curr_head.getY() + 1);
        else
            curr_head.setY(1);
        break;
    case LEFT:
        if(curr_head.getX() > 1)
            curr_head.setX(curr_head.getX()-1);
        else
            curr_head.setX(BOARD_WIDTH - 2);
        break;
    case RIGHT:
        if(curr_head.getX() < BOARD_WIDTH - 2)
            curr_head.setX(curr_head.getX() + 1);
        else
            curr_head.setX(1);
        break;
    }


    if(snakeBodyNode.getX() == foodObjPos.getX() && snakeBodyNode.getY() == foodObjPos.getY())
    {

        playerPosList->insertHead(curr_head);
        foodObj.generateFood(*playerPosList, sizeX, sizeY);
        mainGameMechsRef->incrementScore();

    }
    else
    {
        // new current head should be inserted to the head of the list
        playerPosList->insertHead(curr_head);

        // then remove the tail of the list
        playerPosList->removeTail();
    }
}

void Player::setFoodObj(Food currFoodObj)
{
    foodObj = currFoodObj;
}


void Player::getFoodPos(objPos &currFoodPos)
{
    objPos tempPos;
    foodObj.getFoodPos(tempPos);
    currFoodPos.setObjPos(tempPos);
}

void Player::checkSelfColision()
{
    objPos snakeHead, snakeBody;
    playerPosList->getHeadElement(snakeHead);
    for(int i = 1; i < playerPosList->getSize(); i++)
    {
        playerPosList->getElement(snakeBody, i);
        if(snakeHead.getX() == snakeBody.getX() && snakeHead.getY() == snakeBody.getY())
            mainGameMechsRef->setLoseFlag();
    }
}