#pragma once

#include "Enums.h"

//�ܼ�â�� ����� �� Ŀ���� ��ġ�� �ٲ��ִ� �Լ��̴�.
void CursorPos(int, int);

//�����̴� Ŀ���� ������ �ش�.
void RemoveCursor();

//�ܼ�â�� ���ڸ� ����� �� ���ڿ� ����� ���� �ٲ㼭 ����ϰ� ���ִ� �Լ��̴�.
void ChangeColor(int = COLOR_WHITE, int = COLOR_BLACK);

//w, a, s, d Ű�� �̿��Ͽ� ������ �����ϴ� �Լ��̴�.
int Selector();
