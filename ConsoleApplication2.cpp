#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <assert.h>

#include "Enums.h"
#include "Console.h"
#include "Canvas.h"
#include "Map.h"
#include "Character.h"

///////////////////////////////////////////////////////////////////////////
//�߰������� ������ ��!
//��� ������ ���ʿ��� ������ ���뿡 ���� �ּ��� �ۼ��Ѵ�.
//.h ������ �� �ȿ� ���ǵ� ��, ���Ǵ� ��Ŀ� ���� �����Ѵ�.
//.cpp ������ ������ ���λ���, �˰��� ���� �����Ѵ�.
//���߿� ���� �и��� ���� ����ٴ�;;;
//final, override, virtual Ű����
//&, const Ű����
//�ǹ��� ������ �������� ������ map �ȿ��� �����ϴ� �� �̻��ѵ�..?? static int�� class �ȿ��� �ؾ� �Ǵ� �� �Ƴ�?
//ĳ���ʹ� ������ ��翡�� ������ ����?
///////////////////////////////////////////////////////////////////////////

std::vector<Structure> GetStructureList() {
    std::vector<Structure> rtn;
    std::ifstream ifs{ "structure_list.txt" };
    while (ifs)
    {
        std::string line;
        std::getline(ifs, line);
        if (line.empty())
            break;

        std::vector<std::string> vec;

        auto begin = line.begin();
        auto it = line.begin();
        int i = 0;
        for (it = std::find(begin, line.end(), ','); it != line.end() && i < 3; it = std::find(begin, line.end(), ','), ++i)
        {
            vec.push_back(std::string(begin, it));
            begin = ++it;
        }
        vec.push_back(std::string(begin, line.end()));
        rtn.push_back(Structure(std::stoi(vec[0]), std::stoi(vec[1]), vec[2], vec[3]));
    }
    return rtn;
}

std::vector<Structure> structure_list = GetStructureList();

