#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{

private:
    char input;
    bool exitFlag; // used to break out of the program loop and print the exit message
    bool loseFlag; // used to break out of the program loop and print the losing message
    int score;
    int boardSizeX;
    int boardSizeY;

public:
    // Constructors
    GameMechs();
    GameMechs(int boardX, int boardY);

    // Exit Flag
    bool getExitFlagStatus();
    void setExitTrue();

    // Lose Flag
    bool getLoseFlagStatus();
    void setLoseFlag();

    // Input
    void readInput(); // Reads the players keyboard input
    char getInput();  // Return the current input class attribute
    void setInput(char this_input);
    void clearInput();

    // Board Size
    int getBoardSizeX();
    int getBoardSizeY();

    // Score
    int getScore();
    void incrementScore();
};

#endif