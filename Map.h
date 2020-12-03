#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

//������ ������ �����ϰ� �ִ� ��� ã�⸦ �����ϴ� Ŭ�����̴�.
class Map {
private:
    //���� ������� �̿��Ͽ� map.txt.�� ����� ���� ������ �ҷ����� �Լ��̴�.
    //�ҷ��� ������ ���� ���ͷ� ��ȯ���ش�.
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

    int map_width;     //���� �ʺ�
    int map_height;    //���� ����
    int attraction_num;  //"���"�� ������ ����
    int structure_num;   //"�б����� �ַ� �̿�Ǵ� ���"�� ������ ����

    std::vector < std::vector <int> > map_data;      //�� ������ �����ϴ� ���� ����
    std::vector < std::vector <int> > temp;          //�ִ� ��θ� ã�� ���� �ʿ��� ���� ����
    std::vector < std::vector <int> > shortest_map;  //�ִ� ��θ� �����ϴ� ���� ����
public:
    Map() {
        map_width = 52;
        map_height = 30;

        InitializeMap();

        shortest_map = map_data;

        attraction_num = 23;
        structure_num = 9;
    }

    //������ �ʺ� ��ȯ�ϴ� �Լ��̴�.
    int GetMapWidth() const {
        return map_width;
    }

    //������ ���̸� ��ȯ�ϴ� �Լ��̴�.
    int GetMapHeight() const {
        return map_height;
    }

    //���� x, y��ǥ�� �ش��ϴ� �� ������ ��ȯ�ϴ� �Լ��̴�.
    int GetMapBlock(const int& x, const int& y) const {
        return map_data[y][x];
    }

    std::vector < std::vector <int> > GetMap() const {
        return map_data;
    }

    std::vector < std::vector <int> > GetShortestMap() const {
        return shortest_map;
    }

    //�ִ� ��θ� ã�� �� x, y�� ��ǥ�� x[], y[] �迭�� �����Ѵ�.
    //temp�� ��ǥ���� cnt�� ���������ν� ��ΰ� ��� �̷�����ִ��� �����Ѵ�.
    void Push(int& x, int& y, int& cnt, const int& xx, const int& yy, const int& x_pos, const int& y_pos) {
        x = xx;
        y = yy;
        temp[y_pos][x_pos] = cnt;
        cnt++;
    }

    //FindShortestWay()�� �����ϸ� map_data�� temp ������ ���� ���� ���������� �ִܰŸ��� ã�� �� ����.
    //���� �ִ� ��θ� ã�� �� �Ʒ� �Լ��� �̿��Ͽ� map_data�� temp�� ������ ������ �����ش�.
    //temp�� ���, �ִ� ��θ� ã�� ���� ���� ��Ŀ� ���� ������ ��� cnt���� ū ���� �⺻���� ���´�.
    void InitializeMap() {
        temp = map_data = ReadMap();
        for (int i = 0; i < map_width; i++) {
            for (int j = 0; j < map_height; j++) {
                temp[j][i] = 9999;
            }
        }
    }