std::vector<Building> building_list{
Building(4, 16, "E1", "DGIST ���� ����.�б� �������� ���� ������ �̰����� ����Ǹ� ���н�, ������ �� �кλ��� ������ ��簡 ������."),
       Building(4, 14, "E2", "DGIST �Ź�����������"),
       Building(4, 12, "E3", "DGIST ���������������"),
       Building(4, 10, "E4", "DGIST �����̿÷������� & ��������������"),
       Building(4, 8, "E5", "DGIST �κ���������"),
       Building(4, 6, "E6", "DGIST ��������������"),
       Building(6, 11, "E7", "E1~E6�� �մ� 3�� ������ ���� �� �ǹ�. �кλ����� ������ �ַ� ���⼭ �̷������. �ص�â�Ǹ���, �ްԽ� �� �л����� �޽İ� ������ ���� ������ ���õǾ� ������, �л�ȸ��, �к���� �� �л���ġ��ü���� ������ ���õǾ��ִ�."),
       Building(20, 6, "E16", "2019�� 12�� �ذ��� �л�ȸ��. ���� ���Ƹ����� ���Ƹ���� �������Ƹ����� ������Ұ� ���õǾ� ������, ���� ���Ƹ����� ���� �������� �ʾ� Ȱ������ ���ϰ� �ִ�."),
       Building(15, 19, "R7", "�������°�. DGIST �� ������ ������� �ִ� ���̴�. �ߵ�������, �߳���ť��Ƽ, ���� ���� �ִ�."),
       Building(37, 24, "S1", "��,ü�� Ȱ���� ����Ǵ� �ǹ��̴�. ���Ͽ��� ��������. 1������ ü������ �ｺ����, 2������ ü�� ������ ���� ���ǽǰ� ������������ ������, 3������ ���ǽ��� �ִ�."),
       Building(41, 20, "������", "�ܺο��� �� �մԵ��� �ӹ����� ����̴�. ȣ���� ������ ���߰� �ִ�. ��ټ��� �л��� ���� ���� �����ϰ�� ������ ���Ѵ�."),
       Building(50, 10, "���п��������", "H205��~207������ �Ǿ�������, ���п������� �ӹ�����."),
       Building(27, 29, "��C", "DGIST ������ �ִ� ū DGIST ǥ���̴�. ���� ���� ���η� ������ ������ �� ����."),
       Building(9, 11, "�ð�������", "DGIST�� ��¡���� �ڸ����� ������ �� �ϳ�. �����, �������, ���� ���� ���ε��� �ձ۰� �� �ְ� ����� DGIST��ũ�� �ִ�."),
       Building(33, 11, "�߿����Ǵ�", "���� ���ǵ��Ƹ��� ������ �ϰų� �ֺ� ��ġ������ ��ǳ�� ���� ����̴�. �������� �� �������� ����� ��� �ִ�."),
       Building(23, 13, "������", "��������� ������ �� �Ͻô� �����Ե��� ������ �����ϴ� �ǹ��̴�. �л����� ���� �̰��� �н��� ������ �鸥��."),
       Building(42, 9, "��������Ȱ��", "�������� �����ϴ� ��Ȱ���̴�."),
       Building(7, 1, "�����", "���� �Խ�Ʈ�Ͽ콺�� ���������� ����� ���� ����� �� �����е鲲�� �������̽ô�."),
       Building(40, 25, "�౸��", "DGIST�� �౸���̴�. �౸���Ƹ��� �������� �����౸ȸ�� �ַ� �̿��ϸ�, ��ټ��� �л��� �౸��� ����� �ʹ����� �����ϱ� ���� ���� �峪���. "),
       Building(35, 27, "�״Ͻ���", "�״Ͻ� ���Ƹ��� �ַ� Ȱ���ϴ� �״Ͻ����̴�. Ŭ������Ʈ�̴�."),
       Building(22, 8, "ǲ����� ����", "�󱸵��Ƹ�, ǲ�쵿�Ƹ��� �ַ� Ȱ���ϴ� ����̴�. ���� �Ϲ� �л��鿡�Ե� ���µǾ� �ִ�."),
       Building(45, 12, "�кλ������", "H201��~204������ �Ǿ�������, �кλ����� �ӹ�����. ����� �Ĵ��� ���� ���� �����̴�."),
       Building(10, 8, "�м�������", "�������� �� 6�� ������ ������ �ǹ��̴�. DGIST�� ������ ������ �ϰ� ������, ���� ������ ���͵�, ���� ���θ� ���� ������ ��� ���õǾ��ִ�."),
};

