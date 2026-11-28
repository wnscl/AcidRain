#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN 21
#define MAX_TEXTS 50
#define DIFF_DATA_TYPE_COUNT 6
#define DIFF_DATA_LEVEL_COUNT 10

typedef struct TextNode
{
	char *text;
	int xPos;
	int yPos;
	struct TextNode* next;
}TextNode;

// [길이][단어순서][문자]
char textDatas[MAX_LEN][MAX_TEXTS][MAX_LEN] = { '\0' };

//특정 길이의 단어데이터가 몇개인지
int textDataIndex[MAX_LEN] = { 0 };

TextNode* head;

float spawnIntervalTime[DIFF_DATA_LEVEL_COUNT];
//생성 후 다음 생성까지 대기 시간
int spawnTextAmount[DIFF_DATA_LEVEL_COUNT];
//1회 생성 당 생성되는 단어 개수
int spawnMinLength[DIFF_DATA_LEVEL_COUNT];
int spawnMaxLength[DIFF_DATA_LEVEL_COUNT];
//단어 생성 시 최소 길이 ~ 최대 길이
float fallDuration[DIFF_DATA_LEVEL_COUNT];
//추락시간 0.5 라면 0.5초마다 모든 text의 y 좌표값이 + 1 (+여야 밑으로 감)
int maxSpawnCount[DIFF_DATA_LEVEL_COUNT];
//난이도 당 최대 생성 개수

int DataContainer_ReadTextData()
{
	FILE* f = NULL;
	errno_t err = fopen_s(&f, "WordDict.txt", "r");
	if (f == NULL)
	{
		printf("단어장 읽기 불가\n");
		return 0;
	}

	char temp[MAX_LEN] = { '\0' };

	while (fgets(temp, MAX_LEN, f) != NULL)
	{
		temp[strcspn(temp, "\r\n")] = '\0'; // \r과 \n 모두 제거
		int length = strlen(temp);

		if (length == 0)
			continue;

		if (textDataIndex[length] >= MAX_TEXTS)
		{
			printf("길이 %d인 단어의 저장 한도 초과\n", length);
			continue;
		}

		int idx = textDataIndex[length];
		strcpy_s(textDatas[length][idx], sizeof(textDatas[length][idx]), temp);
		printf("%s | L = %d (index: %d)\n", textDatas[length][idx], length, idx);

		textDataIndex[length]++;
	}

	fclose(f); // 파일 닫기 추가
	return 1;
}
void DataContainer_WriteDiffData(int diffLevel, int caseNum, char* data)
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
int DataContainer_ReadDiffData()
{
	FILE* f = NULL;
	errno_t err = fopen_s(&f, "DifficultData.txt", "r");
	if (f == NULL)
	{
		printf("난이도 데이터 텍스트 파일 읽기 불가\n");
		return 0;
	}

	char temp[MAX_LEN] = { '\0' };
	int typeIdx = 0;
	int levelIdx = 0;

	while (fgets(temp, MAX_LEN, f) != NULL && levelIdx < DIFF_DATA_LEVEL_COUNT)
	{
		DataContainer_WriteDiffData(levelIdx, typeIdx, temp);
		typeIdx++;
		if (typeIdx == DIFF_DATA_TYPE_COUNT)
		{
			typeIdx = 0;
			levelIdx++;
		}
	}

	fclose(f);
	return 1;
}
int DataContainer_TrySpawnText(int textLength, int x, int y)
{
	//주어진 텍스트 길이값의 배열 크기값(textdataIndex)으로 난수값 생성
	//생성된 난수값에 해당하는 단어로 textnode 구조체 생성
	//가장 마지막 노드가 됨

	if (textLength < 0 || textLength > MAX_LEN || (textLength % 2) != 0)
		return 0;

	int n = textDataIndex[textLength];
	int randomNum = (rand() % n);

	TextNode* curr = head;
	TextNode* newTextNode = (TextNode*)malloc(sizeof(TextNode));
	if (newTextNode == NULL)
		return 0;
	newTextNode->text = textDatas[textLength][randomNum];
	newTextNode->xPos = x;
	newTextNode->yPos = y;
	newTextNode->next = NULL;

	if (head == NULL)
	{
		head = newTextNode;
		return 1;
	}

	while (curr->next != NULL)
		curr = curr->next;
	curr->next = newTextNode;
	return 1;
}
int DataContainer_TryRemoveText(char *inputText)
{
	if (inputText == NULL || head == NULL)
		return 0;

	TextNode *curr = head;
	TextNode *prev = NULL;
	while (curr != NULL)
	{
		if (curr->text != NULL && strcmp(curr->text, inputText) == 0)
		{
			if (prev == NULL)
				head = curr->next;
			else
				prev->next = curr->next;
			free(curr);
			return 1;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return 0;
}
void DataContainer_MoveAllTextDown()
{
	TextNode* curr;
	curr = head;

	while (curr != NULL)
	{
		if (curr->yPos == NULL || curr->yPos < 0)
		{
			//게임에 버그를 띄우는 기능을 추가해야함
			break;
		}
		curr->yPos += 1;
		curr = curr->next;
	}
}