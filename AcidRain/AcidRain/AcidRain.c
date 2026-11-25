#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Console.h"
#include "DataContainer.h"
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

//게임의 완전한 초기화
void InitGame();
//게임을 종료할 때 호출되는 함수
void OnExitGame();
//인게임에서 게임이 종료되었을 때 호출
void OnGameOver();
//다음 난이도로 변경할 때 호출
void OnNextLevel();
//게임의 전체적인 상태 변경 함수
void ChangeGameState(GameState newState);
//게임의 시간을 갱신
void UpdateTime();
//게임의 정보값을 최신화
void Update();
//게임의 화면을 갱신
void RenderScreen();
void OnRenderMenu();
void OnRenderInGame();
//플레이어 조작을 갱신
void PlayerInput();
//플레이어의 체력을 수정
void EditHp(int amount);

void LockTheMain(int agree)
{
	if (agree == 1)
		return;

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

int main(void)
{
	srand((unsigned int)time(NULL));

	DataContainer_ReadTextData();
	DataContainer_TrySpawnText(30, 0, 0);
}
void InitGame()
{
	Console_SetSize(ScreenWidth, ScreenHeigth);
	currentState = Menu;
	isRunning = 1;
	srand((unsigned int)time(NULL));
	maxHp = 5;
	currentHp = 5;
}
void OnExitGame()
{
	
}
void OnGameOver()
{
}
void OnNextLevel()
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
void Update()
{
	if (currentHp == 0)
	{
		OnGameOver();
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
			OnRenderMenu();
			break;
		case InGame:
			OnRenderInGame();
			break;
	}
}
void OnRenderMenu()
{
	char start[] = "GameStart";
	char exit[] = "Exit";


}
void OnRenderInGame()
{

}

void PlayerInput()
{

}
void EditHp(int amount)
{
	currentHp += amount;
	if (currentHp <= 0)
		currentHp = 0;
	else if (currentHp > maxHp)
		currentHp = maxHp;
}
