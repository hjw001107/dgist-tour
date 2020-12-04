#include "Map.h"

void Map::Push(int& x, int& y, int& cnt, const int& xx, const int& yy, const int& x_pos, const int& y_pos) {
    x = xx;
    y = yy;
    temp[y_pos][x_pos] = cnt;
    cnt++;
}

void Map::InitializeMap() {
    temp = map_data = ReadMap();
    for (int i = 0; i < map_width; i++) {
        for (int j = 0; j < map_height; j++) {
            temp[j][i] = 9999;
        }
    }
}

void Map::SearchWay(const int& start_x, const int& start_y, const int& end_x, const int& end_y) {
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

void Map::LinkWay(const int& start_x, const int& start_y, const int& end_x, const int& end_y) {
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

void Map::PrintMap(const std::vector<std::vector<int>>& map_requested) const {
    for (int i = 0; i < map_height; i++) {
        for (int j = 0; j < map_width; j++) {
            if (map_requested[i][j] == BLOCK_ROAD) {
                ChangeColor(COLOR_LIGHTGRAY, COLOR_DARKGRAY);
                std::cout << "��";
                ChangeColor();
            }
            else if (map_requested[i][j] == BLOCK_WALL) {
                ChangeColor(COLOR_LIGHTGREEN, COLOR_GREEN);
                std::cout << "��";
                ChangeColor();
            }
            else if (map_requested[i][j] == BLOCK_ATTRACTION) {
                ChangeColor(COLOR_WHITE, COLOR_LIGHTRED);
                std::cout << "��";
                ChangeColor();
            }
            else if (map_requested[i][j] == BLOCK_STRUCTURE) {
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