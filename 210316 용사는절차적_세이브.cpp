/*
용사는 절차적
세이브 파일 만들기
상점에서 세이브 기능 제공
용사의 위치, 보유골드, 적의 위치, 맵 크기(난이도), 체력 저장


*/

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <conio.h>

#include <fstream>
using namespace std;

#pragma region 구조체 정의

enum TILETYPE { FOREST, SWAMP, EARTH };
enum DIFFICULTY { BEGINNER = 1, INTERMEDIATE = 2, EXPERT = 3 };

struct Tile
{
	int posX = 0;
	int posY = 0;
	TILETYPE type;		// 0 = 숲, 1 = 늪, 2 = 땅
	char shape;		// 0 = 'Y', 1 = 'E', 2 = 'M'
};
struct HERO
{
	string Name;
	int Hp = 10;
	int MaxHp = 10;
	int Exp = 0;
	int Gold = 5;
	int Level = 1;
	int PosX = 0;
	int PosY = 0;
	int offensivePower = 1;
};
struct MONSTER
{
	string Name;
	int PosX = 1;
	int PosY = 1;
	int Hp = 1;
	int Exp = 0;
	int remainMonster = 0;
};
struct POTION
{
	string name[4] = { "최고급포션" , "고급포션" ,"중급포션","하급포션" };
	int price[4] = { 30,12,5,1 };
};
struct STORE
{
	POTION potion;
};
struct GAMEDATA
{
	int difficulty = 0;
	bool meetmonster = 0;
	bool goshop = 0;
	bool winCheck = 0;
	bool loseCheck = 0;
	int gameCnt = 1;
};
struct MAPDATA
{
	int size = 0;
};

HERO hero;
MONSTER monster;
POTION potion;
STORE store;
GAMEDATA game;
MAPDATA mapdata;

#pragma endregion 구조체 정의

#pragma region 함수 선언

void StartScreen();
void GameOverScreen();
void GameClearScreen();
void GetUserInfo();
void SetGameByDifficulty(DIFFICULTY diff);
void SetMonster();
void SetHero(Tile** map);
void MoveHero(Tile** map, Tile** map_check);
void MoveMonster();
void MeetCheck();
void FightMonster(Tile** map);
void Shop();
void CheckLevel();
void SetMap(Tile*** map, Tile*** map_check);
void PrintMap(Tile** map, MONSTER monster);
void PrintStatus();
void CheckCondition();
void FreeMap(Tile** map);

#pragma endregion 함수 선언

int main(void)
{
	Tile** map = nullptr;
	Tile** map_check = nullptr;

	srand(time(NULL));
	StartScreen();
	GetUserInfo();
	SetGameByDifficulty((DIFFICULTY)game.difficulty);
	SetMap(&map, &map_check);
	SetHero(map);
	SetMonster();

	while (1)
	{

		PrintMap(map, monster);
		PrintStatus();
		MoveHero(map, map_check);

		if (game.gameCnt % 3 == 0)
			MoveMonster();

		MeetCheck();

		if (game.meetmonster == 1)
		{
			FightMonster(map_check);
			CheckLevel();
			SetMonster();
			game.meetmonster = 0; //초기화
		}
		if (game.goshop == 1)
		{
			Shop();
			game.goshop = 0; //초기화
		}

		CheckCondition();
		if (game.winCheck == 1)
		{
			GameClearScreen();
			break;
		}
		if (game.loseCheck == 1)
		{
			GameOverScreen();
			break;
		}

		game.gameCnt++;
	}
	FreeMap(map);
	FreeMap(map_check);

	return 0;
}


#pragma region 함수 정의
void StartScreen()
{
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

	system("pause");
}

void GameOverScreen()
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
}

void GameClearScreen()
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
}

void GetUserInfo()
{
	system("cls");
	cout << "이름을 입력하세요 : ";
	cin >> hero.Name;

	cout << "난이도를 입력하세요 (1~3) : ";
	cin >> game.difficulty;

}

