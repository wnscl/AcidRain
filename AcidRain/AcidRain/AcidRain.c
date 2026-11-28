#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DataContainer.h"
#include "TextRenderer.h"
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

int main(void)
{
	InitGame();
	DataContainer_TrySpawnText(6,45,0);
	DataContainer_TrySpawnText(10, 65, 5);
	DataContainer_TrySpawnText(8, 15, 2);

	int testC = 0;
	while (testC < 50)
	{
		DataContainer_MoveAllTextDown();
		TextRenderer_DrawGameScene(head);
		testC++;
		Sleep(300);
	}

}
void InitGame()
{
	int errorDetect = 1;

	currentState = Menu;
	isRunning = 1;
	srand((unsigned int)time(NULL));
	maxHp = 5;
	currentHp = 5;

	errorDetect = DataContainer_ReadTextData();
	if (errorDetect == 0)
	{
		printf("초기 로드 오류 _ 단어장 데이터 초기화 실패");
		return;
	}
	errorDetect = DataContainer_ReadDiffData();
	if (errorDetect == 0)
	{
		printf("초기 로드 오류 _ 난이도 데이터 초기화 실패");
		return;
	}

	if (errorDetect == 1)
		printf("게임 초기화 성공\0");

	TextRenderer_DrawMainScene();
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
