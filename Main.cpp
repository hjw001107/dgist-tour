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
//모든 파일의 위쪽에는 파일의 내용에 대한 주석을 작성한다.
//.h 파일은 그 안에 정의된 것, 사용되는 방식에 대해 설명한다.
//.cpp 파일은 구현의 세부사항, 알고리즘에 대해 설명한다.
///////////////////////////////////////////////////////////////////////////

//structure_list.txt 파일과 attraction_list.txt 내에서 콤마와 엔터로 구별되어 있는 건물들의 좌표와 설명을 받아와서 vector에 저장한다.
//이후 해당 vector의 요소 4가지를 인자로 attraction과 structure 인스턴스를 생성한다.
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

//위에서 생성된 attraction과 building의 인스턴스를 인수로 가지고 있는 vector를 만든다.
std::vector<Attraction> attraction_list = ReadFromFIle<Attraction>("attraction_list.txt");
std::vector<Structure> structure_list = ReadFromFIle<Structure>("structure_list.txt");

//시작 화면이 그려져 있는 intro.txt를 읽어 문자열로 만든다.
std::string ReadIntroDrawing() {
    std::ifstream ifs{ "intro.txt", std::ifstream::binary };
    return std::string((std::istreambuf_iterator<char>(ifs)),
        std::istreambuf_iterator<char>());
}


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
        
        //시작 화면에서 커서를 조종한다. 위, 아래, 엔터(혹은 스페이스)만으로 구성되어있으며, 이외의 값 입력에 대한 예외처리도 되어 있다.
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

