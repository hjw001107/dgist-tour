#pragma once

#include <string>
#include <iostream>

//Place, Map, Character�� �θ� Ŭ�����̴�.
//x_pos, y_pos�� �� Ŭ�������� �ʿ��� x, y��ǥ�� ����Ѵ�.
//PrintInformation�� ���� �� Ŭ�������� ����� �ʿ��� ������ ����Ѵ�.
class Canvas {
protected:
    //x,y ��ǥ�̴�.
    int x_pos;
    int y_pos;
public:

    //x��ǥ�� ��ȯ�ϴ� �Լ��̴�.
    virtual int GetXpos() {
        return x_pos;
    }

    //y��ǥ�� ��ȯ�ϴ� �Լ��̴�.
    virtual int GetYpos() {
        return y_pos;
    }

    //�� Ŭ�������� ����� �ʿ��� ������ ����Ѵ�
    virtual void PrintInformation() = 0;
};

//�������̽��� �����ϴ� Ŭ�����̴�.
//�� ����� x, y��ǥ�� ��ȯ�ϸ�, �̸��� ������ ����Ѵ�.
//Sturcture, Building Ŭ������ �θ� Ŭ�����̴�.
class Place : public Canvas {
protected:
    std::string p_name;
    std::string p_explanation;
public:
    //place�� �̸��� ����ϴ� �Լ��̴�.
    virtual void PrintName() {
        std::cout << p_name;
    }

    //place�� ������ ����ϴ� �Լ��̴�.
    virtual void PrintInformation() override final {
        std::cout << p_explanation << std::endl;
    }
};

//�����󿡼� �������� �ش��ϴ� ��ҿ� ���� Ŭ�����̴�.
//x, y��ǥ, �̸�, �������� ��ü�� �����ϸ� ���� ������ �ʱ�ȭ�Ѵ�.
class Structure :public Place {
public:
    Structure(int x, int y, std::string name, std::string explanation) {
        x_pos = x;
        y_pos = y;
        p_name = name;
        p_explanation = explanation;
    }
    ~Structure() {}
};


//�����󿡼� �������� �ش��ϴ� ��ҿ� ���� Ŭ�����̴�.
//x, y��ǥ, �̸�, �������� ��ü�� �����ϸ� ���� ������ �ʱ�ȭ�Ѵ�.
class Building :public Place {
public:
    Building(int x, int y, std::string name, std::string explanation) {
        x_pos = x;
        y_pos = y;
        p_name = name;
        p_explanation = explanation;
    }
    ~Building() {}
};