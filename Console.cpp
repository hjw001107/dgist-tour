#include "Console.h"
#include "Enums.h"

#include <Windows.h>
#include <conio.h>
#include <ctype.h>

//console 헤더 파일의 함수에 대한 정의 부분이다.
//자세한 설명은 헤더 파일에서 찾아볼 수 있다.

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

void ChangeColor(int text, int background) {
	int color = text + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int Selector() {
	char input = _getch();
	switch (tolower(input)) {
	case 'w': return DIRECTION_UP;
	case 'a': return DIRECTION_LEFT;
	case 's': return DIRECTION_DOWN;
	case 'd': return DIRECTION_RIGHT;
	case '8': return DIRECTION_FASTUP;
	case '4': return DIRECTION_FASTLEFT;
	case '2': return DIRECTION_FASTDOWN;
	case '6': return DIRECTION_FASTRIGHT;
	case 'q': return DIRECTION_STAY;
	default:
		if (isspace(input))
			return DIRECTION_ENTER;
	}
	return DIRECTION_UNKNOWN;
}
