#pragma once

#include "Canvas.h"
#include "Enums.h"
#include "Map.h"

//������ ���� ���ƴٴ� �� �ִ� ĳ���Ϳ� ���� Ŭ�����̴�.
//x, y��ǥ�� ��� ������ ������, �̵��� ����� ����ϴ� ��� �Լ��� ������.
class Character : public Canvas {
public:
    //ó�� ��ġ�� ������ �ʴ� ��� �кλ� ����翡�� ���
    Character() : Character(45, 12) {}
    //ó�� ��ġ�� ���� ��� �ش� ��ġ���� ���
    Character(int x, int y) {
        x_pos = x;
        y_pos = y;
    }
    ~Character() {}

    //ĳ���͸� �����󿡼� �����̴� �Լ��̴�.
    //������ ����, ���� ��ü�� �Ű������� �̿��Ѵ�.
    //������ �Ѿ�� �����鼭 ��, �ǹ�, �������� �̵��� �� �ֵ��� ���ѵǾ��ִ�.
    void MovePlayer(int direction, Map map) {
        int height = map.GetMapHeight();
        int width = map.GetMapWidth();
        switch (direction) {
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
                x_pos --;
            }
            break;
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
        }
    }

    //ĳ���͸� ������ ����ϴ� �Լ��̴�.
    void PrintInformation() override final {
        CursorPos(x_pos * 2, y_pos);
        ChangeColor(COLOR_YELLOW, COLOR_DARKGRAY);
        std::cout << "��";
        ChangeColor();
    }
};
