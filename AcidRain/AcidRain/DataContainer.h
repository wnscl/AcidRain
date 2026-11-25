#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 21
#define MAX_TEXTS 50

typedef struct TextNode
{
	char *text;
	int xpos;
	int ypos;
	struct TextNode *next;
}TextNode;

char textDatas[MAX_LEN][MAX_TEXTS][MAX_LEN] = { '\0' };
// [길이][단어순서][문자]

int DataContainer_ReadTextData()
{
	FILE* f = NULL;
	errno_t err = fopen_s(&f, "WordDict.txt", "r");
	if (f == NULL)
	{
		printf("단어장 읽기 불가\n");
		return 0;
	}

	int textDataIndex[MAX_LEN] = { 0 }; // 크기를 MAX_LEN(21)으로 수정
	char temp[MAX_LEN] = { '\0' };

	// fgets의 반환값으로 EOF 체크
	while (fgets(temp, MAX_LEN, f) != NULL)
	{
		temp[strcspn(temp, "\r\n")] = '\0'; // \r과 \n 모두 제거
		int length = strlen(temp);

		if (length == 0)
			continue; // 빈 줄이 있을 경우 종료(break) 대신 건너뛰기(continue) 권장

		// 배열 범위 초과 방지
		if (textDataIndex[length] >= MAX_TEXTS)
		{
			printf("길이 %d인 단어의 저장 한도 초과\n", length);
			continue;
		}

		// 인덱스를 length로 통일
		int idx = textDataIndex[length];
		strcpy_s(textDatas[length][idx], sizeof(textDatas[length][idx]), temp);
		printf("%s | L = %d (index: %d)\n", textDatas[length][idx], length, idx);

		textDataIndex[length]++;
	}

	fclose(f); // 파일 닫기 추가
	return 1;
}

void DataContainer_CreateText(int textLength)
{

}