void SetGameByDifficulty(DIFFICULTY diff)
{
	switch (diff)
	{
	case BEGINNER:
		monster.remainMonster = 2;
		hero.MaxHp = 10;
		mapdata.size = 10;
		cout << endl;
		cout << "초급으로 설정되었습니다" << endl;
		cout << "몬스터 수 : " << monster.remainMonster << endl;
		cout << "영웅의 최대 체력 : " << hero.MaxHp << endl;
		cout << "맵 사이즈 : " << mapdata.size << " X " << mapdata.size << endl;
		cout << endl;
		system("pause");
		break;

	case INTERMEDIATE:
		monster.remainMonster = 4;
		hero.MaxHp = 12;
		mapdata.size = 12;
		cout << endl;
		cout << "중급으로 설정되었습니다" << endl;
		cout << "몬스터 수 : " << monster.remainMonster << endl;
		cout << "영웅의 최대 체력 : " << hero.MaxHp << endl;
		cout << "맵 사이즈 : " << mapdata.size << " X " << mapdata.size << endl;
		cout << endl;
		system("pause");
		break;

	case EXPERT:
		monster.remainMonster = 7;
		hero.MaxHp = 15;
		mapdata.size = 15;
		cout << endl;
		cout << "고급으로 설정되었습니다" << endl;
		cout << "몬스터 수 : " << monster.remainMonster << endl;
		cout << "영웅의 최대 체력 : " << hero.MaxHp << endl;
		cout << "맵 사이즈 : " << mapdata.size << " X " << mapdata.size << endl;
		cout << endl;
		system("pause");
		break;

	default:
		cout << "잘못된 값을 선택하셨습니다" << endl;
		break;
	}

}

void SetMap(Tile*** map, Tile*** map_check)
{
	(*map) = new Tile * [mapdata.size];
	for (int i = 0; i < mapdata.size; i++)
		(*map)[i] = new Tile[mapdata.size];

	(*map_check) = new Tile * [mapdata.size];
	for (int i = 0; i < mapdata.size; i++)
		(*map_check)[i] = new Tile[mapdata.size];

	for (int j = 0; j < mapdata.size; j++)
	{
		for (int i = 0; i < mapdata.size; i++)
		{
			(*map)[j][i].type = (TILETYPE)(rand() % 3);
			switch ((*map)[j][i].type)
			{
			case TILETYPE::FOREST:
				(*map)[j][i].shape = 'Y';
				(*map_check)[j][i].shape = 'Y';
				break;
			case TILETYPE::SWAMP:
				(*map)[j][i].shape = 'E';
				(*map_check)[j][i].shape = 'E';
				break;
			case TILETYPE::EARTH:
				(*map)[j][i].shape = 'M';
				(*map_check)[j][i].shape = 'M';
				break;
			}
		}
	}
}

void FreeMap(Tile** map)
{

	for (int i = 0; i < mapdata.size; i++)
		delete[] map[i];
	delete[] map;
}

void SetMonster()
{
	while (1)
	{
		monster.PosX = rand() % mapdata.size;
		monster.PosY = rand() % mapdata.size;

		if (monster.PosX != 0 && monster.PosY != 0)
			break;
	}

}

void SetHero(Tile** map)
{
	hero.PosX = 0;
	hero.PosY = 0;
	map[hero.PosX][hero.PosY].shape = 'O';
}

void MoveHero(Tile** map, Tile** map_check)
{
	char inputWay;
	inputWay = _getch();

	switch (inputWay)
	{
	case 'W': case 'w':
		map[hero.PosX][hero.PosY].shape = map_check[hero.PosX][hero.PosY].shape;
		hero.PosX--;
		if (hero.PosX < 0)
			hero.PosX = 0;
		break;
	case 'S': case 's':
		map[hero.PosX][hero.PosY].shape = map_check[hero.PosX][hero.PosY].shape;
		hero.PosX++;
		if (hero.PosX >= mapdata.size - 1)
			hero.PosX = mapdata.size - 1;
		break;
	case 'A': case 'a':
		map[hero.PosX][hero.PosY].shape = map_check[hero.PosX][hero.PosY].shape;
		hero.PosY--;
		if (hero.PosY < 0)
			hero.PosY = 0;
		break;
	case 'D': case 'd':
		map[hero.PosX][hero.PosY].shape = map_check[hero.PosX][hero.PosY].shape;
		hero.PosY++;
		if (hero.PosY >= mapdata.size - 1)
			hero.PosY = mapdata.size - 1;
		break;
	default:
		break;
	}

	map[hero.PosX][hero.PosY].shape = 'O';
}

