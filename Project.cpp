#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 1000
#define BOARD_WIDTH 36
#define BOARD_HEIGHT 36

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
    gameMechs->getInput();
}

void RunLogic(void)
{
    player->updatePlayerDir();
    player->movePlayer();
}

void DrawScreen(void)
{
    // Get the current player position; this will be used to update the game_ui
    objPos curr_player_pos;
    player->getPlayerPos(curr_player_pos);

    objPos game_ui[BOARD_WIDTH][BOARD_HEIGHT] = {0};
    
    // Initialize the border and inner spaces in one loop
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        for (int j = 0; j < BOARD_HEIGHT; j++)
        {
            if (i == 0 || i == BOARD_WIDTH - 1 || j == 0 || j == BOARD_HEIGHT - 1)
            {
                game_ui[i][j].setObjPos(i, j, '#'); // Set border symbols to '#'
            }
            else if (i == curr_player_pos.y && j == curr_player_pos.x)
            {
                game_ui[i][j].setObjPos(curr_player_pos); // Set player
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

    MacUILib_clearScreen();
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
