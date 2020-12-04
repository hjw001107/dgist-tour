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

//////////////////////////////////////////////////////////////////////////
//DGIST Campus Cyer Tour Program                                        //
//201911100 ������, 201911105 ������, 201911151 ������, 201911192 ������//
//////////////////////////////////////////////////////////////////////////

//���� ������� �̿��Ͽ� structure_list.txt, attraction_list.txt ���� �޸��� ���ͷ� �����Ǿ� �ִ� �ǹ����� ��ǥ�� ������ vector�� ����, ��ȯ�Ѵ�.
//�ش� vector�� ��� 4������ ���ڷ� attraction�� structure �ν��Ͻ��� �����Ѵ�.
//template�� Structure Ÿ�԰� Attraction Ÿ���� ��� �ٷ�� ���� ���Ǿ���.
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
        for (it = std::find(begin, line.end(), ','); it != line.end() && i < 3; it = std::find(begin, line.end(), ','), i++)
        {
            vec.push_back(std::string(begin, it));
            begin = ++it;
        }
        vec.push_back(std::string(begin, line.end()));
        rtn.push_back(T(std::stoi(vec[0]), std::stoi(vec[1]), vec[2], vec[3]));
    }
    return rtn;
}

//������ ������ attraction�� building�� �ν��Ͻ��� �μ��� ������ �ִ� vector�� �����.
std::vector<Attraction> attraction_list = ReadFromFIle<Attraction>("attraction_list.txt");
std::vector<Structure> structure_list = ReadFromFIle<Structure>("structure_list.txt");

//���� ������� �̿��Ͽ� �ƽ�Ű ��Ʈ�� ����� intro.txt�� �а�, ���� ȭ�鿡���� ��¿� �̿��� �� �ְ� string Ÿ������ ��ȯ�Ѵ�.
std::string ReadIntroDrawing() {
    std::ifstream ifs{ "intro.txt", std::ifstream::binary };
    return std::string((std::istreambuf_iterator<char>(ifs)),
        std::istreambuf_iterator<char>());
}

