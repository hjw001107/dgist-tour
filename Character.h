#pragma once

#include "Location.h"
#include "Enums.h"
#include "Map.h"

//������ ���� ���ƴٴ� �� �ִ� ĳ���Ϳ� ���� Ŭ�����̴�.
//x, y��ǥ�� ��� ������ ������, �̵��� ����� ����ϴ� ��� �Լ��� ������.
class Character final : public Location {
public:
    //ó�� ��ġ�� ������ �ʴ� ��� �кλ� �����(45, 12)���� ���
    Character() noexcept 
        : Character(45, 12) 
    {}
    //ó�� ��ġ�� ���� ��� �ش� ��ġ���� ���
    //���� case3���� ��ġ�� �Է¹޴� ����� ū �ǹ̰� ���� ������ ���� �߰����� �ʾ�����, ���� �ٸ� ������ �̿��ϴ� �� Ȯ�强 ���鿡�� �Ʒ��� ���� �����Ͽ���.
    Character(const int& x, const int& y) noexcept {
        x_pos = x;
        y_pos = y;
    }

    //ĳ���͸� �����󿡼� �����̴� �Լ��̴�.
    //������ ����, ���� ��ü�� �Ű������� �̿��Ѵ�.
    //������ �Ѿ�� �����鼭 ��, �ǹ�, �������� �̵��� �� �ֵ��� ���ѵǾ��ִ�.
    void MovePlayer(const int& direction, const Map& map);

    //ĳ���͸� ������ ����ϴ� �Լ��̴�.
    void PrintInformation() override;
};
