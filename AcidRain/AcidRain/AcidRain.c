#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Console.h"
#define TargetFrame 100
#define MS 1000.0
#define ScreenWidth 120
#define ScreenHeight 30

typedef enum
{
	Menu = 0,
	InGame,
	Length
} GameState;

int isRunning = 1;
GameState currentState = Menu;

ULONGLONG previousTime;
ULONGLONG currentTime;
double deltaTime;


void ChangeGameState(GameState newState)
{
	if (currentState == newState)
		return;

	currentState = newState;
}

void Update();
void RenderScreen();
void RenderMenu();
void RenderInGame();

void InitGame()
{
	SetConsoleSize(90, 50);
	currentState = Menu;
	isRunning = 1;
}

int main(void)
{
	InitGame();
	
}

void Update()
{
	int a;
}

void RenderScreen()
{
	switch (currentState)
	{
		case Menu:
			RenderMenu();
			break;
		case InGame:
			RenderInGame();
			break;
	}
}
void RenderMenu()
{
	char start[] = "GameStart";
	char exit[] = "Exit";


}
void RenderInGame()
{

}

