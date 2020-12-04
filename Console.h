#pragma once

#include "Enums.h"

//콘솔창에 출력할 때 커서의 위치를 바꿔주는 함수이다.
void CursorPos(int, int);

//깜빡이는 커서를 제거해 준다.
void RemoveCursor();

//콘솔창에 글자를 출력할 때 글자와 배경의 색을 바꿔서 출력하게 해주는 함수이다.
void ChangeColor(int = COLOR_WHITE, int = COLOR_BLACK);

//w, a, s, d 키를 이용하여 방향을 선택하는 함수이다.
int Selector();
