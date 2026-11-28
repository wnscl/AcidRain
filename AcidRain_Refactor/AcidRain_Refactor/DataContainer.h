#pragma once
#define MAX_LEN 21
#define MAX_TEXTS 50
#define DIFF_DATA_TYPE_COUNT 6
#define DIFF_DATA_LEVEL_COUNT 10

typedef struct TextNode
{
	char* text;
	int xPos;
	int yPos;
	struct TextNode* next;
}TextNode;

extern TextNode* head;

extern float spawnIntervalTime[DIFF_DATA_LEVEL_COUNT];
extern int spawnTextAmount[DIFF_DATA_LEVEL_COUNT];
extern int spawnMinLength[DIFF_DATA_LEVEL_COUNT];
extern int spawnMaxLength[DIFF_DATA_LEVEL_COUNT];
extern float fallDuration[DIFF_DATA_LEVEL_COUNT];
extern int maxSpawnCount[DIFF_DATA_LEVEL_COUNT];

//DataContainer_이름 <- public 함수

int DataContainer_Init();
void DataContainer_SpawnText(int min, int max, int x);
void DataContainer_CompareText(char* inputText);
void DataContainer_DropAllText();