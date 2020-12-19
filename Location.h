#pragma once

#include <string>
#include <iostream>

//Place, Character�� �θ� Ŭ�����̴�.
//x_pos, y_pos�� �� Ŭ�������� �ʿ��� x, y��ǥ�� ������ �ִ�.
//GetXpos, GetYpos�� ���� x_pos, y_pos�� ��ȯ�Ѵ�.
//PrintInformation�� ���� �� Ŭ�������� ����� �ʿ��� ������ ����Ѵ�.
class Location {
protected:
    //x,y ��ǥ�̴�.
    int x_pos;
    int y_pos;
public:
    Location() noexcept {}
    Location(int x, int y) noexcept
        : x_pos(x), y_pos(y) 
    {}
    virtual ~Location() {}

    //x��ǥ�� ��ȯ�ϴ� �Լ��̴�.
    virtual int GetXpos() final {
        return x_pos;
    }

    //y��ǥ�� ��ȯ�ϴ� �Լ��̴�.
    virtual int GetYpos() final {
        return y_pos;
    }

    //�� Ŭ�������� ����� �ʿ��� ������ ����Ѵ�.
    virtual void PrintInformation() = 0;
};

//�������̽��� �����ϴ� Ŭ�����̴�.
//Attraction, Structure Ŭ������ �θ� Ŭ�����̴�.
class Place : public Location {
protected:
    std::string p_name;
    std::string p_explanation;
public:
    Place() noexcept {}
    Place(int x, int y, std::string name, std::string explanation) noexcept
        : Location(x, y), p_name(name), p_explanation(explanation)
    {}

    //place�� �̸��� ����ϴ� �Լ��̴�.
    virtual void PrintName() final {
        std::cout << p_name;
    }

    //place�� ������ ����ϴ� �Լ��̴�.
    virtual void PrintInformation() override final {
        std::cout << p_explanation << std::endl;
    }
};

//�����󿡼� �������� �ش��ϴ� ��ҿ� ���� Ŭ�����̴�.
//x, y��ǥ, �̸�, �������� ��ü�� �����ϸ� ���� ������ �ʱ�ȭ�Ѵ�.
class Attraction final :public Place {
public:
    Attraction(int x, int y, std::string name, std::string explanation)
        : Place(x, y, name, explanation) {}
};

//�����󿡼� �������� �ش��ϴ� ��ҿ� ���� Ŭ�����̴�.
//x, y��ǥ, �̸�, �������� ��ü�� �����ϸ� ���� ������ �ʱ�ȭ�Ѵ�.
class Structure final :public Place {
public:
    Structure(int x, int y, std::string name, std::string explanation)
        : Place(x, y, name, explanation) {}
};