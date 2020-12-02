#include "Console.h"
#include "Enums.h"

#include <Windows.h>
#include <conio.h>
#include <ctype.h>

//�ܼ�â�� ����� �� Ŀ���� ��ġ�� �ٲ��ִ� �Լ��̴�.
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

//�ܼ�â�� ���ڸ� ����� �� ���ڿ� ����� ���� �ٲ㼭 ����ϰ� ���ִ� �Լ��̴�.
//������ ��, ����� ���� ���ʷ� �Ű������� �޴´�.
void ChangeColor(int text, int background) {
	int color = text + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//w, a, s, d Ű�� �̿��Ͽ� ������ �����ϴ� �Լ��̴�.
//������ ������ ���������� ��ȯ�Ѵ�.
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
