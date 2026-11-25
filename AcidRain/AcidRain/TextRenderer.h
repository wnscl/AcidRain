#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//ingame에 등장하는 즉 떨어지는 단어를 구조체화
//이 때 인게임 상에 등장하는 단어가 100개를 넘어가지 않을 것임으로 연결리스트를 통해
//편리하게 삽입, 제거 할 수 있도록 함

char *screenTextInfo = NULL;
//define으로 정의된 게임 화면 크기에 따라 w, h 값으로 동적 배열 크기 할당
//좌표는 index값으로 조회하여 해당 인덱스에 char ''를 넣어주는 방식으로 화면 갱신
// x + (y * w) 로 좌표 index위치값 계산 현재 \n과 \0이 들어갈 칸이 필요함으로
// x + (y * (w + 2))로 계산
float fallDuration = 0;
//추락속도 난이도에 따라 초기화 시켜주어야 함

//원본 단어를 단어길이 1 ~ n까지 단어들을 각 길이에 해당하는 단어장 배열에 보관
//메모장의 단어를 전부 읽어 원본 단어장에 저장하는 함수
void TextRenderer_LoadTextBuffer()
{

}
void TextRenderer_SetScreenSizeData(int width, int height)
{
	screenTextInfo = (char*)malloc(sizeof(char) * ((width + 2) * height));
}
void TextRenderer_SetFallDuration(float duration)
{
	fallDuration = duration;
}
//원본 단어장에서 단어를 찾아와서 text구조체로 만들어 ingame에 존재하는 단어로 만듦
void TextRenderer_CreateText(int textLength)
{
	//가장 마지막 노드에 연결시키기
}
void TextRenderer_RemoveText()
{
	//연결리스트의 노드가 빠지게 됨으로 
	// 자신은 빠지고
	// 이전 노드와 다음 노드를 연결시킴
}
void TextRenderer_CompareInputText(char *inputText)
{
	//유저가 입력한 단어를 ingame에 존재하는 단어와 비교
	//ingame 단어는 연결리스트 임으로 선형으로 노드를 조회
	//일치하는 text 구조체가 있다면 해당 구조체를 제거하고 이전 노드와 다음 노드를 이어주기
	//제거함수 RemoveText
	//없다면 제거하지 않음
}