//���α׷��� ������ �� �ʿ��� �Լ��̴�.
//�⺻ â�� ũ�⸦ �����ϰ�, ���� ȭ�鿡 �ƽ�Ű ��Ʈ�� ������ش�.
//�ɼ��� ������ �� �ֵ��� 4���� �������� �����ش�.
//������ �ɼ��� ���������� ��ȯ���ش�.
int StartProgram() {
    system("mode con cols=155 lines=38 | title ������Ʈ ķ�۽� ���̹� ���� ���α׷�");

    //�����̴� Ŀ���� �������ش�.
    RemoveCursor();

    //���� ȭ���� �����Ѵ�.
    int x = 47;
    int y = 20;
    int option = 0;
    while (true) {
        CursorPos(x - 2, y);
        std::cout << ">" << std::endl;
        CursorPos(0, 0);
        const char* drawing = "\
\n               \
\n                                                           <DGIST ķ�۽� ���̹� ���� ���α׷�>\
\n               \
\n                                                              ���� �ٷ� DGIST�� �����غ�����!\
\n               \
\n               \
\n                                                         (w, s: �޴� �̵�, �����̽���: �޴� ����)\
\n                                                                           _____\
\n                                                                           |   |\
\n                                                                           DGIST\
\n                                          _____         ____     __________| o |___________      _________\
\n                                         |o o o|_______|    |___|               | | # # #  |____|o o o o  | \
\n                                         |o o o|  * * *|: ::|. .|               |o| # # #  |. . |o o o o  |\
\n                                         |o o o|* * *  |::  |. .| []  []  []  []|o| # # #  |. . |o o o o  |\
\n                                         |o o o|**  ** |:  :|. .| []  []  []    |o| # # #  |. . |o o o o  |\
\n                                         |_[]__|__[]___|_||_|___|____________��_|_|___��___|_.|_|____[]___|\
\n";
        std::cout << drawing << std::endl;

        int start = 20;
        CursorPos(x, start);
        std::cout << "�ɼ� 1: ���� ��� ���Ѵٸ�? �ִ� ��θ� �˷������!" << std::endl;
        CursorPos(x, start + 1);
        std::cout << "�ɼ� 2: ������Ʈ ��� ó���̶��? �ڽ��� ��õ�ص����." << std::endl;
        CursorPos(x, start + 2);
        std::cout << "�ɼ� 3: ���̹��� ķ�۽��� �����ϰ� �ʹٸ�? ĳ���͸� ������������!" << std::endl;
        CursorPos(x, start + 3);
        std::cout << "�ɼ� 4: ������ �б����� ������!" << std::endl;

        int input = Selector();
        system("cls");

        switch (input) {
        case DIRECTION_UP:
            if (y > start) {
                CursorPos(x - 2, y);
                std::cout << " " << std::endl;
                CursorPos(x - 2, --y);
                std::cout << ">" << std::endl;
            }
            break;
        case DIRECTION_DOWN:
            if (y < start + 3) {
                CursorPos(x - 2, y);
                std::cout << " " << std::endl;
                CursorPos(x - 2, ++y);
                std::cout << ">" << std::endl;
            }
            break;
        case DIRECTION_ENTER:
            if (y == 20) option = 1;
            if (y == 21) option = 2;
            if (y == 22) option = 3;
            if (y == 23) option = 4;
            return option;
        default:
            CursorPos(x, 18);
            std::cout << "��wŰ�� sŰ�θ� ������ �����մϴ�." << std::endl;
        }
    }
}

