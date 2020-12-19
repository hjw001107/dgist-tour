#pragma once

#include "Enums.h"
#include "console.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

//������ ������ �����ϰ� �ִ� ��� ã�⸦ �����ϴ� Ŭ�����̴�.
//������ �ʺ�, ����, map, map�� block�� ��ȯ�ϴ� �Լ��� �����ϸ�, ���� ����ϴ� �Լ��� �����Ͽ���.
class Map {
private:
    int map_width;       //���� �ʺ�
    int map_height;      //���� ����
    int attraction_num;  //"���"�� ������ ����
    int structure_num;   //"�б����� �ַ� �̿�Ǵ� ���"�� ������ ����

    //���� ������ ���� ���͸� �̿��Ͽ� �����Ͽ���. ������ ���� ���Ҹ� �߰��ϸ�, �ε����� ����ϰ� ���Ǳ� ������ ������ ������� �Ǵ��Ͽ���.
    std::vector < std::vector <int> > map_data;      //�� ������ �����ϴ� ���� ����
    std::vector < std::vector <int> > temp;          //�ִ� ��θ� ã�� ���� �ʿ��� ���� ����
    std::vector < std::vector <int> > shortest_map;  //�ִ� ��θ� �����ϴ� ���� ����

    //���� ������� �̿��Ͽ� map.txt�� ����� ���� ������ �ҷ����� �Լ��̴�.
    //�ҷ��� ������ ���� ���Ϳ� �־� ��ȯ���ش�.
    static std::vector<std::vector<int>> ReadMap();

    //�ִ� ��θ� ã�� �� x, y�� ��ǥ�� �����ͷ� �����Ѵ�.
    //temp�� �� ��ǥ���� cnt�� ���������ν� �ִ� ����� ������ ��� �̷�����ִ��� �����Ѵ�.
    void Push(int& x, int& y, int& cnt, const int& xx, const int& yy, const int& x_pos, const int& y_pos);

    //FindShortestWay()�� �����ϸ� map_data�� temp ������ ���� ���Ͽ� ���������� �ִܰŸ��� ã�� �� ����.
    //���� �ִ� ��θ� ã�� �� �Ʒ� �Լ��� �̿��Ͽ� map_data�� temp�� ������ ������ �����ش�.
    //temp�� ���, �ִ� ��θ� ã�� ���� ���� ��Ŀ� ���� ������ ��� cnt���� ū ���� �⺻���� ���´�.
    void InitializeMap();

    //BFS ����� �̿�ǰ� �ִ�.
    //�Ű������� ���� ��ǥ, ���� ��ǥ�� �޴´�.
    //�Լ� ���ο��� Push()�� ȣ���Ѵ�.
    //�Լ� ���� ���� map_data�� temp�� ����� ���� �ٲ��.
    void SearchWay(const int& start_x, const int& start_y, const int& end_x, const int& end_y);

    //SearchWay() ���� ���� ������ temp�κ��� shortestway�� ������ִ� �Լ��̴�.
    //�Ű������� ���� ��ǥ, ���� ��ǥ�� �Է��Ѵ�.
    //�������� ������ 4�� �����ϰ�, �� ������ temp�� �̿��Ͽ� �����Ѵ�.
    void LinkWay(const int& start_x, const int& start_y, const int& end_x, const int& end_y);
public:
    //�ʺ�, ����, attraction, structure, ���� ������ �ʱ�ȭ�Ѵ�.
    //DGIST ������ 52X30 ������ �迭�� ������� ������, width�� height�� �Ʒ��� ���� �ʱ�ȭ�Ͽ���(attraction, structure�� ��쵵 ��������).
    //���� �ٸ� ������ ���� ������ �߰��� ���, �׿� �´� ����� �����Ѵ�(�ν��Ͻ� ������ �����ڿ� ������ ũ�⸦ �Ű������� �Ѱ��� ���� ���� ���̴�).
    Map() noexcept {
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
    void PrintMap(const std::vector<std::vector<int>>& map_requested) const;
};