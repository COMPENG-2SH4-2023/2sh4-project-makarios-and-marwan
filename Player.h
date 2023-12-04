#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "Food.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
public:
    enum Dir
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        STOP
    }; // This is the direction state

    Player(GameMechs *thisGMRef); // Constructor
    ~Player();

    objPosArrayList getPlayerPos();
    void getPlayerPos(objPosArrayList &returnPos);
    void updatePlayerDir();
    void movePlayer(int sizeX, int sizeY);
    void setFoodObj(Food currFoodObj);
    void getFoodPos(objPos &currFoodPos);
    void checkSelfColision();

private:
    objPosArrayList *playerPosList;
    enum Dir myDir;
    Food foodObj;
    GameMechs *mainGameMechsRef;
};

#endif