//옵션 1에 대한 함수이다. 건물 리스트를 제시 후, 두 개의 숫자를 받아 해당하는 건물 사이의 최단 경로를 출력한다.
void MainCase1(Map& map, const int& structure_num, const int& attraction_num) {
    int start_num, end_num;
    int x1, y1, x2, y2;
    do {
        try {
            //structure_list와 attraction_list를 숫자를 붙여 출력한다.
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

            //사용자가 쳐 넣은 두 개의 값을 인식하여 integer로 변환한다.
            std::string str;
            std::getline(std::cin, str);
            std::istringstream iss{ str };
            iss >> start_num;
            iss >> end_num;

            //integer로 변환 실패 시 throw
            if (iss.fail()) {
                throw iss.str();
            }
            //start_num과 end_num이 상정된 범위를 벗어날 시 throw
            if (start_num <= 0 || start_num > 32 || start_num == end_num) {
                throw start_num;
            }
            if (end_num <= 0 || end_num > 32) {
                throw end_num;
            }

            //각 숫자에 맞는 건물을 인식, 해당 건물의 x, y 좌표를 읽어서 두 x,y 좌표 간의 최단 경로를 표시한다.
            //map에서 캐릭터가 지나다닐 수 있는 경로만을 이용하여 최단 경로가 짜여진다.
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

        //범위에 벗어난 숫자를 입력시에는 잘못된 숫자를 입력하였다고 뜬다.
        catch (int expn) {
            system("cls");
            std::cout << expn << ": 잘못된 숫자를 입력하셨습니다." << std::endl;
        }
        //integer 변환 실패시, 문자를 입력하였다고 뜬다. 
        catch (std::string expn) {
            system("cls");
            std::cout << expn << ": 문자를 입력하셨습니다." << std::endl;
        }
        //숫자 입력에 대한 예외 발생 시 엔터(스페이스바)를 누르면 다시 숫자 입력으로 돌아간다.
        //올바른 숫자 입력 시까지 반복된다.
        std::cout << "1에서 32까지의 숫자를 중복하지 않고 입력해주세요." << std::endl;
        std::cout << "스페이스바를 누르시면 목록으로 다시 돌아갑니다." << std::endl;
        while (true) {
            if (Selector() == DIRECTION_ENTER) break;
        }
    } while (true);
}

//옵션 2에 대한 함수이다. 해당 함수는 추천 경로 출력을 담당한다.
//장소에 대한 설명만을 보고 장소를 순서대로 입력하면, 해당 순서에 맞는 최단 경로를 이어서 나타낸다.
void MainCase2(Map& map, const int& attraction_num) {
    int x1, y1, x2, y2, temp;
    std::vector <int>  sequence;
    //std::string sequence, temp;
    int sequence_count;
    do {
        try {
            system("cls");
            for (int i = 0; i < attraction_num; i++) {
                std::cout << i + 1 << ". ";
                attraction_list[i].PrintName();
                std::cout << ": ";
                attraction_list[i].PrintInformation();
                std::cout << std::endl;
            }
            // 최소 2개, 최대 9개까지 장소를 입력받기 때문에, 입력받을 장소의 개수를 먼저 입력받아 sequence_count에 저장한다.
            std::cout << "가고 싶은 장소의 개수를 입력하세요." << std::endl;
            std::string str1;
            std::getline(std::cin, str1);
            std::istringstream iss1{ str1 };
            iss1 >> sequence_count;

            //integer로 변환 실패 시 throw 
            if (iss1.fail()) {
                throw iss1.str();
            }
            //sequence_count가 범위를 벗어날 시 throw 
            if (sequence_count <= 1 || sequence_count > 9)
            {
                throw sequence_count;
            }
            std::cout << "가고 싶은 장소의 숫자를 순서대로 입력하세요." << std::endl;
            std::cout << "예시: 5번, 3번, 1번 장소 순서로 이동 -> 5 3 1을 입력" << std::endl;

            //사용자가 쳐 넣은 sequence_count만큼의 값을 인식하여 integer로 변환한다.
            std::string str2;
            std::getline(std::cin, str2);
            std::istringstream iss2{ str2 };
            for (int i = 0; i < sequence_count; i++) {
                iss2 >> temp;

                //integer로 변환 실패 시 throw
                if (iss2.fail()) {
                    std::vector <int> new_vector;
                    sequence = new_vector;
                    throw iss2.str();
                }

                //sequence_count가 범위를 벗어날 시 throw 
                if (temp < 1 || temp > 9)
                {
                    std::vector <int> new_vector;
                    sequence = new_vector;
                    throw temp;
                }

                // 이후 각각의 값을 sequence에 집어넣는다.
                sequence.push_back(temp);
            }

            //sequence에서 두 개의 값씩 차례대로 뽑아서 x, y좌표를 뽑아 최단경로를 찾는다.
            //모든 최단경로가 중복되어 그려진 map을 출력한다.
            for (int i = 1; i < sequence_count; i++) {
                x1 = attraction_list[sequence[i - 1]].GetXpos();
                y1 = attraction_list[sequence[i - 1]].GetYpos();
                x2 = attraction_list[sequence[i]].GetXpos();
                y2 = attraction_list[sequence[i]].GetYpos();
                map.FindShortestWay(x1, y1, x2, y2);
            }
            system("cls");
            attraction_list[*(sequence.begin())].PrintName();
            std::cout << "에서 출발하여 ";
            attraction_list[*(sequence.end() - 1)].PrintName();
            std::cout << "으로 이동합니다." << std::endl;
            std::cout << "추천 경로를 출력합니다." << std::endl << std::endl;

            map.PrintMap(map.GetShortestMap());
            break;
        }

        //범위에 벗어난 숫자를 입력시에는 잘못된 숫자를 입력하였다고 뜬다.
        catch (int expn) {
            system("cls");
            std::cout << expn << ": 잘못된 숫자를 입력하셨습니다." << std::endl;

        }

        //integer 변환 실패시, 문자를 입력하였다고 뜬다. 
        catch (std::string expn) {
            system("cls");
            std::cout << expn << ": 문자를 입력하셨습니다." << std::endl;
        }

        //숫자 입력에 대한 예외 발생 시 엔터(스페이스바)를 누르면 다시 숫자 입력으로 돌아간다.
        //올바른 숫자 입력 시까지 반복된다.
        std::cout << "1에서 9까지의 숫자를 올바르게 입력해주세요." << std::endl;
        std::cout << "스페이스바를 누르시면 목록으로 다시 돌아갑니다." << std::endl;
        while (true) {
            if (Selector() == DIRECTION_ENTER) break;
        }
    } while (true);
}

void MainCase3(Map& map, const int& structure_num, const int& attraction_num) {
    Character person;
    while (true) {
        system("cls");
        map.PrintMap(map.GetMap());
        std::cout << "w: 위로 1칸 이동, s: 아래로 1칸 이동, a: 왼쪽으로 1칸 이동, d: 오른쪽으로 1칸 이동, q: 디지스트 사이버 투어 홈페이지 연결" << std::endl;
        std::cout << "8: 위로 5칸 이동, 2: 아래로 5칸 이동, 4: 왼쪽으로 5칸 이동, 6: 오른쪽으로 5칸 이동, 스페이스바: 종료";
        CursorPos(0, 33);

        //건물과 같은 좌표에 character의 좌표가 인식되면, 해당 건물의 이름과 정보를 출력한다.
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
        
        //character의 위치를 출력해준다.
        person.PrintInformation();
        
        //스페이스바나 엔터 출력시 이전 메뉴로 돌아간다.
        int direction = Selector();
        if (direction == DIRECTION_ENTER) {
            CursorPos(0, 35);
            break;
        }
        
        //특정 키 입력시 dgist cyber tour URL 링크로 연결이 된다.
        if (direction == DIRECTION_STAY) {
            system("explorer https://www.dgist.ac.kr/site/cyber/tour/");
        }
        person.MovePlayer(direction, map);
    }
}

//시작 화면에서 w, s 키를 이용하여 옵션 1-4 중에 하나를 선택한다.
//각 옵션에 맞는 기능이 실행된다(옵션 1: 최단 경로, 옵션 2: 추천 경로, 옵션 3: 캐릭터 조작, 옵션 4: 종료).
int main() {
    while (true) {
        int choice = StartProgram();
        std::cout << "옵션 " << choice << "을(를) 선택하셨습니다." << std::endl;
        if (choice == 1 || choice == 2 || choice == 3) {
            Map map;
            int structure_num = structure_list.size();
            int attraction_num = attraction_list.size();

            std::cout << "스페이스바를 누르시면 투어가 시작됩니다." << std::endl;
            while (true) if (Selector() == 0) break;
            system("cls");

            switch (choice) {
                //옵션 1:
            case 1:
                MainCase1(map, structure_num, attraction_num);
                break;

                //옵션 2 
            case 2:
                MainCase2(map, attraction_num);
                break;

                //옵션 3
            case 3:
                MainCase3(map, structure_num, attraction_num);
                break;
            }
            //스페이스 혹은 엔터를 이용해 이전 메뉴로 돌아갈 수 있다.
            std::cout << "스페이스바를 누르시면 메뉴로 돌아갑니다." << std::endl;
            while (true) if (Selector() == 0) break;
            system("cls");
        }
        //start 메뉴에서 옵션 4를 선택해야만 프로그램이 종료된다.
        else {
            std::cout << "프로그램을 종료합니다." << std::endl;
            break;
        }
    }
    return 0;
}