#pragma once

#include <string>
#include <iostream>

//Place, Map, Character의 부모 클래스이다.
//x_pos, y_pos로 각 클래스에서 필요한 x, y좌표를 사용한다.
//PrintInformation을 통해 각 클래스에서 출력이 필요한 정보를 출력한다.
class Canvas {
protected:
    //x,y 좌표이다.
    int x_pos;
    int y_pos;
public:

    //x좌표를 반환하는 함수이다.
    virtual int GetXpos() {
        return x_pos;
    }

    //y좌표를 반환하는 함수이다.
    virtual int GetYpos() {
        return y_pos;
    }

    //각 클래스에서 출력이 필요한 정보를 출력한다
    virtual void PrintInformation() = 0;
};

//인터페이스를 제공하는 클래스이다.
//각 장소의 x, y좌표를 반환하며, 이름과 설명을 출력한다.
//Sturcture, Building 클래스의 부모 클래스이다.
class Place : public Canvas {
protected:
    std::string p_name;
    std::string p_explanation;
public:
    //place의 이름을 출력하는 함수이다.
    virtual void PrintName() {
        std::cout << p_name;
    }

    //place의 설명을 출력하는 함수이다.
    virtual void PrintInformation() override final {
        std::cout << p_explanation << std::endl;
    }
};

//지도상에서 조형물에 해당하는 장소에 관한 클래스이다.
//x, y좌표, 이름, 설명으로 객체를 생성하면 관련 변수를 초기화한다.
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


//지도상에서 조형물에 해당하는 장소에 관한 클래스이다.
//x, y좌표, 이름, 설명으로 객체를 생성하면 관련 변수를 초기화한다.
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