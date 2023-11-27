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

bool exitFlag;
Player *player;
GameMechs *gameMechs;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    while (exitFlag == false)
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

    exitFlag = false;
    gameMechs = new GameMechs(BOARD_WIDTH, BOARD_HEIGHT);
    player = new Player(gameMechs);
}

void GetInput(void)
{
    // gameMechs->getInput();
}

void RunLogic(void)
{
    player->updatePlayerDir();
    player->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    // Get the entire snake position
    objPosArrayList *player_body = player->getPlayerPos();
    objPos temp_body;

    bool drawn;

    // Initialize the border and inner spaces in one loop
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            drawn = false;

            // iterate through the player body
            for (int k = 0; k < player_body->getSize(); k++)
            {
                player_body->getElement(temp_body, k);
                if (temp_body.x == j && temp_body.y == i)
                {
                    MacUILib_printf("%c", temp_body.symbol);
                    drawn = true;
                    break;
                }
            }

            // skip to next iteration if the player body is drawn
            if (drawn == true)
                continue;

            // draw border
            if (i == 0 || i == BOARD_HEIGHT - 1 || j == 0 || j == BOARD_WIDTH - 1)
            {
                MacUILib_printf("%c", '#'); // Set border to '#'
            }
            // draw inner spaces
            else
            {
                MacUILib_printf("%c", ' '); // Set inner spaces to ' '
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Player position: \n");
    for (int l = 0; l < player_body->getSize(); l++)
    {
        player_body->getElement(temp_body, l);
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

    MacUILib_uninit();

    delete gameMechs;
    delete player;
}
