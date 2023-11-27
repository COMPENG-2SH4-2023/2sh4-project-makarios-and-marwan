#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef); // Constructor
        ~Player();

        objPosArrayList* getPlayerPos(); // Upgrade this in iteration 3.
        void updatePlayerDir();
        void movePlayer();
        // TODO: Need more actions in here:
        // after inserting the head, but before removing the tail
        // - check if new head position collides with food
        // - if yes, increment the score in Gm, generate new food,
        // and dont remove the tail
        // otherwise, remove the tail and move on

        //Lastly, add check collision check:
        // - if self-collided
        // -set loseFlag and exitFlag to true (in GM)
        // this will end the game
        //
        //- if ending, you need to differnetiate between win and lose
        // LOST - display "You Lose" and the score
        // WIN - display "ENDGAME" and the score
    
    private:
        objPosArrayList *playerPosList;   // Upgrade this in iteration 3.       
        enum Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif