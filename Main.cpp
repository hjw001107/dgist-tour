#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <assert.h>

#include "Enums.h"
#include "Console.h"
#include "Location.h"
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

template <typename T>
std::vector<T> ReadFromFIle(const char* path) {
	std::vector<T> rtn;
	std::ifstream ifs{ path };
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
		rtn.push_back(T(std::stoi(vec[0]), std::stoi(vec[1]), vec[2], vec[3]));
	}
	return rtn;
}

std::string ReadIntroDrawing() {
	std::ifstream ifs{ "intro.txt", std::ifstream::binary };
	return std::string((std::istreambuf_iterator<char>(ifs)),
		std::istreambuf_iterator<char>());
}

std::vector<Attraction> attraction_list = ReadFromFIle<Attraction>("attraction_list.txt");

std::vector<Structure> structure_list = ReadFromFIle<Structure>("structure_list.txt");

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
		std::cout << ReadIntroDrawing() << std::endl;

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
        std::string sequence, temp;
        int sequence_count;
        int x1, y1, x2, y2;


        int structure_num = structure_list.size();
        int attraction_num = attraction_list.size();

        std::cout << "�����̽��ٸ� �����ø� ��� ���۵˴ϴ�." << std::endl;

        while (true) if (Selector() == 0) break;

        switch (choice) {
            //�ɼ� 1: �ִ� ��� ���
            //���� ��ġ�� ���� ��ġ�� �����ϸ� �� ������ �մ� ��θ� ��Ÿ����.

        case 1:
            int start_num, end_num;
            do {
                try {
                    system("cls");

                    for (int i = 0; i < structure_num; i++) {
                        std::cout << i + 1 << ". ";
                        structure_list[i].PrintName();
                        std::cout << std::endl;
                    }

                    for (int i = 0; i < attraction_num; i++) {
                        std::cout << i + 24 << ". ";
                        attraction_list[i].PrintName();
                        std::cout << std::endl;
                    }

                    std::cout << std::endl << "��� ��ġ�� ���� ��ġ�� �Է��ϼ���." << std::endl;
                    std::cout << "����: E7���� ����ؼ� �кλ� ������ �̵� �� 7 16 �Է�" << std::endl;

                    std::string str;
                    std::getline(std::cin, str);
                    std::istringstream iss{ str };
                    iss >> start_num;
                    iss >> end_num;

                    if (iss.fail()) {
                        throw iss.str();
                    }

                    if (start_num <= 0 || start_num > 32) {
                        throw start_num;
                    }
                    if (end_num <= 0 || end_num > 32) {
                        throw end_num;
                    }
                    if (start_num == end_num) {
                        throw start_num;
                    }
                    
                    system("cls");
                    if (start_num <= structure_num) {
                        x1 = structure_list[start_num - 1].GetXpos();
                        y1 = structure_list[start_num - 1].GetYpos();
                        std::cout << "��� ��ġ�� ";
                        structure_list[start_num - 1].PrintName();
                    }
                    else if (start_num > structure_num) {
                        x1 = attraction_list[start_num - structure_num - 1].GetXpos();
                        y1 = attraction_list[start_num - structure_num - 1].GetYpos();
                        std::cout << "��� ��ġ�� ";
                        attraction_list[start_num - structure_num - 1].PrintName();
                    }
                    if (end_num <= structure_num) {
                        x2 = structure_list[end_num - 1].GetXpos();
                        y2 = structure_list[end_num - 1].GetYpos();
                        std::cout << "�̰�, ���� ��ġ�� ";
                        structure_list[end_num - 1].PrintName();
                        std::cout << "�Դϴ�." << std::endl;
                    }
                    else if (end_num > structure_num) {
                        x2 = attraction_list[end_num - structure_num - 1].GetXpos();
                        y2 = attraction_list[end_num - structure_num - 1].GetYpos();
                        std::cout << "�̰�, ���� ��ġ�� ";
                        attraction_list[end_num - structure_num - 1].PrintName();
                        std::cout << "�Դϴ�." << std::endl;
                    }

                    std::cout << "�ִ� ��θ� ����մϴ�." << std::endl << std::endl;
                    map.FindShortestWay(x1, y1, x2, y2);
                    map.PrintMap(map.GetShortestMap());
                    break;
                }
                catch (int expn) {
                    system("cls");
                    std::cout << expn << ": �߸��� ���ڸ� �Է��ϼ̽��ϴ�." << std::endl;
                }
                catch (std::string expn) {
                    system("cls");
                    std::cout << expn << ": ���ڸ� �Է��ϼ̽��ϴ�." << std::endl;
                }
                std::cout << "1���� 32������ ���ڸ� �ߺ����� �ʰ� �Է����ּ���." << std::endl;
                std::cout << "�����̽��ٸ� �����ø� ������� �ٽ� ���ư��ϴ�." << std::endl;
                while (true) {
                    if (Selector() == DIRECTION_ENTER) break;
                }
            } while (true);
            break;
            //�ɼ� 2: ��õ ��� ���
            //��ҿ� ���� ������ ���� ��Ҹ� ������� �Է��ϸ�, �ش� ������ �´� �ִ� ��θ� �̾ ��Ÿ����.
        case 2:
            system("cls");

            for (int i = 0; i < attraction_num; i++) {
                std::cout << i + 1 << ". ";
                attraction_list[i].PrintName();
                std::cout << ": ";
                attraction_list[i].PrintInformation();
                std::cout << std::endl;
            }
            std::cout << "���� ���� ����� ������ �Է��ϼ���." << std::endl;
            std::cin >> sequence_count;
            std::cout << "���� ���� ����� ���ڸ� ������� �Է��ϼ���." << std::endl;
            std::cout << "����: 5��, 3��, 1�� ��� ������ �̵� -> 5 3 1 �Է�" << std::endl;

            for (int i = 0; i < sequence_count; i++) {
                std::cin >> temp;
                sequence.append(temp);
            }

            for (int i = 1; i < sequence.length(); i++) {
                x1 = attraction_list[sequence[i - 1] - '0' -1].GetXpos();
                y1 = attraction_list[sequence[i - 1] - '0' -1].GetYpos();
                x2 = attraction_list[sequence[i] - '0' -1].GetXpos();
                y2 = attraction_list[sequence[i] - '0' -1].GetYpos();
                map.FindShortestWay(x1, y1, x2, y2);
            }

            system("cls");
            attraction_list[sequence[0] - '0' -1].PrintName();
            std::cout << "���� ����Ͽ� ";
            attraction_list[sequence[sequence.length() - 1] - '0' -1].PrintName();
            std::cout << "���� �̵��մϴ�." << std::endl;
            std::cout << "��õ ��θ� ����մϴ�." << std::endl << std::endl;

            map.PrintMap(map.GetShortestMap());
            break;

            //�ɼ� 3: ĳ���͸� �����󿡼� ����
            //ĳ���Ͱ� Ư�� ��ҿ� �����ϸ� ���� ������ ��µȴ�
        case 3:
            Character person;

            while (true) {
                system("cls");

                map.PrintMap(map.GetMap());
                std::cout << "w: ���� 1ĭ �̵�, s: �Ʒ��� 1ĭ �̵�, a: �������� 1ĭ �̵�, d: ���������� 1ĭ �̵�, q: ������Ʈ ���̹� ���� Ȩ������ ����" << std::endl;
                std::cout << "8: ���� 5ĭ �̵�, 2: �Ʒ��� 5ĭ �̵�, 4: �������� 5ĭ �̵�, 6: ���������� 5ĭ �̵�, �����̽���: ����";
                CursorPos(0, 33);
                for (int i = 0; i < attraction_num; i++) {
                    if (attraction_list[i].GetXpos() == person.GetXpos() && attraction_list[i].GetYpos() == person.GetYpos()) {
                        attraction_list[i].PrintName();
                        std::cout << ": ";
                        attraction_list[i].PrintInformation();
                    }
                }
                for (int i = 0; i < structure_num; i++) {
                    if (structure_list[i].GetXpos() == person.GetXpos() && structure_list[i].GetYpos() == person.GetYpos()) {
                        structure_list[i].PrintName();
                        std::cout << ": ";
                        structure_list[i].PrintInformation();
                    }
                }

                person.PrintInformation();

                int direction = Selector();
                if (direction == DIRECTION_ENTER) {
                    CursorPos(0, 35);
                    break;
                }

                if (direction == DIRECTION_STAY) {
                    system("explorer https://www.dgist.ac.kr/site/cyber/tour/");
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