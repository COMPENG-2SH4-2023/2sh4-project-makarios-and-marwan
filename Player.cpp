#include "Player.h"
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
    // playerPos.setObjPos(boardSizeX / 2, boardSizeY / 2, '@'); not true anymore
    objPos tempPos;
    tempPos.setObjPos(boardSizeX / 2, boardSizeY / 2, '@');

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);

    // For bebugging purposes
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
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

void Player::getPlayerPos(objPosArrayList &returnPos)
{
    /*
    getPlayerPos:
    1. write the current player position to the returnPos reference
    */

    returnPos = *playerPosList;
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

void Player::movePlayer()
{
    /*
    movePlayer:
    1. Update the player position based on the player direction
    2. Wrap around the player position if necessary
    */

    objPos curr_head; // holding the pos info of the current head
    playerPosList->getHeadElement(curr_head);

    int BOARD_WIDTH = mainGameMechsRef->getBoardSizeX();
    int BOARD_HEIGHT = mainGameMechsRef->getBoardSizeY();

    switch (myDir)
    {
    case UP:
        curr_head.y = (curr_head.y > 1) ? curr_head.y - 1 : BOARD_HEIGHT - 2; // decrement or wrap around
        break;
    case DOWN:
        curr_head.y = (curr_head.y < BOARD_HEIGHT - 2) ? curr_head.y + 1 : 1; // increment or wrap around
        break;
    case LEFT:
        curr_head.x = (curr_head.x > 1) ? curr_head.x - 1 : BOARD_WIDTH - 2; // decrement or wrap around
        break;
    case RIGHT:
        curr_head.x = (curr_head.x < BOARD_WIDTH - 2) ? curr_head.x + 1 : 1; // increment or wrap around
        break;
    }

    // new current head should be inserted to the head of the list
    playerPosList->insertHead(curr_head);

    // then remove the tail of the list
    playerPosList->removeTail();
}