    //BFS ����� �̿�ǰ� �ִ�.
    //�Ű������� ���� ��ǥ, ���� ��ǥ�� �޴´�.
    //�Լ� ���ο��� Push()�� ȣ���Ѵ�.
    //�Լ� ���� ���� map_data�� temp�� ����� ���� �ٲ��.
    void SearchWay(const int& start_x, const int& start_y, const int& end_x, const int& end_y) {
        int pos, cnt;             //�ִ� ��θ� ã�� ���� �ʿ��� ����
        int* x = new int[40000];  //�ִ� ��θ� ã�� ���� �ʿ��� �迭
        int* y = new int[40000];  //�ִ� ��θ� ã�� ���� �ʿ��� �迭

        x[0] = start_x;
        y[0] = start_y;
        pos = 0;
        cnt = 1;

        while (pos < cnt && (x[pos] != end_x || y[pos] != end_y)) {
            //��湮�� �����ϱ� ���� ���� Ž�� ���� ��ǥ�� ���� �ٲ��ش�.
            map_data[y[pos]][x[pos]] = 1;

            //���� ��ǥ�� ���� �ƴ� ���(�� �� �ִ� ����� ���) Push()�� �����Ѵ�.
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
        //������� �ִ� ��θ� Ž���ϱ� ���� ������ ��� Ž���ǰ�, �Ʒ����ʹ� �ִ� ��θ� �ϳ��� ����� �����Ѵ�.
        //temp�� ����� ���� ��������, ���� ������������ ��� ���������� ��θ� �մ´�.
        //���� �������� �����Ͽ� ���� ��ǥ�� �� �� ���� ���� ���� ���� ��ǥ�� �ִ� ��ο� �ش��Ѵٰ� �����Ѵ�.

        pos--;
        temp[y[pos]][x[pos]] = cnt;
        temp[end_y][end_x] = cnt + 1;
        temp[start_y][start_x] = 0;

        delete[] x;
        delete[] y;
    }

    //SearchWay() ���� ���� ������ temp�κ��� shortestway�� ������ִ� �Լ��̴�.
    //�Ű������� ���� ��ǥ, ���� ��ǥ�� �Է��Ѵ�.
    //�������� ������ 4�� �����ϰ�, �� ������ temp�� �̿��Ͽ� �����Ѵ�.
    void LinkWay(const int& start_x, const int& start_y, const int& end_x, const int& end_y) {
        int xptr = end_x;
        int yptr = end_y;
        int before = temp[yptr][xptr];   //���� 4���� ��ǥ �� ���� ���� ���� �����ϴ� ����
        shortest_map[yptr][xptr] = shortest_map[start_y][start_x] = 4;  //�ִ� ��ο� �ش��ϴ� ��ǥ�� 4�� ǥ��

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

    //BFS ������� �ִ� ��θ� ã���ִ� �Լ��̴�.
    //�Ű������� ���� ��ǥ, ���� ��ǥ�� �Է��Ѵ�.
    //�Լ� ���ο��� SearchWay(), LinkWay(), InitializeMap()�� ȣ���Ѵ�.
    //�Լ��� ����Ǹ� map_data�� temp�� �ʱ�ȭ�Ǿ� shortest_map�� �ٲ���ְ� �ȴ�.
    void FindShortestWay(const int& start_x, const int& start_y, const int& end_x, const int& end_y) {
        SearchWay(start_x, start_y, end_x, end_y);
        LinkWay(start_x, start_y, end_x, end_y);
        InitializeMap();
    }

    //map_data�� ����ϴ� �Լ��̴�.
    void PrintMap(const std::vector<std::vector<int>>& map_requested) const {
        for (int i = 0; i < map_height; i++) {
            for (int j = 0; j < map_width; j++) {
                if (map_requested[i][j] == BLOCK_ROAD || map_requested[i][j] == 10) {
                    ChangeColor(COLOR_LIGHTGRAY, COLOR_DARKGRAY);
                    std::cout << "��";
                    ChangeColor();
                }
                else if (map_requested[i][j] == BLOCK_WALL) {
                    ChangeColor(COLOR_LIGHTGREEN, COLOR_GREEN);
                    std::cout << "��";
                    ChangeColor();
                }
                else if (map_requested[i][j] == BLOCK_STRUCTURE || map_requested[i][j] == 12) {
                    ChangeColor(COLOR_WHITE, COLOR_LIGHTRED);
                    std::cout << "��";
                    ChangeColor();
                }
                else if (map_requested[i][j] == BLOCK_BUILDING || map_requested[i][j] == 13) {
                    ChangeColor(COLOR_WHITE, COLOR_BLUE);
                    std::cout << "��";
                    ChangeColor();
                    ChangeColor();
                }
                else if (map_requested[i][j] == BLOCK_WAY) {
                    ChangeColor(COLOR_WHITE, COLOR_RED);
                    std::cout << "��";
                    ChangeColor();
                }
            }
            std::cout << std::endl;
        }
    }
};