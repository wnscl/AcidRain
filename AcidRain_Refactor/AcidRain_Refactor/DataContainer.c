#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "DataContainer.h"

TextNode* head;

// [길이][단어순서][문자]
static char textDatas[MAX_LEN][MAX_TEXTS][MAX_LEN] = { '\0' };

//특정 길이의 단어데이터가 몇개인지
static int textDataCounts[MAX_LEN] = { 0 };

//생성 후 다음 생성까지 대기 시간
float spawnIntervalTime[DIFF_DATA_LEVEL_COUNT];

//1회 생성 당 생성되는 단어 개수
int spawnTextAmount[DIFF_DATA_LEVEL_COUNT];

//단어 생성 시 최소 길이 ~ 최대 길이
int spawnMinLength[DIFF_DATA_LEVEL_COUNT];
int spawnMaxLength[DIFF_DATA_LEVEL_COUNT];

//추락시간 0.5 라면 0.5초마다 모든 text의 y 좌표값이 + 1 (+여야 밑으로 감)
float fallDuration[DIFF_DATA_LEVEL_COUNT];

//난이도 당 최대 생성 개수
int maxSpawnCount[DIFF_DATA_LEVEL_COUNT];

//DataContainer_이름 <- public 함수
 
static void ReadTexts(FILE* f);
static void ReadDiffs(FILE* f);
static void WriteDiffData(int diffLevel, int caseNum, char* data);
static void SpawnText(int length, int x);
static void RemoveText(TextNode* prev, TextNode* curr);

int DataContainer_Init()
{
	FILE* f = NULL;
	errno_t err = fopen_s(&f, "WordDict.txt", "r");
	if (f == NULL)
		return 1;
	ReadTexts(f);
	if (fclose(f))
		return 1;

	err = fopen_s(&f, "DiffData.txt", "r");
	if (f == NULL)
		return 1;
	ReadDiffs(f);
	if (fclose(f))
		return 1;

	return 0;
}
static void ReadTexts(FILE* f)
{
	char temp[MAX_LEN] = { '\0' };

	while (fgets(temp, MAX_LEN, f) != NULL)
	{
		temp[strcspn(temp, "\r\n")] = '\0'; // \r과 \n 모두 제거
		int length = strlen(temp);

		if (length == 0)
			continue;

		if (textDataCounts[length] >= MAX_TEXTS)
			continue;

		int idx = textDataCounts[length];
		strcpy_s(textDatas[length][idx], sizeof(textDatas[length][idx]), temp);
		printf("%s | L = %d (index: %d)\n", textDatas[length][idx], length, idx);

		textDataCounts[length]++;
	}
}
static void ReadDiffs(FILE* f)
{
	char temp[MAX_LEN] = { '\0' };
	int typeIdx = 0;
	int levelIdx = 0;
	while (fgets(temp, MAX_LEN, f) != NULL && levelIdx < DIFF_DATA_LEVEL_COUNT)
	{
		WriteDiffData(levelIdx, typeIdx, temp);
		typeIdx++;
		if (typeIdx == DIFF_DATA_TYPE_COUNT)
		{
			typeIdx = 0;
			levelIdx++;
		}
	}
}
static void WriteDiffData(int diffLevel, int caseNum, char* data)
{
	switch (caseNum)
	{
	case 0:
		spawnIntervalTime[diffLevel] = (float)atof(data);
		break;
	case 1:
		spawnTextAmount[diffLevel] = (int)atoi(data);
		break;
	case 2:
		spawnMinLength[diffLevel] = (int)atoi(data);
		break;
	case 3:
		spawnMaxLength[diffLevel] = (int)atoi(data);
		break;
	case 4:
		fallDuration[diffLevel] = (float)atof(data);
		break;
	case 5:
		maxSpawnCount[diffLevel] = (int)atoi(data);
		break;
	default:
		printf("없는 난이도 데이터 접근");
		break;
	}
}
void DataContainer_SpawnText(int min, int max, int x)
{
	if (min == 0 || max == 0)
		return;

	int randomLength = rand() % (max - min + 1) + min;
	if (randomLength % 2 != 0)
		randomLength += 1;
	SpawnText(randomLength, x);
}
static void SpawnText(int length, int x)
{
	int n = textDataCounts[length];
	if (n <= 0)
		return;

	int randomNum = (rand() % n);

	TextNode* newNode = (TextNode*)malloc(sizeof(TextNode));
	if (newNode == NULL)
		return;

	newNode->text = textDatas[length][randomNum];
	newNode->xPos = x;
	newNode->yPos = 0;
	newNode->next = NULL;

	if (head == NULL)
		head = newNode;	
	else
	{
		TextNode* curr = head;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = newNode;
	}
}
void DataContainer_CompareText(char* inputText)
{
	if (head == NULL)
		return;

	TextNode* curr = head;
	TextNode* prev = NULL;
	while (curr != NULL)
	{
		if (curr->text != NULL && strcmp(curr->text, inputText) == 0)
		{
			RemoveText(prev, curr);
			return;
		}

		prev = curr;
		curr = curr->next;
	}
}
static void RemoveText(TextNode* prev, TextNode* curr)
{
	if (prev == NULL)
		head = curr->next;
	else
		prev->next = curr->next;

	free(curr);
}
void DataContainer_DropAllText()
{
	if (head == NULL)
		return;

	TextNode* curr = head;
	
	while (curr != NULL)
	{
		curr->yPos += 1;
		curr = curr->next;
	}
}