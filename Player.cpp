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
    playerPos.setObjPos(boardSizeX / 2, boardSizeY / 2, '@');
}

Player::~Player()
{
}

void Player::getPlayerPos(objPos &returnPos)
{
    /*
    getPlayerPos:
    1. write the current player position to the returnPos reference
    */

    returnPos = playerPos;
    // returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
}

void Player::setInput()
{
    if (MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }
    else
    {
        input = 0;
    }

}

void Player::updatePlayerDir()
{
    /*
    updatePlayerDir:
    1. Get the input from the GameMechs object
    2. Update the player direction based on the input
    3. Clear the input in the GameMechs object
    */


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
    int BOARD_WIDTH = mainGameMechsRef->getBoardSizeX();
    int BOARD_HEIGHT = mainGameMechsRef->getBoardSizeY();

    switch (myDir)
    {
    case UP:
        playerPos.y = (playerPos.y > 1) ? playerPos.y - 1 : BOARD_HEIGHT - 2; // decrement or wrap around
        break;
    case DOWN:
        playerPos.y = (playerPos.y < BOARD_HEIGHT - 2) ? playerPos.y + 1 : 1; // increment or wrap around
        break;
    case LEFT:
        playerPos.x = (playerPos.x > 1) ? playerPos.x - 1 : BOARD_WIDTH - 2; // decrement or wrap around
        break;
    case RIGHT:
        playerPos.x = (playerPos.x < BOARD_WIDTH - 2) ? playerPos.x + 1 : 1; // increment or wrap around
        break;
    }
}