int main() {
    int choice = StartProgram();
    std::cout << "�ɼ� " << choice << "��(��) �����ϼ̽��ϴ�." << std::endl;

    if (choice == 1 || choice == 2 || choice == 3) {
        Map map;
        std::string sequence;
        int x1, y1, x2, y2;


        int building_num = building_list.size();
        int structure_num = structure_list.size();

        std::cout << "�����̽��ٸ� �����ø� ��� ���۵˴ϴ�." << std::endl;

        while (true) if (Selector() == 0) break;

        switch (choice) {
            //�ɼ� 1: �ִ� ��� ���
            //���� ��ġ�� ���� ��ġ�� �����ϸ� �� ������ �մ� ��θ� ��Ÿ����.
        case 1:
            system("cls");
            for (int i = 0; i < building_num; i++) {
                std::cout << i + 1 << ". ";
                building_list[i].PrintName();
                std::cout << std::endl;
            }

            for (int i = 0; i < structure_num; i++) {
                std::cout << i + 24 << ". ";
                structure_list[i].PrintName();
                std::cout << std::endl;
            }

            std::cout << std::endl << "��� ��ġ�� ���� ��ġ�� �Է��ϼ���." << std::endl;
            std::cout << "����: E7���� ����ؼ� �кλ� ������ �̵� �� 7 16 �Է�" << std::endl;

            int start_num, end_num;

            while (true) {
                std::string str;
                std::getline(std::cin, str);
                std::istringstream iss{ str };
                iss >> start_num;
                iss >> end_num;

                if (iss.fail()) {
                    std::cout << "���� �� ���� �Է����ּ���." << std::endl;
                    continue;
                }

                break;
            }

            system("cls");

            if (start_num <= building_num) {
                x1 = building_list[start_num - 1].GetXpos();
                y1 = building_list[start_num - 1].GetYpos();
                std::cout << "��� ��ġ�� ";
                building_list[start_num - 1].PrintName();
            }
            else if (start_num > building_num) {
                x1 = structure_list[start_num - building_num - 1].GetXpos();
                y1 = structure_list[start_num - building_num - 1].GetYpos();
                std::cout << "��� ��ġ�� ";
                structure_list[start_num - building_num - 1].PrintName();
            }
            if (end_num <= building_num) {
                x2 = building_list[end_num - 1].GetXpos();
                y2 = building_list[end_num - 1].GetYpos();
                std::cout << "�̰�, ���� ��ġ�� ";
                building_list[end_num - 1].PrintName();
                std::cout << "�Դϴ�." << std::endl;
            }
            else if (end_num > building_num) {
                x2 = structure_list[end_num - building_num - 1].GetXpos();
                y2 = structure_list[end_num - building_num - 1].GetYpos();
                std::cout << "�̰�, ���� ��ġ�� ";
                structure_list[end_num - building_num - 1].PrintName();
                std::cout << "�Դϴ�." << std::endl;
            }

            std::cout << "�ִ� ��θ� ����մϴ�." << std::endl << std::endl;
            map.FindShortestWay(x1, y1, x2, y2);
            map.PrintShortestMap();

            break;

            //�ɼ� 2: ��õ ��� ���
            //��ҿ� ���� ������ ���� ��Ҹ� ������� �Է��ϸ�, �ش� ������ �´� �ִ� ��θ� �̾ ��Ÿ����.
        case 2:
            system("cls");

            for (int i = 0; i < structure_num; i++) {
                std::cout << i + 1 << ". ";
                structure_list[i].PrintName();
                std::cout << ": ";
                structure_list[i].PrintExplanation();
                std::cout << std::endl;
            }
            std::cout << "���� ���� ����� ��ȣ�� ������� �Է��ϼ���." << std::endl;
            std::cout << "����: 5��, 3��, 1�� ��� ������ �̵� -> 531 �Է�" << std::endl;

            std::cin >> sequence;

            for (int i = 1; i < sequence.length(); i++) {
                x1 = structure_list[sequence[i - 1] - '0'].GetXpos();
                y1 = structure_list[sequence[i - 1] - '0'].GetYpos();
                x2 = structure_list[sequence[i] - '0'].GetXpos();
                y2 = structure_list[sequence[i] - '0'].GetYpos();
                map.FindShortestWay(x1, y1, x2, y2);
            }

            system("cls");
            structure_list[sequence[0] - '0'].PrintName();
            std::cout << "���� ����Ͽ� ";
            structure_list[sequence[sequence.length() - 1] - '0'].PrintName();
            std::cout << "���� �̵��մϴ�." << std::endl;
            std::cout << "��õ ��θ� ����մϴ�." << std::endl << std::endl;

            map.PrintShortestMap();
            break;

            //�ɼ� 3: ĳ���͸� �����󿡼� ����
            //ĳ���Ͱ� Ư�� ��ҿ� �����ϸ� ���� ������ ��µȴ�.
        case 3:
            Character person;

            while (true) {
                system("cls");

                map.PrintInformation();
                std::cout << "w: ��, s: �Ʒ�, a: ����, d: ������, �����̽���: ����";

                CursorPos(0, 33);
                for (int i = 0; i < structure_num; i++) {
                    if (structure_list[i].GetXpos() == person.GetXpos() && structure_list[i].GetYpos() == person.GetYpos()) {
                        structure_list[i].PrintName();
                        std::cout << ": ";
                        structure_list[i].PrintExplanation();
                    }
                }
                for (int i = 0; i < building_num; i++) {
                    if (building_list[i].GetXpos() == person.GetXpos() && building_list[i].GetYpos() == person.GetYpos()) {
                        building_list[i].PrintName();
                        std::cout << ": ";
                        building_list[i].PrintExplanation();
                    }
                }

                person.PrintInformation();

                int direction = Selector();
                if (direction == DIRECTION_ENTER) {
                    CursorPos(0, 35);
                    break;
                }

                person.MovePlayer(direction, map);
            }
        }
    }
    else {
        std::cout << "���α׷��� �����մϴ�." << std::endl;
    }
    return 0;
}