#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"

using namespace std;

#define DELAY_CONST 10
#define BOARD_WIDTH 36
#define BOARD_HEIGHT 18

Player *player;
GameMechs *gameMechs;
objPosArrayList curr_player_body; // need the current player position to generate food

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

    gameMechs = new GameMechs(BOARD_WIDTH, BOARD_HEIGHT); // create a GameMechs object with a specified board size on the heap
    player = new Player(gameMechs);

    player->getPlayerPos(curr_player_body);

    gameMechs->generateFood(curr_player_body); // TODO: generate food so it doesnt collide with snake body
}

void GetInput(void)
{
    gameMechs->readInput(); // get the users input and store it in the gameMechs input attribute
}

void RunLogic(void)
{
    if (gameMechs->getInput() == 27)
    {
        gameMechs->setExitTrue(); // set the exit flag true if the users input is the esc key
    }
    if (gameMechs->getInput() == 'p')
        gameMechs->incrementScore(); // increment the gameMechs score attribute by one using the p key
    if (gameMechs->getInput() == 'o')
        gameMechs->setLoseFlag(); // set the loseFlag attribute to true with the o key
    if (gameMechs->getInput() == 'i')
        gameMechs->generateFood(curr_player_body);

    player->updatePlayerDir();
    player->movePlayer();
    player->getPlayerPos(curr_player_body);
}

void DrawScreen(void)
{

    objPos curr_food_pos, temp_body;
    gameMechs->getFoodPos(curr_food_pos);
    bool drawn;

    objPos game_ui[gameMechs->getBoardSizeY()][gameMechs->getBoardSizeX()];

    // Initialize the border and inner spaces in one loop
    for (int i = 0; i < gameMechs->getBoardSizeY(); i++)
    {
        for (int j = 0; j < gameMechs->getBoardSizeX(); j++)
        {
            // drawn = false;

            // for (int k = 0; k < curr_player_body.getSize(); k++)
            // {
            //     curr_player_body.getElement(temp_body, k);
            //     if (temp_body.x == j && temp_body.y == i)
            //     {
            //         MacUILib_printf("Snake Symbol: %c", temp_body.symbol);
            //         drawn = true;
            //         break;
            //     }
            // }

            // // skip to next iteration if the player body is drawn
            // if (drawn)
            //     continue;

            if (i == 0 || i == gameMechs->getBoardSizeY() - 1 || j == 0 || j == gameMechs->getBoardSizeX() - 1)
            {
                MacUILib_printf("#"); // Set border to '#'
            }
            // draw inner spaces
            else if (i == curr_food_pos.y && j == curr_food_pos.x)
            {
                MacUILib_printf("%c", curr_food_pos.getSymbol()); // Set food to 'F'
            }
            else
            {
                MacUILib_printf(" "); // Set inner spaces to ' '
            }
        }
        MacUILib_printf("\n");
    }


    MacUILib_printf("score is %d\n", gameMechs->getScore()); // print the users score at the bottom
    MacUILib_printf("Food Coord is(%d,%d)", curr_food_pos.x, curr_food_pos.y);

    MacUILib_printf("Player position: \n");
    for (int l = 0; l < curr_player_body.getSize(); l++)
    {
        curr_player_body.getElement(temp_body, l);
        MacUILib_printf("<%d,%d> symbol: %c\n", temp_body.x, temp_body.y, temp_body.symbol);
    }
    MacUILib_clearScreen();
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_clearScreen();
    if (gameMechs->getLoseFlagStatus() == true)
        MacUILib_printf("You lost. Final score is %d\n", gameMechs->getScore()); // print the final score if the lose flag is set true
    else if (gameMechs->getExitFlagStatus() == true)
        MacUILib_printf("You have successfully quits"); // print a successful quit message if the exit flag is true
    MacUILib_uninit();

    delete gameMechs;
    delete player;
}
