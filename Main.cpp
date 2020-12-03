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
//추가적으로 생각할 것!
//모든 파일의 위쪽에는 파일의 내용에 대한 주석을 작성한다.
//.h 파일은 그 안에 정의된 것, 사용되는 방식에 대해 설명한다.
//.cpp 파일은 구현의 세부사항, 알고리즘에 대해 설명한다.
//나중에 파일 분리할 때도 힘들겟다;;;
//final, override, virtual 키워드
//&, const 키워드
//건물의 개수랑 조형물의 개수를 map 안에서 저장하는 게 이상한데..?? static int로 class 안에서 해야 되는 거 아냐?
//캐릭터는 무조건 긱사에서 시작할 건지?
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

//프로그램을 시작할 때 필요한 함수이다.
//기본 창의 크기를 조정하고, 시작 화면에 아스키 아트를 출력해준다.
//옵션을 선택할 수 있도록 4가지 선택지를 보여준다.
//선택한 옵션을 정수형으로 반환해준다.
int StartProgram() {
	system("mode con cols=155 lines=38 | title 디지스트 캠퍼스 사이버 투어 프로그램");

	//깜빡이는 커서를 제거해준다.
	RemoveCursor();

	//시작 화면을 세팅한다.
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
		std::cout << "옵션 1: 빠른 투어를 원한다면? 최단 경로를 알려드려요!" << std::endl;
		CursorPos(x, start + 1);
		std::cout << "옵션 2: 디지스트 투어가 처음이라면? 코스를 추천해드려요." << std::endl;
		CursorPos(x, start + 2);
		std::cout << "옵션 3: 사이버로 캠퍼스를 구경하고 싶다면? 캐릭터를 움직여보세요!" << std::endl;
		CursorPos(x, start + 3);
		std::cout << "옵션 4: 다음에 학교에서 만나요!" << std::endl;

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
			std::cout << "※w키와 s키로만 조작이 가능합니다." << std::endl;
		}
	}
}

int main() {
    int choice = StartProgram();
    std::cout << "옵션 " << choice << "을(를) 선택하셨습니다." << std::endl;

    if (choice == 1 || choice == 2 || choice == 3) {
        Map map;
        std::string sequence, temp;
        int sequence_count;
        int x1, y1, x2, y2;


        int structure_num = structure_list.size();
        int attraction_num = attraction_list.size();

        std::cout << "스페이스바를 누르시면 투어가 시작됩니다." << std::endl;

        while (true) if (Selector() == 0) break;

        switch (choice) {
            //옵션 1: 최단 경로 출력
            //시작 위치와 도착 위치를 선택하면 두 지점을 잇는 경로를 나타낸다.

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

                    std::cout << std::endl << "출발 위치와 도착 위치를 입력하세요." << std::endl;
                    std::cout << "예시: E7에서 출발해서 학부생 기숙사로 이동 시 7 16 입력" << std::endl;

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
                        std::cout << "출발 위치는 ";
                        structure_list[start_num - 1].PrintName();
                    }
                    else if (start_num > structure_num) {
                        x1 = attraction_list[start_num - structure_num - 1].GetXpos();
                        y1 = attraction_list[start_num - structure_num - 1].GetYpos();
                        std::cout << "출발 위치는 ";
                        attraction_list[start_num - structure_num - 1].PrintName();
                    }
                    if (end_num <= structure_num) {
                        x2 = structure_list[end_num - 1].GetXpos();
                        y2 = structure_list[end_num - 1].GetYpos();
                        std::cout << "이고, 도착 위치는 ";
                        structure_list[end_num - 1].PrintName();
                        std::cout << "입니다." << std::endl;
                    }
                    else if (end_num > structure_num) {
                        x2 = attraction_list[end_num - structure_num - 1].GetXpos();
                        y2 = attraction_list[end_num - structure_num - 1].GetYpos();
                        std::cout << "이고, 도착 위치는 ";
                        attraction_list[end_num - structure_num - 1].PrintName();
                        std::cout << "입니다." << std::endl;
                    }

                    std::cout << "최단 경로를 출력합니다." << std::endl << std::endl;
                    map.FindShortestWay(x1, y1, x2, y2);
                    map.PrintMap(map.GetShortestMap());
                    break;
                }
                catch (int expn) {
                    system("cls");
                    std::cout << expn << ": 잘못된 숫자를 입력하셨습니다." << std::endl;
                }
                catch (std::string expn) {
                    system("cls");
                    std::cout << expn << ": 문자를 입력하셨습니다." << std::endl;
                }
                std::cout << "1에서 32까지의 숫자를 중복하지 않고 입력해주세요." << std::endl;
                std::cout << "스페이스바를 누르시면 목록으로 다시 돌아갑니다." << std::endl;
                while (true) {
                    if (Selector() == DIRECTION_ENTER) break;
                }
            } while (true);
            break;
            //옵션 2: 추천 경로 출력
            //장소에 대한 설명만을 보고 장소를 순서대로 입력하면, 해당 순서에 맞는 최단 경로를 이어서 나타낸다.
        case 2:
            system("cls");

            for (int i = 0; i < attraction_num; i++) {
                std::cout << i + 1 << ". ";
                attraction_list[i].PrintName();
                std::cout << ": ";
                attraction_list[i].PrintInformation();
                std::cout << std::endl;
            }
            std::cout << "가고 싶은 장소의 개수를 입력하세요." << std::endl;
            std::cin >> sequence_count;
            std::cout << "가고 싶은 장소의 숫자를 순서대로 입력하세요." << std::endl;
            std::cout << "예시: 5번, 3번, 1번 장소 순서로 이동 -> 5 3 1 입력" << std::endl;

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
            std::cout << "에서 출발하여 ";
            attraction_list[sequence[sequence.length() - 1] - '0' -1].PrintName();
            std::cout << "으로 이동합니다." << std::endl;
            std::cout << "추천 경로를 출력합니다." << std::endl << std::endl;

            map.PrintMap(map.GetShortestMap());
            break;

            //옵션 3: 캐릭터를 지도상에서 조작
            //캐릭터가 특정 장소에 도착하면 관련 설명이 출력된다
        case 3:
            Character person;

            while (true) {
                system("cls");

                map.PrintMap(map.GetMap());
                std::cout << "w: 위로 1칸 이동, s: 아래로 1칸 이동, a: 왼쪽으로 1칸 이동, d: 오른쪽으로 1칸 이동, q: 디지스트 사이버 투어 홈페이지 연결" << std::endl;
                std::cout << "8: 위로 5칸 이동, 2: 아래로 5칸 이동, 4: 왼쪽으로 5칸 이동, 6: 오른쪽으로 5칸 이동, 스페이스바: 종료";
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
    std::cout << "프로그램을 종료합니다." << std::endl;
    }
    return 0;
}