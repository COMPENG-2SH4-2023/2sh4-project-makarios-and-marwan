#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "objPosArrayList.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 1000
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

    gameMechs = new GameMechs(BOARD_WIDTH, BOARD_HEIGHT); // create a GameMechs object with a specified board size on the heap
    player = new Player(gameMechs);
    curr_food = new Food();

    player->getPlayerPos(curr_player_body); // get the player position and store it in the curr_player_body objPosArrayList
    curr_food->generateFood(curr_player_body, gameMechs->getBoardSizeX(), gameMechs->getBoardSizeY()); // generate a food position based on the player position
}

void GetInput(void)
{
    gameMechs->readInput(); // get the users input and store it in the gameMechs input attribute
}

void RunLogic(void)
{
    char userInput = gameMechs->getInput();



    switch (userInput)
    {
    case 27:
        gameMechs->setExitTrue(); // set the exit flag true if the user's input is the ESC key
        break;
    case 'p':
        gameMechs->incrementScore(); // increment the gameMechs score attribute by one using the p key
        break;
    case 'o':
        gameMechs->setLoseFlag(); // set the loseFlag attribute to true with the o key
        break;
    case 'i':
        curr_food->generateFood(curr_player_body, gameMechs->getBoardSizeX(), gameMechs->getBoardSizeY());
        break;
    }

    player->updatePlayerDir();
    player->movePlayer();
    // Get the current player position and generate a new food position
    player->getPlayerPos(curr_player_body); // TODO: THERE IS A BUG HERE. COPY CONSTRUCTOR!!!
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    int boardSizeX = gameMechs->getBoardSizeX();
    int boardSizeY = gameMechs->getBoardSizeY();
    bool drawn;
    objPos curr_food_pos; 
    objPos temp_body;

    curr_food->getFoodPos(curr_food_pos);

    // Initialize the border and inner spaces in one loop
    for (int i = 0; i < boardSizeY; i++)
    {
        for (int j = 0; j < boardSizeX; j++)
        {
            drawn = false;

            for (int k = 0; k < curr_player_body.getSize(); k++)
            {
                curr_player_body.getElement(temp_body, k);
                if (temp_body.x == j && temp_body.y == i)
                {
                    MacUILib_printf("%c", temp_body.symbol);
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


    // DEBUGGING PURPOSES
    MacUILib_printf("score is %d\n", gameMechs->getScore()); 
    MacUILib_printf("\n");

    MacUILib_printf("Food Coord is(%d,%d)\n", curr_food_pos.x, curr_food_pos.y);
    MacUILib_printf("\n");

    MacUILib_printf("Player position DRAW SCREEN: \n");
    for (int l = 0; l < curr_player_body.getSize(); l++)
    {
        curr_player_body.getElement(temp_body, l);
        MacUILib_printf("<%d,%d> symbol: %c\n", temp_body.x, temp_body.y, temp_body.symbol);
    }
    
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
