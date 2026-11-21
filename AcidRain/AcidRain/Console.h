#include <windows.h>
#include <stdio.h>

enum {
    BLACK,
    DARK_BLUE,
    DARK_GREEN,
    DARK_SKYBLUE,
    DARK_RED,
    DARK_VOILET,
    DAKR_YELLOW,
    GRAY,
    DARK_GRAY,
    BLUE,
    GREEN,
    SKYBLUE,
    RED,
    VIOLET,
    YELLOW,
    WHITE,
};
/// <summary>
/// 콘솔 커서이동
/// </summary>
void Console_Gotoxy(int x, int y)
{
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
/// <summary>
/// 콘솔 크기 조정
/// </summary>
void Console_SetSize(int width, int height)
{
	char setText[100];
	snprintf(setText, sizeof(setText), "mode con: cols=%d lines=%d", width, height);
	system(setText);
}
/// <summary>
/// 콘솔 초기화 커서는 0,0 좌표로 이동됨
/// </summary>
void Console_Clear()
{
	printf("\x1b[2J\x1b[H");
	fflush(stdout);
}
/// <summary>
/// 콘솔 텍스트 색상 변경
/// </summary>
/// <param name="text">색상</param>
void Console_SetColor(unsigned short text) 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

