#include "Character.h"
#include "Location.h"
#include "Enums.h"
#include "Map.h"

//Character Ŭ������ ��� �Լ��� ���� ���� �κ��̴�.
//�ڼ��� ������ ��� ���Ͽ��� ã�ƺ� �� �ִ�.

void Character::MovePlayer(const int& direction, const Map& map) {
    int height = map.GetMapHeight();
    int width = map.GetMapWidth();
    switch (direction) {
        //ĳ���Ͱ� ��,��,��,��� �� ĭ�� �����δ�. �������� ĳ���Ͱ� �̵��� �� ���� Block�� ��� �������� �ʴ´�.
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

        //���� ��ɾ for���� ���� �ټ� �� �ݺ��Ѵ�. �ټ� ĭ�� ������ �� �ִ�.
        //�������� ĳ���Ͱ� �̵��� �� ���� ����� ��� �� �������� �̵��Ѵ�.
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
    std::cout << "��";
    ChangeColor();
}