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
Building(4, 16, "E1", "DGIST 대학 본부.학교 전반적인 행정 업무가 이곳에서 진행되며 입학식, 졸업식 등 학부생의 굵직한 행사가 열린다."),
       Building(4, 14, "E2", "DGIST 신물질과학전공"),
       Building(4, 12, "E3", "DGIST 정보통신융합전공"),
       Building(4, 10, "E4", "DGIST 뉴바이올로지전공 & 뇌인지과학전공"),
       Building(4, 8, "E5", "DGIST 로봇공학전공"),
       Building(4, 6, "E6", "DGIST 에너지공학전공"),
       Building(6, 11, "E7", "E1~E6를 잇는 3층 높이의 낮고 긴 건물. 학부생들의 수업은 주로 여기서 이루어진다. 해동창의마루, 휴게실 등 학생들의 휴식과 과제를 위한 공간이 마련되어 있으며, 학생회실, 학보사실 등 학생자치단체들의 공간도 마련되어있다."),
       Building(20, 6, "E16", "2019년 12월 준공된 학생회관. 여러 동아리들의 동아리방과 공연동아리들의 연습장소가 마련되어 있으나, 아직 동아리별로 방이 배정되지 않아 활용하지 못하고 있다."),
       Building(15, 19, "R7", "산학협력관. DGIST 내 입주한 기업들이 있는 곳이다. ㈜디지엠텍, ㈜나노큐엔티, 제핏 등이 있다."),
       Building(37, 24, "S1", "예,체능 활동이 진행되는 건물이다. 지하에는 수영장이. 1층에는 체육관과 헬스장이, 2층에는 체육 수업을 위한 강의실과 골프연습장이 있으며, 3층에는 음악실이 있다."),
       Building(41, 20, "국제관", "외부에서 온 손님들이 머무르는 장소이다. 호텔의 형식을 갖추고 있다. 대다수의 학생은 면접 때를 제외하고는 가보지 못한다."),
       Building(50, 10, "대학원생기숙사", "H205동~207동으로 되어있으며, 대학원생들이 머무른다."),
       Building(27, 29, "빅C", "DGIST 정문에 있는 큰 DGIST 표식이다. 떼서 앞의 도로로 굴리면 굴러갈 것 같다."),
       Building(9, 11, "시간의정원", "DGIST의 상징물로 자리잡은 조각상 중 하나. 정약용, 세종대왕, 에디슨 등의 위인들이 둥글게 서 있고 가운데엔 DGIST마크가 있다."),
       Building(33, 11, "야외음악당", "가끔 음악동아리가 공연을 하거나 주변 유치원에서 소풍을 오는 장소이다. 원형으로 된 공연장의 모습을 띄고 있다."),
       Building(23, 13, "연구동", "연구원들과 수업을 안 하시는 교수님들이 연구를 진행하는 건물이다. 학생들은 보통 이곳에 학식을 먹으러 들른다."),
       Building(42, 9, "연구원생활관", "연구원이 거주하는 생활관이다."),
       Building(7, 1, "영빈관", "본래 게스트하우스로 지어졌으나 현재는 국양 총장님 및 가족분들께서 거주중이시다."),
       Building(40, 25, "축구장", "DGIST의 축구장이다. 축구동아리나 유가읍의 조기축구회가 주로 이용하며, 대다수의 학생은 축구장과 연결된 쪽문으로 출입하기 위해 자주 드나든다. "),
       Building(35, 27, "테니스장", "테니스 동아리가 주로 활동하는 테니스장이다. 클레이코트이다."),
       Building(22, 8, "풋살장과 농구장", "농구동아리, 풋살동아리가 주로 활동하는 장소이다. 물론 일반 학생들에게도 오픈되어 있다."),
       Building(45, 12, "학부생기숙사", "H201동~204동으로 되어있으며, 학부생들이 머무른다. 기숙사 식당은 문을 닫은 상태이다."),
       Building(10, 8, "학술정보관", "원형으로 된 6층 높이의 유리벽 건물이다. DGIST의 도서관 역할을 하고 있으며, 조별 과제와 스터디, 개인 공부를 위한 공간이 모두 마련되어있다."),
};

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
        const char* drawing = "\
\n               \
\n                                                           <DGIST 캠퍼스 사이버 투어 프로그램>\
\n               \
\n                                                              지금 바로 DGIST를 투어해보세요!\
\n               \
\n               \
\n                                                         (w, s: 메뉴 이동, 스페이스바: 메뉴 선택)\
\n                                                                           _____\
\n                                                                           |   |\
\n                                                                           DGIST\
\n                                          _____         ____     __________| o |___________      _________\
\n                                         |o o o|_______|    |___|               | | # # #  |____|o o o o  | \
\n                                         |o o o|  * * *|: ::|. .|               |o| # # #  |. . |o o o o  |\
\n                                         |o o o|* * *  |::  |. .| []  []  []  []|o| # # #  |. . |o o o o  |\
\n                                         |o o o|**  ** |:  :|. .| []  []  []    |o| # # #  |. . |o o o o  |\
\n                                         |_[]__|__[]___|_||_|___|____________□_|_|___□___|_.|_|____[]___|\
\n";
        std::cout << drawing << std::endl;

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
        std::string sequence;
        int x1, y1, x2, y2;


        int building_num = building_list.size();
        int structure_num = structure_list.size();

        std::cout << "스페이스바를 누르시면 투어가 시작됩니다." << std::endl;

        while (true) if (Selector() == 0) break;

        switch (choice) {
            //옵션 1: 최단 경로 출력
            //시작 위치와 도착 위치를 선택하면 두 지점을 잇는 경로를 나타낸다.
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

            std::cout << std::endl << "출발 위치와 도착 위치를 입력하세요." << std::endl;
            std::cout << "예시: E7에서 출발해서 학부생 기숙사로 이동 시 7 16 입력" << std::endl;

            int start_num, end_num;

            while (true) {
                std::string str;
                std::getline(std::cin, str);
                std::istringstream iss{ str };
                iss >> start_num;
                iss >> end_num;

                if (iss.fail()) {
                    std::cout << "숫자 두 개를 입력해주세요." << std::endl;
                    continue;
                }

                break;
            }

            system("cls");

            if (start_num <= building_num) {
                x1 = building_list[start_num - 1].GetXpos();
                y1 = building_list[start_num - 1].GetYpos();
                std::cout << "출발 위치는 ";
                building_list[start_num - 1].PrintName();
            }
            else if (start_num > building_num) {
                x1 = structure_list[start_num - building_num - 1].GetXpos();
                y1 = structure_list[start_num - building_num - 1].GetYpos();
                std::cout << "출발 위치는 ";
                structure_list[start_num - building_num - 1].PrintName();
            }
            if (end_num <= building_num) {
                x2 = building_list[end_num - 1].GetXpos();
                y2 = building_list[end_num - 1].GetYpos();
                std::cout << "이고, 도착 위치는 ";
                building_list[end_num - 1].PrintName();
                std::cout << "입니다." << std::endl;
            }
            else if (end_num > building_num) {
                x2 = structure_list[end_num - building_num - 1].GetXpos();
                y2 = structure_list[end_num - building_num - 1].GetYpos();
                std::cout << "이고, 도착 위치는 ";
                structure_list[end_num - building_num - 1].PrintName();
                std::cout << "입니다." << std::endl;
            }

            std::cout << "최단 경로를 출력합니다." << std::endl << std::endl;
            map.FindShortestWay(x1, y1, x2, y2);
            map.PrintShortestMap();

            break;

            //옵션 2: 추천 경로 출력
            //장소에 대한 설명만을 보고 장소를 순서대로 입력하면, 해당 순서에 맞는 최단 경로를 이어서 나타낸다.
        case 2:
            system("cls");

            for (int i = 0; i < structure_num; i++) {
                std::cout << i + 1 << ". ";
                structure_list[i].PrintName();
                std::cout << ": ";
                structure_list[i].PrintExplanation();
                std::cout << std::endl;
            }
            std::cout << "가고 싶은 장소의 번호를 순서대로 입력하세요." << std::endl;
            std::cout << "예시: 5번, 3번, 1번 장소 순서로 이동 -> 531 입력" << std::endl;

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
            std::cout << "에서 출발하여 ";
            structure_list[sequence[sequence.length() - 1] - '0'].PrintName();
            std::cout << "으로 이동합니다." << std::endl;
            std::cout << "추천 경로를 출력합니다." << std::endl << std::endl;

            map.PrintShortestMap();
            break;

            //옵션 3: 캐릭터를 지도상에서 조작
            //캐릭터가 특정 장소에 도착하면 관련 설명이 출력된다.
        case 3:
            Character person;

            while (true) {
                system("cls");

                map.PrintInformation();
                std::cout << "w: 위, s: 아래, a: 왼쪽, d: 오른쪽, 스페이스바: 종료";

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
        std::cout << "프로그램을 종료합니다." << std::endl;
    }
    return 0;
}