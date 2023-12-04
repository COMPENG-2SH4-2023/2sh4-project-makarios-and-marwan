#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000
#define BOARD_WIDTH 30
#define BOARD_HEIGHT 15

Player *player;                   // create a player object on the heap
GameMechs *gameMechs;             // create a GameMechs object on the heap
objPosArrayList curr_player_body; // create a objPosArrayList object on the stack
Food *curr_food;

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

    // Initialize the game mechanics, player, and food instances
    gameMechs = new GameMechs(BOARD_WIDTH, BOARD_HEIGHT);
    player = new Player(gameMechs);
    curr_food = new Food();

    // store the player position in the curr_player_body objPosArrayList
    curr_player_body.copy(player->getPlayerPos());

    // generate a food position based on the player position
    curr_food->generateFood(curr_player_body, gameMechs->getBoardSizeX(), gameMechs->getBoardSizeY());

    // set the food object in the player object
    player->setFoodObj(*curr_food);
}

void GetInput(void)
{
    // get the users input and store it in the gameMechs input attribute
    gameMechs->readInput();
}

void RunLogic(void)
{
    // get the user input
    char userInput = gameMechs->getInput();

    // check if the user input exits the game
    if (userInput == 27)
    {
        gameMechs->setExitTrue();
    }

    // update the player direction based on the user input
    player->updatePlayerDir();
    player->movePlayer(gameMechs->getBoardSizeX(), gameMechs->getBoardSizeY());

    // After the player moves, update the player position in the curr_player_body objPosArrayList
    curr_player_body.copy(player->getPlayerPos());
    player->checkSelfColision();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    // get the board size
    int boardSizeX = gameMechs->getBoardSizeX();
    int boardSizeY = gameMechs->getBoardSizeY();

    bool drawn; // a flag to check if the player body is drawn

    // dummy variables
    objPos curr_food_pos;
    objPos temp_body;

    // update dummy variables
    curr_food->getFoodPos(curr_food_pos);
    player->getFoodPos(curr_food_pos);

    // draw the game
    for (int i = 0; i < boardSizeY; i++)
    {
        for (int j = 0; j < boardSizeX; j++)
        {
            drawn = false;

            // draw the player body
            for (int k = 0; k < curr_player_body.getSize(); k++)
            {
                curr_player_body.getElement(temp_body, k);
                if (temp_body.getX() == j && temp_body.getY() == i)
                {
                    MacUILib_printf("%c", temp_body.getSymbol());
                    drawn = true;
                    break;
                }
            }

            // skip to next iteration if the player body is drawn
            if (drawn)
                continue;

            if (i == 0 || i == boardSizeY - 1 || j == 0 || j == boardSizeX - 1)
            {
                MacUILib_printf("#"); // Set border to '#'
            }
            // draw inner spaces
            else if (i == curr_food_pos.getY() && j == curr_food_pos.getX())
            {
                MacUILib_printf("%c", curr_food_pos.getSymbol()); // Print food
            }
            else
            {
                MacUILib_printf(" "); // Set inner spaces to ' '
            }
        }
        MacUILib_printf("\n");
    }

    // print the score
    MacUILib_printf("score is %d\n", gameMechs->getScore());
    MacUILib_printf("\n");
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
    delete curr_food;
}
