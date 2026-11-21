#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Console.h"
#define TargetFrame 60
#define MS 1000.0
#define ScreenWidth 90
#define ScreenHeigth 50

typedef enum
{
	Menu = 0,
	InGame,
	Length
} GameState;

int isRunning = 1;
GameState currentState = Menu;
int maxHp = 0;
int currentHp = 0;

ULONGLONG previousTime;
ULONGLONG currentTime;
double deltaTime;

void InitGame()
{
	Console_SetSize(ScreenWidth, ScreenHeigth);
	currentState = Menu;
	isRunning = 1;
	maxHp = 5;
	currentHp = 5;


}
void OnExitGame()
{

}
void GameOver()
{
}
void ChangeGameState(GameState newState)
{
	if (currentState == newState)
		return;

	currentState = newState;
}
void UpdateTime()
{
	currentTime = GetTickCount64();
	deltaTime = (currentTime - previousTime) / MS;
	previousTime = currentTime;
}
void Update();
void RenderScreen();
void RenderMenu();
void RenderInGame();
void PlayerInput();
int EditHp(int amount);

int main(void)
{
	InitGame();

	previousTime = GetTickCount64();
	float targetFrameSeconds = 1 / (float)TargetFrame;
	float t = targetFrameSeconds * 1000;

	while (isRunning)
	{
		UpdateTime();
		PlayerInput();
		if (isRunning == 0)
		{
			OnExitGame();
			break;
		}
		Update();
		RenderScreen();
		Sleep(t);
	}
}

void Update()
{
	if (currentHp == 0)
	{
		GameOver();
		ChangeGameState(Menu);
	}
	switch (currentState)
	{
		//함수 포인터 콜백으로 해야하는 행위함수를 변수화 시켜 게임 정보 최신화
		case Menu:

			break;
		case InGame:
			
			break;
	}
}

void RenderScreen()
{
	Console_Clear();
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

void PlayerInput()
{

}
int EditHp(int amount)
{
	currentHp += amount;
	if (currentHp <= 0)
		currentHp = 0;
	else if (currentHp > maxHp)
		currentHp = maxHp;
}
