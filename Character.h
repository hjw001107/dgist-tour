#pragma once

#include "Location.h"
#include "Enums.h"
#include "Map.h"

//지도를 직접 돌아다닐 수 있는 캐릭터에 관한 클래스이다.
//x, y좌표를 멤버 변수로 가지며, 이동과 출력을 담당하는 멤버 함수를 가진다.
class Character : public Location {
public:
    //처음 위치를 정하지 않는 경우 학부생 기숙사에서 출발
    Character() : Character(45, 12) {}
    //처음 위치를 정할 경우 해당 위치에서 출발
    Character(const int& x, const int& y) {
        x_pos = x;
        y_pos = y;
    }
    ~Character() {}

    //캐릭터를 지도상에서 움직이는 함수이다.
    //지도의 방향, 지도 객체를 매개변수로 이용한다.
    //지도를 넘어가지 않으면서 길, 건물, 조형물만 이동할 수 있도록 제한되어있다.
    void MovePlayer(const int& direction, const Map& map);

    //캐릭터를 지도에 출력하는 함수이다.
    void PrintInformation() override final;
};
