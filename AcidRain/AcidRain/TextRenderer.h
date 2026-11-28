#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Console.h"

int w, h = 0;

char *screenTextInfo = NULL;
//define으로 정의된 게임 화면 크기에 따라 w, h 값으로 동적 배열 크기 할당
//좌표는 index값으로 조회하여 해당 인덱스에 char ''를 넣어주는 방식으로 화면 갱신
// x + (y * w) 로 좌표 index위치값 계산 현재 \n과 \0이 들어갈 칸이 필요함으로
// x + (y * (w + 2))로 계산

void TextRenderer_SetScreenSizeData(int width, int height)
{
	w = width;
	h = height;
	Console_SetSize(width, height);
	screenTextInfo = (char*)malloc(sizeof(char) * ((width + 2) * height));
}
void TextRenderer_TextComplete()
{
	for (int i = 0; i < h; i++)
	{
		Console_Gotoxy(w - 2, i);
		printf("\n");
		Console_Gotoxy(w - 1, i);
		printf("\0");
	}
}
void TextRenderer_DrawAllText(struct TextNode* head)
{
	if (head == NULL)
		return;

	TextNode* curr;
	curr = head;
	while (curr != NULL)
	{
		Console_Gotoxy(curr->xPos, curr->yPos);
		printf("%s", curr->text);
		curr = curr->next;
	}
}
void TextRenderer_DrawGameScene(struct TextNode* head)
{
	Console_Clear();
	TextRenderer_DrawAllText(head);
	TextRenderer_TextComplete();
}
void TextRenderer_DrawMainScene()
{
	system("cls");
}