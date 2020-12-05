#pragma once

#include "Location.h"
#include "Enums.h"
#include "Map.h"

//������ ���� ���ƴٴ� �� �ִ� ĳ���Ϳ� ���� Ŭ�����̴�.
//x, y��ǥ�� ��� ������ ������, �̵��� ����� ����ϴ� ��� �Լ��� ������.
class Character : public Location {
public:
    //ó�� ��ġ�� ������ �ʴ� ��� �кλ� ����翡�� ���
    Character() : Character(45, 12) {}
    //ó�� ��ġ�� ���� ��� �ش� ��ġ���� ���
    Character(const int& x, const int& y) {
        x_pos = x;
        y_pos = y;
    }
    ~Character() {}

    //ĳ���͸� �����󿡼� �����̴� �Լ��̴�.
    //������ ����, ���� ��ü�� �Ű������� �̿��Ѵ�.
    //������ �Ѿ�� �����鼭 ��, �ǹ�, �������� �̵��� �� �ֵ��� ���ѵǾ��ִ�.
    void MovePlayer(const int& direction, const Map& map);

    //ĳ���͸� ������ ����ϴ� �Լ��̴�.
    void PrintInformation() override final;
};