//���α׷��� ������ �� �ҷ����� �Լ��̴�.
//�⺻ â�� ũ�⸦ �����ϰ�, ���� ȭ�鿡 �ƽ�Ű ��Ʈ�� ������ش�.
//�ɼ��� ������ �� �ֵ��� 4���� �������� �����ش�.
//������ �ɼ��� ���������� ��ȯ���ش�.
int StartProgram() {
    //�Ʒ��� ������ �ܼ�â�� ũ��� ������ ��� �� ���� ����� ������ ���� ����Ͽ� �����Ǿ���.
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

        //w, s, ����(Ȥ�� �����̽�)�� �����Ͽ� �Է¹޴´�.
        int input = Selector();
        system("cls");
        
        //���� ȭ�鿡�� Ŀ���� �����Ѵ�. ��, �Ʒ�, ����(Ȥ�� �����̽�)������ �����Ǿ�������, �̿��� �� �Է¿� ���� ����ó���� �Ǿ� �ִ�.
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

//main �Լ� ���ο��� case1�� �Ҹ��� �Ǹ� ���� �޴��� ������ִ� �Լ��̴�. 
//structure_num, attraction_num�� �Ű������� �ް�, �� ����� ��Ҹ� ���ڿ� �Բ� ����Ѵ�.
void PrepareMainCase1(const int& structure_num, const int& attraction_num) {
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
}

//main �Լ� ���ο��� case1�� �Ҹ��� �Ǹ� ���� ó�� �Ŀ� ȣ��Ǿ� ����� �����ϱ� �����ϴ� �Լ��̴�. 
//�� ���ڿ� �´� �ǹ��� �ν�, �ش� �ǹ��� x, y ��ǥ�� �о �� x,y ��ǥ ���� �ִ� ��θ� ǥ���Ѵ�.
//map���� road, attraction, structure�� �ش��ϴ� ��θ��� �̿��Ͽ� �ִ� ��ΰ� ¥������.
void SuccessMainCase1(Map& map, const int& structure_num, const int& attraction_num, const int& start_num, const int& end_num) {
    int x1, y1, x2, y2;
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
}


//�ɼ� 1�� ���� �Լ��̴�. �ǹ� ����Ʈ�� ���� ��, �� ���� ���ڸ� �޾� �ش��ϴ� �ǹ� ������ �ִ� ��θ� ����Ѵ�.
void MainCase1(Map& map, const int& structure_num, const int& attraction_num) {
    int start_num, end_num;
    do {
        try {
            //case1�� ���� �޴� ���
            PrepareMainCase1(structure_num, attraction_num);

            //����ڰ� �ļ� ���� �� ���� ���� �ν��Ͽ� integer�� ��ȯ�Ѵ�.
            std::string str;
            std::getline(std::cin, str);
            std::istringstream iss{ str };
            iss >> start_num;
            iss >> end_num;

            //integer�� ��ȯ ���� �� throw
            if (iss.fail()) throw iss.str();

            //start_num�� end_num�� ������ ������ ��� �� throw(����� ���� 32���̴�.)
            if (start_num <= 0 || start_num > 32 || start_num == end_num) throw start_num;
            if (end_num <= 0 || end_num > 32) throw end_num;

            //���� ó�� ���� ��� ����
            SuccessMainCase1(map, structure_num, attraction_num, start_num, end_num);
            break;
        }

        //������ ��� ���ڸ� �Է½ÿ��� �߸��� ���ڸ� �Է��Ͽ��ٰ� ��µȴ�.
        catch (int expn) {
            system("cls");
            std::cout << expn << ": �߸��� ���ڸ� �Է��ϼ̽��ϴ�." << std::endl;
        }
        //integer ��ȯ ���н�, ���ڸ� �Է��Ͽ��ٰ� ��µȴ�. 
        catch (std::string expn) {
            system("cls");
            std::cout << expn << ": ���ڸ� �Է��ϼ̽��ϴ�." << std::endl;
        }
        //���� �Է¿� ���� ���� �߻� �� ����(�����̽���)�� ������ �ٽ� ���� �Է����� ���ư���.
        //�ùٸ� ���� �Է� �ñ��� �ݺ��ȴ�.
        std::cout << "1���� 32������ ���ڸ� �ߺ����� �ʰ� �Է����ּ���." << std::endl;
        std::cout << "�����̽��ٸ� �����ø� ������� �ٽ� ���ư��ϴ�." << std::endl;
        while (true) {
            if (Selector() == DIRECTION_ENTER) break;
        }
    } while (true);
}

//main �Լ� ���ο��� case2�� �Ҹ��� �Ǹ� ���� �޴��� ������ִ� �Լ��̴�. 
//attraction_num�� �Ű������� �ް�, ����� �̸��� ��Ҹ� ���ڿ� �Բ� ����Ѵ�.
void PrepareMainCase2(const int& attraction_num) {
    system("cls");
    for (int i = 0; i < attraction_num; i++) {
        std::cout << i + 1 << ". ";
        attraction_list[i].PrintName();
        std::cout << ": ";
        attraction_list[i].PrintInformation();
        std::cout << std::endl;
    }
}

//main �Լ� ���ο��� case2�� �Ҹ��� �Ǹ� ���� ó�� �Ŀ� ȣ��Ǿ� ����� �����ϱ� �����ϴ� �Լ��̴�. 
//sequence���� �� ���� ���� ���ʴ�� �̾Ƽ� x, y��ǥ�� ����, �ִܰ�θ� ã�´�.
//��� �ִܰ�ΰ� ��ø�Ǿ� �׷��� map�� ����Ѵ�.
void SuccessMainCase2(Map& map, const int& sequence_count, std::vector <int> sequence) {
    int x1, y1, x2, y2;
    for (int i = 1; i < sequence_count; i++) {
        x1 = attraction_list[sequence[i - 1]].GetXpos();
        y1 = attraction_list[sequence[i - 1]].GetYpos();
        x2 = attraction_list[sequence[i]].GetXpos();
        y2 = attraction_list[sequence[i]].GetYpos();
        map.FindShortestWay(x1, y1, x2, y2);
    }
    system("cls");
    attraction_list[*(sequence.begin())].PrintName();
    std::cout << "���� ����Ͽ� ";
    attraction_list[*(sequence.end() - 1)].PrintName();
    std::cout << "���� �̵��մϴ�." << std::endl;
    std::cout << "��õ ��θ� ����մϴ�." << std::endl << std::endl;
    map.PrintMap(map.GetShortestMap());
}

//�ɼ� 2�� ���� �Լ��̴�. �ش� �Լ��� ��õ ��� ����� ����Ѵ�.
//��ҿ� ���� ������ ���� ��Ҹ� ������� �Է��ϸ�, �ش� ������ �´� �ִ� ��θ� �̾ ��Ÿ����.
void MainCase2(Map& map, const int& attraction_num) {
    int temp;
    int sequence_count;
    do {
        try {
            PrepareMainCase2(attraction_num);
            
            //�ּ� 2��, �ִ� 9������ ��Ҹ� �Է¹ޱ� ������, �Է¹��� ����� ������ ���� �Է¹޾� sequence_count�� �����Ѵ�.
            std::cout << "���� ���� ����� ������ �Է��ϼ���." << std::endl;
            std::vector <int>  sequence;
            std::string str1;
            std::getline(std::cin, str1);
            std::istringstream iss1{ str1 };
            iss1 >> sequence_count;

            //integer�� ��ȯ ���� �� throw 
            if (iss1.fail()) throw iss1.str();

            //sequence_count�� ������ ��� �� throw 
            if (sequence_count <= 1 || sequence_count > 9) throw sequence_count;

            std::cout << "���� ���� ����� ���ڸ� ������� �Է��ϼ���." << std::endl;
            std::cout << "����: 5��, 3��, 1�� ��� ������ �̵� -> 5 3 1�� �Է�" << std::endl;

            //����ڰ� �ļ� ���� sequence_count��ŭ�� ���� �ν��Ͽ� integer�� ��ȯ�Ѵ�.
            std::string str2;
            std::getline(std::cin, str2);
            std::istringstream iss2{ str2 };
            for (int i = 0; i < sequence_count; i++) {
                iss2 >> temp;

                //integer�� ��ȯ ���� �� throw
                if (iss2.fail()) {
                    std::vector <int> new_vector;
                    sequence = new_vector;
                    throw iss2.str();
                }

                //sequence_count�� ������ ��� �� throw 
                if (temp < 1 || temp > 9)
                {
                    std::vector <int> new_vector;
                    sequence = new_vector;
                    throw temp;
                }

                //���� �� ������ ���� sequence�� ����ִ´�.
                sequence.push_back(temp);
            }
            
            //�ߺ��� ���� �޾��� ��� throw
            for (int i = 0; i < sequence_count; i++) {
                for (int j = i + 1; j < sequence_count; j++) {
                    if (sequence[i] == sequence[j]) throw sequence[i];
                }
            }

            //���� ó�� ���� ��� ����
            SuccessMainCase2(map, sequence_count, sequence);
            break;
        }

        //������ ��� ���ڸ� �Է½ÿ��� �߸��� ���ڸ� �Է��Ͽ��ٰ� ���.
        catch (int expn) { 
            system("cls");
            std::cout << expn << ": �߸��� ���ڸ� �Է��ϼ̽��ϴ�." << std::endl;

        }

        //integer ��ȯ ���н�, ���ڸ� �Է��Ͽ��ٰ� ���. 
        catch (std::string expn) {
            system("cls");
            std::cout << expn << ": ���ڸ� �Է��ϼ̰ų�, �ǹ��� ����ŭ ���ڸ� �Է����� �����̽��ϴ�." << std::endl;
        }

        //���� �Է¿� ���� ���� �߻� �� ����(�����̽���)�� ������ �ٽ� ���� �Է����� ���ư���.
        //�ùٸ� ���� �Է� �ñ��� �ݺ��ȴ�.
        std::cout << "1���� 9������ ���ڸ� �ùٸ��� �Է����ּ���." << std::endl;
        std::cout << "�����̽��ٸ� �����ø� ������� �ٽ� ���ư��ϴ�." << std::endl;
        while (true) {
            if (Selector() == DIRECTION_ENTER) break;
        }
    } while (true);
}

//main �Լ� ���ο��� case3�� �Ҹ��� �Ǹ� ����� �����ϱ� �����ϴ� �Լ��̴�. 
//map���� ĳ���͸� �����ϸ� road, attraction, structure ���� �̵��Ѵ�.
//Ư�� ��ġ�� �����ϸ� �ǹ��� ������ ��µǰ�, q Ű�� ������ ���ͳ� ����Ʈ�� ����ȴ�.
void MainCase3(Map& map, const int& structure_num, const int& attraction_num) {
    Character person;
    while (true) {
        system("cls");
        map.PrintMap(map.GetMap());
        std::cout << "w: ���� 1ĭ �̵�, s: �Ʒ��� 1ĭ �̵�, a: �������� 1ĭ �̵�, d: ���������� 1ĭ �̵�, q: ������Ʈ ���̹� ���� Ȩ������ ����" << std::endl;
        std::cout << "8: ���� 5ĭ �̵�, 2: �Ʒ��� 5ĭ �̵�, 4: �������� 5ĭ �̵�, 6: ���������� 5ĭ �̵�, �����̽���: ����";
        CursorPos(0, 33);

        //�ǹ��� ���� ��ǥ�� character�� ��ǥ�� �νĵǸ�, �ش� �ǹ��� �̸��� ������ ����Ѵ�.
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
        
        //character�� ��ġ�� ������ش�.
        person.PrintInformation();
        
        //�����̽��ٳ� ���� ��½� ���� �޴��� ���ư���.
        int direction = Selector();
        if (direction == DIRECTION_ENTER) {
            CursorPos(0, 35);
            break;
        }
        
        //Ư�� Ű �Է½� dgist cyber tour URL ��ũ�� ������ �ȴ�.
        if (direction == DIRECTION_STAY) {
            system("explorer https://www.dgist.ac.kr/site/cyber/tour/");
        }
        person.MovePlayer(direction, map);
    }
}

//���� ȭ�鿡�� w, s Ű�� �̿��Ͽ� �ɼ� 1-4 �߿� �ϳ��� �����Ѵ�.
//�� �ɼǿ� �´� ����� ����ȴ�(�ɼ� 1: �ִ� ���, �ɼ� 2: ��õ ���, �ɼ� 3: ĳ���� ����, �ɼ� 4: ����).
int main() {
    while (true) {
        int choice = StartProgram();
        std::cout << "�ɼ� " << choice << "��(��) �����ϼ̽��ϴ�." << std::endl;
        if (choice == 1 || choice == 2 || choice == 3) {
            Map map;
            int structure_num = structure_list.size();
            int attraction_num = attraction_list.size();

            std::cout << "�����̽��ٸ� �����ø� ��� ���۵˴ϴ�." << std::endl;
            while (true) if (Selector() == 0) break;
            system("cls");

            switch (choice) {
                //�ɼ� 1: �ִ� ���
            case 1:
                MainCase1(map, structure_num, attraction_num);
                break;

                //�ɼ� 2: ��õ ���
            case 2:
                MainCase2(map, attraction_num);
                break;

                //�ɼ� 3: ĳ���� ����
            case 3:
                MainCase3(map, structure_num, attraction_num);
                break;
            }
            //�����̽� Ȥ�� ���͸� �̿��� ���� �޴��� ���ư� �� �ִ�.
            std::cout << "�����̽��ٸ� �����ø� �޴��� ���ư��ϴ�." << std::endl;
            while (true) if (Selector() == 0) break;
            system("cls");
        }
        //start �޴����� �ɼ� 4�� �����ؾ߸� ���α׷��� ����ȴ�.
        else {
            std::cout << "���α׷��� �����մϴ�." << std::endl;
            break;
        }
    }
    return 0;
}