void MoveMonster()
{
	int randomIndex = rand() % 4;
	if (randomIndex == 0)
	{
		monster.PosX++;
		if (monster.PosX >= mapdata.size)
			monster.PosX = mapdata.size;
		if (monster.PosX == hero.PosX)
			monster.PosX--;
	}
	else if (randomIndex == 1)
	{
		monster.PosX--;
		if (monster.PosX < 0)
			monster.PosX = 0;
		if (monster.PosX == hero.PosX)
			monster.PosX++;
	}
	else if (randomIndex == 2)
	{
		monster.PosY++;
		if (monster.PosY >= mapdata.size)
			monster.PosY = mapdata.size;
		if (monster.PosY == hero.PosY)
			monster.PosY--;
	}
	else
	{
		monster.PosY--;
		if (monster.PosY < 0)
			monster.PosY = 0;
		if (monster.PosY == hero.PosY)
			monster.PosY++;
	}
}

void MeetCheck()
{
	if (hero.PosX == monster.PosX && hero.PosY == monster.PosY)
		game.meetmonster = 1;
	else
		game.meetmonster = 0;
}

void FightMonster(Tile** map_check)
{
	system("cls");
	cout << "!!!!! 몬스터를 만났습니다! 전투 시작!" << endl;

	if (map_check[hero.PosX][hero.PosY].shape == 'Y')
	{
		monster.Hp = 1;
		monster.Exp = 1;
	}
	else if (map_check[hero.PosX][hero.PosY].shape == 'E')
	{
		monster.Hp = 2;
		monster.Exp = 2;
	}
	else if (map_check[hero.PosX][hero.PosY].shape == 'M')
	{
		monster.Hp = 3;
		monster.Exp = 3;
	}

	//가위바위보 전투
	while (monster.Hp > 0)
	{
		//몬스터 가위바위보 고르기
		int monsterPick = rand() % 3;
		cout << "확인용 몬스터 값 가위(0) 바위(1) 보(2) : " << monsterPick << endl << endl;
		cout << "##### 몬스터의 현재 체력 : " << monster.Hp << endl;

		//히어로 가위바위보 고르기
		int userPick;
		while (1)
		{
			cout << "가위(0) 바위(1) 보(2) 중에 숫자로 입력 : ";
			cin >> userPick;
			if (userPick < 0 || userPick >3)
			{
				cout << "0,1,2 중에 고르세요" << endl;
				continue;
			}
			break;
		}

		//승패 판별 - 승리
		if (monsterPick - userPick == 2 || monsterPick - userPick == -1)
		{
			cout << endl << endl << "승리!" << endl << endl;


			//몬스터 체력 감소
			monster.Hp -= hero.offensivePower;
			if (monster.Hp <= 0) // 0이하가 되면 몬스터 완전 죽음
			{
				cout << "몬스터를 죽였습니다!" << endl << endl;
				//골드 얻기
				int getGold;
				getGold = rand() % 30;
				cout << getGold << "원을 얻었습니다!" << endl;
				hero.Gold += getGold;
				//경험치 얻기
				cout << "경험치 " << monster.Exp << "를 얻었습니다!" << endl << endl;
				hero.Exp += monster.Exp;

				cout << "상점을 가시려면 1, 계속하시려면 0을 입력하세요" << endl;
				cin >> game.goshop;
				monster.remainMonster--;
			}

		}

		//승패 판별 - 패배
		else if (monsterPick - userPick == 1 || monsterPick - userPick == -2)
		{
			cout << "패배!" << endl << endl;
			hero.Hp -= 1;
			if (hero.Hp > 0) //히어로 살았을 경우 재대결
			{
				cout << "아직 기회가 남았습니다" << endl;
				system("pause");
				continue;
			}
			else if (hero.Hp <= 0)
			{
				cout << "영원한 패배" << endl;
				system("pause");
			}
			break;
		}

		//승패 판별 - 무승부
		else
		{
			cout << "비겼습니다. 다시 대결합니다" << endl << endl;
			continue;
		}
	}
}

