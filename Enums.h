#pragma once

//지도 배열에 저장된 숫자의 의미이다.
enum Block {
    BLOCK_ROAD = 0,
    BLOCK_WALL = 1,
    BLOCK_STRUCTURE = 2,
    BLOCK_BUILDING = 3,
    BLOCK_WAY = 4,
};

//콘솔창에 출력되는 글자, 배경의 색상이다.
enum Color {
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
    COLOR_GREEN = 2,
    COLOR_CYAN = 3,
    COLOR_RED = 4,
    COLOR_MAGENTA = 5,
    COLOR_BROWN = 6,
    COLOR_LIGHTGRAY = 7,
    COLOR_DARKGRAY = 8,
    COLOR_LIGHTBLUE = 9,
    COLOR_LIGHTGREEN = 10,
    COLOR_LIGHTCYAN = 11,
    COLOR_LIGHTRED = 12,
    COLOR_LIGHTMAGENTA = 13,
    COLOR_YELLOW = 14,
    COLOR_WHITE = 15,
};

//w, a, s, d 키로 입력한 방향이다.
enum Direction {
    DIRECTION_UP = 1,
    DIRECTION_DOWN = 2,
    DIRECTION_LEFT = 3,
    DIRECTION_RIGHT = 4,
    DIRECTION_ENTER = 0,
    DIRECTION_UNKNOWN = 255,
};