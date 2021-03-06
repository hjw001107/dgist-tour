#pragma once

//지도 배열에 저장된 숫자의 의미이다.
//길, 벽, 조형물, 명소, 최단 경로로 구분된다.
enum Block {
    BLOCK_ROAD = 0,
    BLOCK_WALL = 1,
    BLOCK_ATTRACTION = 2,
    BLOCK_STRUCTURE = 3,
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

//w, a, s, d, 2, 4, 6, 8 키. 스페이스바, 엔터로 입력한 방향이다.  
enum Direction {
    DIRECTION_UP = 1,
    DIRECTION_DOWN = 2,
    DIRECTION_LEFT = 3,
    DIRECTION_RIGHT = 4,
    DIRECTION_FASTUP = 5,
    DIRECTION_FASTDOWN = 6,
    DIRECTION_FASTLEFT = 7,
    DIRECTION_FASTRIGHT = 8,
    DIRECTION_STAY = 9,

    DIRECTION_ENTER = 0,
    DIRECTION_UNKNOWN = 255,
};