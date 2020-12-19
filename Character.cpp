#include "Character.h"
#include "Location.h"
#include "Enums.h"
#include "Map.h"

//Character 클래스의 멤버 함수에 대한 정의 부분이다.
//자세한 설명은 헤더 파일에서 찾아볼 수 있다.

void Character::MovePlayer(const int& direction, const Map& map) {
    int height = map.GetMapHeight();
    int width = map.GetMapWidth();
    switch (direction) {
        //캐릭터가 상,하,좌,우로 한 칸씩 움직인다. 목적지가 캐릭터가 이동할 수 없는 Block일 경우 움직이지 않는다.
    case DIRECTION_UP:
        if (y_pos > 0 && map.GetMapBlock(x_pos, y_pos - 1) != 1) {
            y_pos--;
        }
        break;
    case DIRECTION_DOWN:
        if (y_pos < height - 1 && map.GetMapBlock(x_pos, y_pos + 1) != 1) {
            y_pos++;
        }
        break;
    case DIRECTION_RIGHT:
        if (x_pos < width - 1 && map.GetMapBlock(x_pos + 1, y_pos) != 1) {
            x_pos++;
        }
        break;
    case DIRECTION_LEFT:
        if (x_pos > 0 && map.GetMapBlock(x_pos - 1, y_pos) != 1) {
            x_pos--;
        }
        break;

        //위의 명령어를 for문을 통해 다섯 번 반복한다. 다섯 칸씩 움직일 수 있다.
        //목적지가 캐릭터가 이동할 수 없는 장소일 경우 그 전까지만 이동한다.
    case DIRECTION_FASTUP:
        for (int i = 0; i < 5; i++) {
            if (y_pos > 0 && map.GetMapBlock(x_pos, y_pos - 1) != 1) {
                y_pos--;
            }
        }
        break;
    case DIRECTION_FASTDOWN:
        for (int i = 0; i < 5; i++) {
            if (y_pos < height - 1 && map.GetMapBlock(x_pos, y_pos + 1) != 1) {
                y_pos++;
            }
        }
        break;
    case DIRECTION_FASTRIGHT:
        for (int i = 0; i < 5; i++) {
            if (x_pos < width - 1 && map.GetMapBlock(x_pos + 1, y_pos) != 1) {
                x_pos++;
            }
        }
        break;
    case DIRECTION_FASTLEFT:
        for (int i = 0; i < 5; i++) {
            if (x_pos > 0 && map.GetMapBlock(x_pos - 1, y_pos) != 1) {
                x_pos--;
            }
        }
        break;
    default:
        break;
    }
}

void Character::PrintInformation() {
    CursorPos(x_pos * 2, y_pos);
    ChangeColor(COLOR_YELLOW, COLOR_DARKGRAY);
    std::cout << "●";
    ChangeColor();
}