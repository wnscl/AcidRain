#include <stdio.h>
#include <time.h>
#include <windows.h>
#include "AcidRain.h"
#include "DataContainer.h"

GameState currentState = Menu;
int currentHp;
int maxHp;

ULONGLONG previousTime;
ULONGLONG currentTime;
double deltaTime;

int InitGame();

int InitGame()
{
	if (DataContainer_Init())
		return 1;

	maxHp = HP;
	currentHp = maxHp;

	return 0;
}

int main()
{
	if (InitGame())
	{
		printf("게임 초기화 단계 실패");
		return;
	}
}