void Shop()
{
	system("cls");
	cout << "$$$$$ 판매 상품 목록 $$$$$" << endl << endl;
	cout << "1번 " << store.potion.name[0] << " : 체력 전체 회복, 가격 : " << store.potion.price[0] << endl;
	cout << "2번 " << store.potion.name[1] << " : 체력 10 회복, 가격 : " << store.potion.price[1] << endl;
	cout << "3번 " << store.potion.name[2] << " : 체력 5 회복, 가격 : " << store.potion.price[2] << endl;
	cout << "4번 " << store.potion.name[3] << " : 체력 1 회복, 가격 : " << store.potion.price[3] << endl;
	cout << "5번 세이브"  << " 가격 : " << store.potion.price[1] << endl;
	cout << "현재 체력 : " << hero.Hp << endl;
	cout << "보유 골드 : " << hero.Gold << endl << endl;

	int selectPotion;
	while (1)
	{
		cout << "무엇을 구매하실 건가요? 상품 번호를 입력하세요" << endl;
		cin >> selectPotion;

		switch (selectPotion)
		{
		case 1:
			if (hero.Gold < store.potion.price[0])
			{
				cout << "가진 돈이 부족합니다" << endl;
				continue;
			}
			else
			{
				hero.Hp = hero.MaxHp;
				hero.Gold -= store.potion.price[0];
				break;
			}

		case 2:
			if (hero.Gold < store.potion.price[1])
			{
				cout << "가진 돈이 부족합니다" << endl;
				continue;
			}
			else
			{
				hero.Hp += 10;
				hero.Gold -= store.potion.price[1];
				break;
			}

		case 3:
			if (hero.Gold < store.potion.price[2])
			{
				cout << "가진 돈이 부족합니다" << endl;
				continue;
			}
			else
			{
				hero.Hp += 5;
				hero.Gold -= store.potion.price[2];
				break;
			}
		case 4:
			if (hero.Gold < store.potion.price[3])
			{
				cout << "가진 돈이 부족합니다" << endl;
				continue;
			}
			else
			{
				hero.Hp += 1;
				hero.Gold -= store.potion.price[3];
				break;
			}
		case 5:
			if(hero.Gold < store.potion.price[1])
			{
				cout << "가진 돈이 부족합니다" << endl;
				continue;
			}
			else
			{
				ofstream fout;
				fout.open("savaData.txt");
				fout << "용사 체력 : " << hero.Hp << endl;
				fout << "용사 위치 : " << hero.PosX << ", " << hero.PosY << endl;
				fout << "보유 골드 : " << hero.Gold - store.potion.price[1] << endl;
				fout << "적의 위치 : " << monster.PosX << ", " << monster.PosY << endl;
				fout << "현재 난이도 : " << game.difficulty << endl;

				fout.close();
				
				hero.Gold -= store.potion.price[1];
				break;
			}
			break;
		default:
			cout << "없는 상품을 고르셨습니다" << endl;
			continue;

		}
		break;
	}

}

void CheckLevel()
{
	if (hero.Exp < 5)
	{
		hero.Level = 1;
		hero.offensivePower = 1;
	}

	else if (hero.Exp < 10)
	{
		hero.Level = 2;
		hero.offensivePower = 2;
	}
	else
	{
		hero.Level = 3;
		hero.offensivePower = 3;
	}
}

void PrintMap(Tile** map, MONSTER monster)
{
	system("cls");
	for (int j = 0; j < mapdata.size; j++)
	{
		for (int i = 0; i < mapdata.size; i++)
		{
			cout << map[j][i].shape;
		}
		cout << endl;
	}
	cout << "(지울것) 몬스터 좌표 " << monster.PosX << ", " << monster.PosY;
}

void PrintStatus()
{
	cout << endl;
	cout << "현재 체력 : " << hero.Hp << endl;
	cout << "보유 골드 : " << hero.Gold << endl;
	cout << endl;
}

void CheckCondition()
{
	if (hero.Hp > 0 && monster.remainMonster == 0)
		game.winCheck = 1;

	if (hero.Hp <= 0)
		game.loseCheck = 1;

}

#pragma endregion 함수 정의