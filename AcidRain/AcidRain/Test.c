//#include <stdio.h>
//#include <string.h>
//#include <windows.h>
//
//char testText[] = "텍스트";
//
//void clear_screen_ansi(void) {
//	printf("\x1b[2J\x1b[H");
//	fflush(stdout);
//}
//
//void gotoxy(int x, int y) {
//	//x, y 좌표 설정
//	COORD pos = { x,y };
//	//커서 이동
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
//}
//
//void TextRender(int x, int y)
//{
//	//clear_screen_ansi();
//	system("cls");
//	gotoxy(x, y);
//	printf("%s", testText);
//}
//
//int main(void)
//{
//	int x, y = 0;
//	int count = 0;
//	x = 10;
//	while (1)
//	{
//		if (count == 100)
//			break;
//		TextRender(x,y);
//		count++;
//		y++;
//		Sleep(50);
//	}
//	return 0;
//}