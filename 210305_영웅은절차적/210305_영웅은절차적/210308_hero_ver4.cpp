#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
using namespace std;

struct Hero
{
	int hp = 100;
	int maxhp = 100;
	string name;
	int posX = 0;
	int posY = 0;
	int money = 0;
};

struct Monster
{
	int posX = 10;
	int posY = 10;
	bool isDead = 0;
};

struct GameData
{
	int difficulty = 0;
	bool goMarket = 0;
	bool monMeet = 0;
	int count = 0;

};

struct MapData
{
	int width = 0;
	int height = 0;
};

int main(void)
{
	srand(time(NULL));
	Hero user;
	Monster mon[20];
	GameData game;
	MapData map;
	int monsterRemain;
	int m; //몬스터 인덱스


#pragma region 시작화면

	cout << "----------------------------------------" << endl;
	cout << "|                                      |" << endl;
	cout << "|                                      |" << endl;
	cout << "|                                      |" << endl;
	cout << "|                                      |" << endl;
	cout << "|            영웅은 절차적!            |" << endl;
	cout << "|                                      |" << endl;
	cout << "|                                      |" << endl;
	cout << "|                                      |" << endl;
	cout << "|                                      |" << endl;
	cout << "----------------------------------------" << endl << endl << endl << endl;

	system("pause"); //계속하려면 아무키나 누르십시오...

#pragma endregion

#pragma region 정보 입력부

	////이름 입력부 -- 현재 이름 입력부 오류 발생...
	while (1)
	{
		system("cls");
		cout << endl << "영웅의 이름을 입력하세요 : ";
		cin >> user.name;

		char modify;
		cout << endl << "당신의 이름은 " << user.name << endl;

	errorNameKey: //goto...안쓰고 싶었지만 유혹은 강렬했다!
		cout << endl << "이름을 수정하시겠습니까? (Y/N) : ";
		cin >> modify;

		if (modify == 'N' || modify == 'n')
			break;
		else if (modify == 'Y' || modify == 'y')
			continue;
		else
		{
			cout << "Y 혹은 N을 눌러주세요" << endl;
			goto errorNameKey;
		}
	}

	//난이도 입력부
	while (1)
	{
		system("cls");
		cout << endl << "게임 난이도를 입력하세요(1~9) : ";
		cin >> game.difficulty;
		

		char modify;
		cout << endl << "입력하신 난이도는 " << game.difficulty << endl;

	errorLevelKey:
		cout << endl << "난이도를 수정하시겠습니까? (Y/N) : ";
		cin >> modify;

		if (modify == 'N' || modify == 'n')
			break;
		else if (modify == 'Y' || modify == 'y')
			continue;
		else
		{
			cout << "Y 혹은 N을 눌러주세요" << endl;
			goto errorLevelKey;
		}
	}
#pragma endregion

#pragma region 초기 설정부

	user.hp = 100 - game.difficulty * 2;
	monsterRemain = game.difficulty; //난이도 수에 따라 몬스터 설정
	map.width = 10 + game.difficulty;
	map.height = 10 + game.difficulty;

	char** escape = new char*[map.height];
	for (int i = 0; i < map.height; i++)
	{
		escape[i] = new char[map.width];
	}
		

	for (int i = 0; i < map.height; i++) //전체 초기화   
	{
		for (int j = 0; j < map.width; j++)
		{
			escape[i][j] = '#';
		}
	}

	for (int i = 0; i < game.difficulty; i++) //몬스터 좌표 설정
	{
		mon[i].posX = rand() % map.width;
		mon[i].posY = rand() % map.height;
		if (mon[i].isDead == 1)
			escape[mon[i].posX][mon[i].posY] = '#';
		else
			escape[mon[i].posX][mon[i].posY] = 'M';

		if (mon[i].posX == 0 && mon[i].posY == 0) //0,0 일 경우 다시 뽑는다.
			i--;

		for (int j = 0; j < i - 1; j++)
		{
			if (mon[i].posX == mon[j].posX && mon[i].posY == mon[j].posY)
				i--;
		}
	}

	escape[user.posX][user.posY] = 'O'; //시작 좌표에 플레이어 출력

#pragma endregion

#pragma region 게임 - 이동부

	while (1)//게임 전체 while문
	{
		if (user.hp <= 0) //패배조건 
		{
			system("cls");
			cout << "----------------------------------------" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "|              게임 오버!              |" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "----------------------------------------" << endl << endl << endl << endl;

			system("pause");
			break;
		}

		if (monsterRemain == 0) //승리조건
		{
			system("cls");
			cout << "----------------------------------------" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "|             게임 클리어!             |" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "----------------------------------------" << endl << endl << endl << endl;
			system("pause");
			break;
		}

		if (game.count % 3 == 0)
		{
			for (int i = 0; i < map.height; i++) //전체 초기화   
			{
				for (int j = 0; j < map.width; j++)
				{
					escape[i][j] = '#';
				}
			}

			for (int i = 0; i < game.difficulty; i++) //몬스터 좌표 설정
			{
				mon[i].posX = rand() % map.width;
				mon[i].posY = rand() % map.height;
				if (mon[i].isDead == 1)
					escape[mon[i].posX][mon[i].posY] = '#';
				else
					escape[mon[i].posX][mon[i].posY] = 'M';

				if (mon[i].posX == 0 && mon[i].posY == 0) //0,0 일 경우 다시 뽑는다.
					i--;

				for (int j = 0; j < i - 1; j++)
				{
					if (mon[i].posX == mon[j].posX && mon[i].posY == mon[j].posY)
						i--;
				}
			}
		}
		escape[user.posX][user.posY] = 'O';

		system("cls");
		cout << endl;
		for (int i = 0; i < map.height; i++)
		{
			for (int j = 0; j < map.width; j++)
			{
				cout << escape[i][j];
			}
			cout << endl;
		}
		cout << endl;

		cout << "=== 현재 체력 : " << user.hp << "  ===" << endl;
		cout << "=== 현재 골드 : " << user.money << "  ===" << endl;
		cout << "=== 남은 몬스터 : " << monsterRemain << " ===" << endl << endl;
		cout << "=== 이동하시려면 WASD를 이용하세요(안될 시 한영키)" << " ===" << endl;
		
		char inputWay;
		inputWay = _getch();

		switch (inputWay)
		{
		case 'W': case 'w':
			escape[user.posX][user.posY] = '#';
			user.posX--;
			if (user.posX < 0)
				user.posX = 0;
			break;
		case 'S': case 's':
			escape[user.posX][user.posY] = '#';
			user.posX++;
			if (user.posX > map.width)
				user.posX = map.width;
			break;
		case 'A': case 'a':
			escape[user.posX][user.posY] = '#';
			user.posY--;
			if (user.posY < 0)
				user.posY = 0;
			break;
		case 'D': case 'd':
			escape[user.posX][user.posY] = '#';
			user.posY++;
			if (user.posY > map.height)
				user.posY = map.height;
			break;
		default:
			break;
		}

		escape[user.posX][user.posY] = 'O'; //플레이어 이동 시킴
		game.count++;

		for (m = 0; m < game.difficulty; m++) //몬스터와 만났는지 판별
		{
			if (user.posX == mon[m].posX && user.posY == mon[m].posY)
			{
				if (mon[m].isDead == 1)
					continue;
				else
				{
					game.monMeet = 1;
					break;
				}

			}
		}

#pragma endregion

#pragma region 게임-전투부

		while (game.monMeet == 1)
		{
			system("cls");
			cout << "몬스터를 만났습니다! 전투 시작!" << endl;
			while (1)
			{
				int monsterPick = rand() % 3; //몬스터 가위,바위,보 랜덤 설정하기 위함. 가위=0, 바위=1, 보=2
				cout << "확인용 몬스터 값 (가위0 바위1 보2)  " << monsterPick << endl;

				//유저 가위, 바위, 보 입력
				string strUserPick; //가위, 바위, 보 입력값 저장할 변수
				cout << "가위, 바위, 보 중에 입력 : ";
				cin >> strUserPick;

				//몬스터 값과 비교하기 위해 strUserPick을 숫자로 변환
				int userPick = 0; //숫자로 변환한 영웅 가위,바위,보 값 저장할 변수
				if (strUserPick == "가위")
					userPick = 0;
				else if (strUserPick == "바위")
					userPick = 1;
				else if (strUserPick == "보")
					userPick = 2;
				else
				{
					cout << "잘못된 값을 입력하셨습니다. 다시 시작합니다." << endl;
					continue;
				}

				//승패 판별 계산
				//가위=0, 바위=1, 보=2 라고 했을때 
				//monsterPick - userPick = 2 or -1 인 경우에 승리, monsterPick - userPick = 1 or -2 인 경우에 패배
				if (monsterPick - userPick == 2 || monsterPick - userPick == -1)
				{
					cout << "승리!" << endl << endl;
					monsterRemain--;
					mon[m].isDead = 1;
					int gold = rand() % 101;
					cout << gold << "원을 얻었습니다!" << endl;
					user.money += gold;
					cout << "계속 진행하려면 0을 상점에 가시려면 1을 누르시오 ";
					cin >> game.goMarket;

					break;
				}
				else if (monsterPick - userPick == 1 || monsterPick - userPick == -2)
				{
					cout << "패배!" << endl << endl;
					user.hp -= 40;
					if (user.hp > 0)
					{
						cout << "한영키를 눌러주세요! 잠시 후 계속";
						Sleep(5000);
					}
					break;
				}
				else
				{
					cout << "비겼습니다. 다시 대결합니다" << endl << endl;
					continue;
				}
			}
			game.monMeet = 0;


		}
#pragma endregion

#pragma region 게임-상점부

		while (game.goMarket == 1)
		{
			system("cls");
			game.goMarket = 0;
			int inputMoney;

			cout << "----------------------------------------" << endl;
			cout << "|                                      |" << endl;
			cout << "|            10회복 = 10원             |" << endl;
			cout << "|                                      |" << endl;
			cout << "|            30회복 = 20원             |" << endl;
			cout << "|                                      |" << endl;
			cout << "|            40회복 = 30원             |" << endl;
			cout << "|                                      |" << endl;
			cout << "|            50회복 = 40원             |" << endl;
			cout << "|                                      |" << endl;
			cout << "----------------------------------------" << endl << endl << endl << endl;
			cout << "구매 가격 입력 : ";
			cin >> inputMoney;

			if (user.money < inputMoney && inputMoney <= 40)
			{
				cout << "가진 돈이 부족합니다. 굿바이." << endl;
				cout << "1초후 계속";
				Sleep(1000);
				break;
			}
			else if (inputMoney == 40)
			{
				user.hp += 50;
				if (user.hp >= 100)
					user.hp = user.maxhp;
				user.money -= 40;
				break;
			}
			else if (inputMoney == 30)
			{
				user.hp += 40;
				if (user.hp >= 100)
					user.hp = user.maxhp;
				user.money -= 30;
				break;
			}
			else if (inputMoney == 20)
			{
				user.hp += 30;
				if (user.hp >= 100)
					user.hp = user.maxhp;
				user.money -= 20;
				break;
			}
			else if (inputMoney == 10)
			{
				user.hp += 10;
				if (user.hp >= 100)
					user.hp = user.maxhp;
				break;
			}
			else
			{
				cout << "없는 상품입니다. 다음 기회에..." << endl;
				cout << "1초후 계속";
				Sleep(1000);
				break;
			}//if문 끝
		}

#pragma endregion

	} //게임 while문

	return 0;

}