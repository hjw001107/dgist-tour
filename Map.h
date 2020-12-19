#pragma once

#include "Enums.h"
#include "console.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

//지도의 정보를 저장하고 최단 경로 찾기를 지원하는 클래스이다.
//지도의 너비, 높이, map, map의 block을 반환하는 함수가 존재하며, 맵을 출력하는 함수도 구현하였다.
class Map {
private:
    int map_width;       //맵의 너비
    int map_height;      //맵의 높이
    int attraction_num;  //"명소"의 개수를 저장
    int structure_num;   //"학교에서 주로 이용되는 장소"의 개수를 저장

    //지도 정보는 이중 벡터를 이용하여 구현하였다. 벡터의 끝에 원소를 추가하며, 인덱싱이 빈번하게 사용되기 때문에 유리한 구조라고 판단하였다.
    std::vector < std::vector <int> > map_data;      //맵 정보를 저장하는 이중 벡터
    std::vector < std::vector <int> > temp;          //최단 경로를 찾기 위해 필요한 이중 벡터
    std::vector < std::vector <int> > shortest_map;  //최단 경로를 저장하는 이중 벡터

    //파일 입출력을 이용하여 map.txt에 저장된 지도 정보를 불러오는 함수이다.
    //불러온 내용을 이중 벡터에 넣어 반환해준다.
    static std::vector<std::vector<int>> ReadMap();

    //최단 경로를 찾을 때 x, y의 좌표를 포인터로 저장한다.
    //temp의 각 좌표에는 cnt를 대입함으로써 최단 경로의 순서가 어떻게 이루어져있는지 저장한다.
    void Push(int& x, int& y, int& cnt, const int& xx, const int& yy, const int& x_pos, const int& y_pos);

    //FindShortestWay()를 실행하면 map_data와 temp 내부의 값이 변하여 연속적으로 최단거리를 찾을 수 없다.
    //따라서 최단 경로를 찾은 후 아래 함수를 이용하여 map_data와 temp를 원래의 값으로 돌려준다.
    //temp의 경우, 최단 경로를 찾을 때의 구현 방식에 따라 들어오는 모든 cnt보다 큰 값을 기본으로 갖는다.
    void InitializeMap();

    //BFS 방식이 이용되고 있다.
    //매개변수로 시작 좌표, 도착 좌표를 받는다.
    //함수 내부에서 Push()를 호출한다.
    //함수 동작 도중 map_data와 temp에 저장된 값이 바뀐다.
    void SearchWay(const int& start_x, const int& start_y, const int& end_x, const int& end_y);

    //SearchWay() 실행 이후 변형된 temp로부터 shortestway를 만들어주는 함수이다.
    //매개변수로 시작 좌표, 도착 좌표를 입력한다.
    //시작점과 끝점을 4로 지정하고, 두 지점을 temp를 이용하여 연결한다.
    void LinkWay(const int& start_x, const int& start_y, const int& end_x, const int& end_y);
public:
    //너비, 높이, attraction, structure, 지도 정보를 초기화한다.
    //DGIST 지도를 52X30 사이즈 배열로 만들었기 때문에, width와 height는 아래와 같이 초기화하였다(attraction, structure의 경우도 마찬가지).
    //만일 다른 지역에 대한 지도를 추가할 경우, 그에 맞는 사이즈를 대입한다(인스턴스 생성시 생성자에 지도의 크기를 매개변수로 넘겨줄 수도 있을 것이다).
    Map() noexcept {
        map_width = 52;
        map_height = 30;

        InitializeMap();

        shortest_map = map_data;

        attraction_num = 23;
        structure_num = 9;
    }

    //지도의 너비를 반환하는 함수이다.
    int GetMapWidth() const {
        return map_width;
    }

    //지도의 높이를 반환하는 함수이다.
    int GetMapHeight() const {
        return map_height;
    }

    //지도 x, y좌표에 해당하는 블럭 정보를 반환하는 함수이다.
    int GetMapBlock(const int& x, const int& y) const {
        return map_data[y][x];
    }

    std::vector < std::vector <int> > GetMap() const {
        return map_data;
    }

    std::vector < std::vector <int> > GetShortestMap() const {
        return shortest_map;
    }

    //BFS 방식으로 최단 경로를 찾아주는 함수이다.
    //매개변수로 시작 좌표, 도착 좌표를 입력한다.
    //함수 내부에서 SearchWay(), LinkWay(), InitializeMap()을 호출한다.
    //함수가 종료되면 map_data와 temp가 초기화되어 shortest_map만 바뀌어있게 된다.
    void FindShortestWay(const int& start_x, const int& start_y, const int& end_x, const int& end_y) {
        SearchWay(start_x, start_y, end_x, end_y);
        LinkWay(start_x, start_y, end_x, end_y);
        InitializeMap();
    }

    //map_data를 출력하는 함수이다.
    void PrintMap(const std::vector<std::vector<int>>& map_requested) const;
};