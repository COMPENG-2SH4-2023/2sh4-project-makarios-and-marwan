#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 1000
#define BOARD_WIDTH 30
#define BOARD_HEIGHT 15


Player *player;
GameMechs *gameMechs;
objPos curr_player_pos; //need the current player position to generate food


void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    while (gameMechs->getExitFlagStatus() == false && gameMechs->getLoseFlagStatus() == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    gameMechs = new GameMechs(BOARD_WIDTH, BOARD_HEIGHT); //create a GameMechs object with a specified board size on the heap
    player = new Player(gameMechs);

    player->getPlayerPos(curr_player_pos);

    gameMechs->generateFood(curr_player_pos);

}

void GetInput(void)
{
    gameMechs->readInput(); //get the users input and store it in the gameMechs input attribute
}

void RunLogic(void)
{
    if(gameMechs->getInput() == 27)
    {
        gameMechs->setExitTrue(); //set the exit flag true if the users input is the esc key
    }
    if(gameMechs->getInput() == 'p')
        gameMechs->incrementScore(); //increment the gameMechs score attribute by one using the p key
    if(gameMechs->getInput() == 'o')
        gameMechs->setLoseFlag(); //set the loseFlag attribute to true with the o key
    if(gameMechs->getInput() == 'i')
        gameMechs->generateFood(curr_player_pos);

    player->updatePlayerDir();
    player->movePlayer();
}

void DrawScreen(void)
{
    // Get the current player position; this will be used to update the game_ui
    player->getPlayerPos(curr_player_pos);
    objPos curr_food_pos;
    gameMechs->getFoodPos(curr_food_pos);

    objPos game_ui[gameMechs->getBoardSizeY()][gameMechs->getBoardSizeX()];
    
    // Initialize the border and inner spaces in one loop
    for (int i = 0; i < gameMechs->getBoardSizeY(); i++)
    {
        for (int j = 0; j < gameMechs->getBoardSizeX(); j++)
        {
            if (i == 0 || i == gameMechs->getBoardSizeY() - 1 || j == 0 || j == gameMechs->getBoardSizeX() - 1)
            {
                game_ui[i][j].setObjPos(i, j, '#'); // Set border symbols to '#'
            }
            else if (i == curr_player_pos.y && j == curr_player_pos.x)
            {
                game_ui[i][j].setObjPos(curr_player_pos); // Set player
            }
            else if (i == curr_food_pos.y && j == curr_food_pos.x)
            {
                game_ui[i][j].setObjPos(curr_food_pos); // Set player
            }
            else
            {
                game_ui[i][j].setObjPos(i, j, ' '); // Set empty spaces to ' '
            }

            // Display the game_ui while initializing
            MacUILib_printf("%c", game_ui[i][j].symbol);
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("score is %d\n", gameMechs->getScore()); //print the users score at the bottom
    MacUILib_printf("Food Coord is(%d,%d)", curr_food_pos.x, curr_food_pos.y);
    
    

    MacUILib_clearScreen();

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_clearScreen();
    if(gameMechs->getLoseFlagStatus() == true)
        MacUILib_printf("You lost. Final score is %d\n", gameMechs->getScore()); //print the final score if the lose flag is set true
    else if(gameMechs->getExitFlagStatus() == true)
        MacUILib_printf("You have successfully quits"); //print a successful quit message if the exit flag is true
    MacUILib_uninit();

    delete gameMechs;
    delete player;
}
