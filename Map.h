#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

//지도의 정보를 저장하고 최단 경로 찾기를 지원하는 클래스이다.
class Map {
private:
    //파일 입출력을 이용하여 map.txt.에 저장된 지도 정보를 불러오는 함수이다.
    //불러온 내용을 이중 벡터로 반환해준다.
    static std::vector<std::vector<int>> ReadMap() {
        std::ifstream ifs{ "map.txt" };
        std::vector<std::vector<int>> rtn;
        while (ifs) {
            std::string line;
            std::getline(ifs, line);
            if (line.empty())
                break;

            std::istringstream iss{ line };
            std::vector<int> vec(
                std::istream_iterator<int>{iss},
                std::istream_iterator<int>{}
            );

            rtn.push_back(vec);
        }
        return rtn;
    }

    int map_width;     //맵의 너비
    int map_height;    //맵의 높이
    int attraction_num;  //"명소"의 개수를 저장
    int structure_num;   //"학교에서 주로 이용되는 장소"의 개수를 저장

    std::vector < std::vector <int> > map_data;      //맵 정보를 저장하는 이중 벡터
    std::vector < std::vector <int> > temp;          //최단 경로를 찾기 위해 필요한 이중 벡터
    std::vector < std::vector <int> > shortest_map;  //최단 경로를 저장하는 이중 벡터
public:
    Map() {
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

    //최단 경로를 찾을 때 x, y의 좌표를 x[], y[] 배열에 저장한다.
    //temp의 좌표에는 cnt를 대입함으로써 경로가 어떻게 이루어져있는지 저장한다.
    void Push(int& x, int& y, int& cnt, const int& xx, const int& yy, const int& x_pos, const int& y_pos) {
        x = xx;
        y = yy;
        temp[y_pos][x_pos] = cnt;
        cnt++;
    }

    //FindShortestWay()를 실행하면 map_data와 temp 내부의 값이 변해 연속적으로 최단거리를 찾을 수 없다.
    //따라서 최단 경로를 찾은 후 아래 함수를 이용하여 map_data와 temp를 원래의 값으로 돌려준다.
    //temp의 경우, 최단 경로를 찾을 때의 구현 방식에 따라 들어오는 모든 cnt보다 큰 값을 기본으로 갖는다.
    void InitializeMap() {
        temp = map_data = ReadMap();
        for (int i = 0; i < map_width; i++) {
            for (int j = 0; j < map_height; j++) {
                temp[j][i] = 9999;
            }
        }
    }

    //BFS 방식이 이용되고 있다.
    //매개변수로 시작 좌표, 도착 좌표를 받는다.
    //함수 내부에서 Push()를 호출한다.
    //함수 동작 도중 map_data와 temp에 저장된 값이 바뀐다.
    void SearchWay(const int& start_x, const int& start_y, const int& end_x, const int& end_y) {
        int pos, cnt;             //최단 경로를 찾기 위해 필요한 정수
        int* x = new int[40000];  //최단 경로를 찾기 위해 필요한 배열
        int* y = new int[40000];  //최단 경로를 찾기 위해 필요한 배열

        x[0] = start_x;
        y[0] = start_y;
        pos = 0;
        cnt = 1;

        while (pos < cnt && (x[pos] != end_x || y[pos] != end_y)) {
            //재방문을 방지하기 위해 현재 탐색 중인 좌표의 값을 바꿔준다.
            map_data[y[pos]][x[pos]] = 1;

            //주위 좌표가 벽이 아닐 경우(갈 수 있는 블록일 경우) Push()를 실행한다.
            if (y[pos] > 0 && ((map_data[y[pos] - 1][x[pos]] != 1))) {
                Push(*(x + cnt), *(y + cnt), cnt, x[pos], y[pos] - 1, x[pos], y[pos]);
            }
            if (x[pos] > 0 && ((map_data[y[pos]][x[pos] - 1] != 1))) {
                Push(*(x + cnt), *(y + cnt), cnt, x[pos] - 1, y[pos], x[pos], y[pos]);
            }
            if (y[pos] < map_height - 1 && ((map_data[y[pos] + 1][x[pos]] != 1))) {
                Push(*(x + cnt), *(y + cnt), cnt, x[pos], y[pos] + 1, x[pos], y[pos]);
            }
            if (x[pos] < map_width - 1 && ((map_data[y[pos]][x[pos] + 1] != 1))) {
                Push(*(x + cnt), *(y + cnt), cnt, x[pos] + 1, y[pos], x[pos], y[pos]);
            }

            pos++;
        }
        //여기까지 최단 경로를 탐색하기 위한 정보는 모두 탐색되고, 아래부터는 최단 경로를 하나로 만들어 저장한다.
        //temp에 저장된 수를 기준으로, 도착 지점에서부터 출발 지점까지의 경로를 잇는다.
        //도착 지점에서 시작하여 주위 좌표의 값 중 가장 작은 값을 가진 좌표가 최단 경로에 해당한다고 가정한다.

        pos--;
        temp[y[pos]][x[pos]] = cnt;
        temp[end_y][end_x] = cnt + 1;
        temp[start_y][start_x] = 0;

        delete[] x;
        delete[] y;
    }

    //SearchWay() 실행 이후 변형된 temp로부터 shortestway를 만들어주는 함수이다.
    //매개변수로 시작 좌표, 도착 좌표를 입력한다.
    //시작점과 끝점을 4로 지정하고, 두 지점을 temp를 이용하여 연결한다.
    void LinkWay(const int& start_x, const int& start_y, const int& end_x, const int& end_y) {
        int xptr = end_x;
        int yptr = end_y;
        int before = temp[yptr][xptr];   //주위 4개의 좌표 중 가장 작은 값을 저장하는 변수
        shortest_map[yptr][xptr] = shortest_map[start_y][start_x] = 4;  //최단 경로에 해당하는 좌표를 4로 표시

        do {
            if (xptr + 1 < map_width - 1) {
                if (temp[yptr][xptr + 1] < before) {
                    before = temp[yptr][xptr + 1];
                }
            }
            if (xptr > 0) {
                if (temp[yptr][xptr - 1] < before) {
                    before = temp[yptr][xptr - 1];
                }
            }
            if (yptr + 1 < map_height) {
                if (temp[yptr + 1][xptr] < before) {
                    before = temp[yptr + 1][xptr];
                }
            }
            if (yptr > 0) {
                if (temp[yptr - 1][xptr] < before) {
                    before = temp[yptr - 1][xptr];
                }
            }

            if (before == temp[yptr][xptr + 1]) xptr++;
            else if (before == temp[yptr][xptr - 1]) xptr--;
            else if (before == temp[yptr + 1][xptr]) yptr++;
            else if (before == temp[yptr - 1][xptr]) yptr--;

            shortest_map[yptr][xptr] = 4;
        } while (before != temp[start_y][start_x]);
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
    void PrintMap(const std::vector<std::vector<int>>& map_requested) const {
        for (int i = 0; i < map_height; i++) {
            for (int j = 0; j < map_width; j++) {
                if (map_requested[i][j] == BLOCK_ROAD || map_requested[i][j] == 10) {
                    ChangeColor(COLOR_LIGHTGRAY, COLOR_DARKGRAY);
                    std::cout << "□";
                    ChangeColor();
                }
                else if (map_requested[i][j] == BLOCK_WALL) {
                    ChangeColor(COLOR_LIGHTGREEN, COLOR_GREEN);
                    std::cout << "□";
                    ChangeColor();
                }
                else if (map_requested[i][j] == BLOCK_STRUCTURE || map_requested[i][j] == 12) {
                    ChangeColor(COLOR_WHITE, COLOR_LIGHTRED);
                    std::cout << "♣";
                    ChangeColor();
                }
                else if (map_requested[i][j] == BLOCK_BUILDING || map_requested[i][j] == 13) {
                    ChangeColor(COLOR_WHITE, COLOR_BLUE);
                    std::cout << "▥";
                    ChangeColor();
                    ChangeColor();
                }
                else if (map_requested[i][j] == BLOCK_WAY) {
                    ChangeColor(COLOR_WHITE, COLOR_RED);
                    std::cout << "□";
                    ChangeColor();
                }
            }
            std::cout << std::endl;
        }
    }
};