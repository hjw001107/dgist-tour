#include "Console.h"
#include "Enums.h"

#include <Windows.h>
#include <conio.h>
#include <ctype.h>

//콘솔창에 출력할 때 커서의 위치를 바꿔주는 함수이다.
void CursorPos(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

void RemoveCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

//콘솔창에 글자를 출력할 때 글자와 배경의 색을 바꿔서 출력하게 해주는 함수이다.
//글자의 색, 배경의 색을 차례로 매개변수로 받는다.
void ChangeColor(int text, int background) {
	int color = text + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//w, a, s, d 키를 이용하여 방향을 선택하는 함수이다.
//선택한 방향을 정수형으로 반환한다.
int Selector() {
	char input = _getch();
	switch (tolower(input)) {
	case 'w': return DIRECTION_UP;
	case 'a': return DIRECTION_LEFT;
	case 's': return DIRECTION_DOWN;
	case 'd': return DIRECTION_RIGHT;
	default:
		if (isspace(input))
			return DIRECTION_ENTER;
	}
	return DIRECTION_UNKNOWN;
}
