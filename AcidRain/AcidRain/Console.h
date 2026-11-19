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


void Console_SetSize(int width, int height)
{
	char setText[100];
	snprintf(setText, sizeof(setText), "mode con: cols=%d lines=%d", width, height);
	system(setText);
}
void Console_Clear()
{
	system("cls");
}
void Console_SetColor(unsigned short text) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

