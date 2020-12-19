#pragma once

#include <string>
#include <iostream>

//Place, Character의 부모 클래스이다.
//x_pos, y_pos로 각 클래스에서 필요한 x, y좌표를 가지고 있다.
//GetXpos, GetYpos를 통해 x_pos, y_pos를 반환한다.
//PrintInformation을 통해 각 클래스에서 출력이 필요한 정보를 출력한다.
class Location {
protected:
    //x,y 좌표이다.
    int x_pos;
    int y_pos;
public:
    Location() noexcept {}
    Location(int x, int y) noexcept
        : x_pos(x), y_pos(y) 
    {}
    virtual ~Location() {}

    //x좌표를 반환하는 함수이다.
    virtual int GetXpos() final {
        return x_pos;
    }

    //y좌표를 반환하는 함수이다.
    virtual int GetYpos() final {
        return y_pos;
    }

    //각 클래스에서 출력이 필요한 정보를 출력한다.
    virtual void PrintInformation() = 0;
};

//인터페이스를 제공하는 클래스이다.
//Attraction, Structure 클래스의 부모 클래스이다.
class Place : public Location {
protected:
    std::string p_name;
    std::string p_explanation;
public:
    Place() noexcept {}
    Place(int x, int y, std::string name, std::string explanation) noexcept
        : Location(x, y), p_name(name), p_explanation(explanation)
    {}

    //place의 이름을 출력하는 함수이다.
    virtual void PrintName() final {
        std::cout << p_name;
    }

    //place의 설명을 출력하는 함수이다.
    virtual void PrintInformation() override final {
        std::cout << p_explanation << std::endl;
    }
};

//지도상에서 조형물에 해당하는 장소에 관한 클래스이다.
//x, y좌표, 이름, 설명으로 객체를 생성하면 관련 변수를 초기화한다.
class Attraction final :public Place {
public:
    Attraction(int x, int y, std::string name, std::string explanation)
        : Place(x, y, name, explanation) {}
};

//지도상에서 조형물에 해당하는 장소에 관한 클래스이다.
//x, y좌표, 이름, 설명으로 객체를 생성하면 관련 변수를 초기화한다.
class Structure final :public Place {
public:
    Structure(int x, int y, std::string name, std::string explanation)
        : Place(x, y, name, explanation) {}
};