//#include <iostream>
//#include <ctime>
//#include <cstdlib>
//#include <string>
//#include <conio.h>
//using namespace std;
//
//#pragma region ����ü ����
//
//enum TILETYPE { FOREST, SWAMP, EARTH };
//enum DIFFICULTY { BEGINNER = 1, INTERMEDIATE = 2, EXPERT = 3 };
//
//struct Tile
//{
//	int posX = 0;
//	int posY = 0;
//	TILETYPE type;		// 0 = ��, 1 = ��, 2 = ��
//	char shape;		// 0 = 'Y', 1 = 'E', 2 = 'M'
//};
//struct HERO
//{
//	string Name;
//	int Hp = 10;
//	int MaxHp = 10;
//	int Exp = 0;
//	int Gold = 5;
//	int Level = 1;
//	int PosX = 0;
//	int PosY = 0;
//	int offensivePower = 1;
//};
//struct MONSTER
//{
//	string Name;
//	int PosX = 1;
//	int PosY = 1;
//	int Hp = 1;
//	int Exp = 0;
//	int remainMonster = 0;
//};
//struct POTION
//{
//	string name[4] = { "�ְ������" , "�������" ,"�߱�����","�ϱ�����" };
//	int price[4] = { 30,12,5,1 };
//};
//struct STORE
//{
//	POTION potion;
//};
//struct GAMEDATA
//{
//	int difficulty = 0;
//	bool meetmonster = 0;
//	bool goshop = 0;
//	bool winCheck = 0;
//	bool loseCheck = 0;
//	int gameCnt = 1;
//};
//struct MAPDATA
//{
//	int size = 0;
//};
//
//HERO hero;
//MONSTER monster;
//POTION potion;
//STORE store;
//GAMEDATA game;
//MAPDATA mapdata;
//
//#pragma endregion ����ü ����
//
//#pragma region �Լ� ����
//
//void StartScreen();
//void GameOverScreen();
//void GameClearScreen();
//void GetUserInfo();
//void SetGameByDifficulty(DIFFICULTY diff);
//void SetMonster();
//void SetHero(Tile** map);
//void MoveHero(Tile** map, Tile** map_check);
//void MoveMonster();
//void MeetCheck();
//void FightMonster(Tile** map);
//void Shop();
//void CheckLevel();
//void SetMap(Tile*** map, Tile*** map_check);
//void PrintMap(Tile** map, MONSTER monster);
//void PrintStatus();
//void CheckCondition();
//void FreeMap(Tile** map);
//
//#pragma endregion �Լ� ����
//
//int main(void)
//{
//	Tile** map = nullptr;
//	Tile** map_check = nullptr;
//
//	srand(time(NULL));
//	StartScreen();
//	GetUserInfo();
//	SetGameByDifficulty((DIFFICULTY)game.difficulty);
//	SetMap(&map, &map_check);
//	SetHero(map);
//	SetMonster();
//
//	while (1)
//	{
//
//		PrintMap(map, monster);
//		PrintStatus();
//		MoveHero(map, map_check);
//
//		if (game.gameCnt % 3 == 0)
//			MoveMonster();
//
//		MeetCheck();
//
//		if (game.meetmonster == 1)
//		{
//			FightMonster(map_check);
//			CheckLevel();
//			SetMonster();
//			game.meetmonster = 0; //�ʱ�ȭ
//		}
//		if (game.goshop == 1)
//		{
//			Shop();
//			game.goshop = 0; //�ʱ�ȭ
//		}
//
//		CheckCondition();
//		if (game.winCheck == 1)
//		{
//			GameClearScreen();
//			break;
//		}
//		if (game.loseCheck == 1)
//		{
//			GameOverScreen();
//			break;
//		}
//
//		game.gameCnt++;
//	}
//	FreeMap(map);
//	FreeMap(map_check);
//
//	return 0;
//}
//
//
//#pragma region �Լ� ����
//void StartScreen()
//{
//	cout << "----------------------------------------" << endl;
//	cout << "|                                      |" << endl;
//	cout << "|                                      |" << endl;
//	cout << "|                                      |" << endl;
//	cout << "|                                      |" << endl;
//	cout << "|            ������ ������!            |" << endl;
//	cout << "|                                      |" << endl;
//	cout << "|                                      |" << endl;
//	cout << "|                                      |" << endl;
//	cout << "|                                      |" << endl;
//	cout << "----------------------------------------" << endl << endl << endl << endl;
//
//	system("pause");
//}
//
//void GameOverScreen()
//{
//	system("cls");
//	cout << "----------------------------------------" << endl;
//	cout << "|                                      |" << endl;
//	cout << "|                                      |" << endl;
//	cout << "|                                      |" << endl;
//	cout << "|                                      |" << endl;
//	cout << "|              ���� ����!              |" << endl;
//	cout << "|                                      |" << endl;
//	cout << "|                                      |" << endl;
//	cout << "|                                      |" << endl;
//	cout << "|                                      |" << endl;
//	cout << "----------------------------------------" << endl << endl << endl << endl;
//}
//
//void GameClearScreen()
//{
//	system("cls");
//	cout << "----------------------------------------" << endl;
//	cout << "|                                      |" << endl;
//	cout << "|                                      |" << endl;
//	cout << "|                                      |" << endl;
//	cout << "|                                      |" << endl;
//	cout << "|             ���� Ŭ����!             |" << endl;
//	cout << "|                                      |" << endl;
//	cout << "|                                      |" << endl;
//	cout << "|                                      |" << endl;
//	cout << "|                                      |" << endl;
//	cout << "----------------------------------------" << endl << endl << endl << endl;
//}
//
//void GetUserInfo()
//{
//	system("cls");
//	cout << "�̸��� �Է��ϼ��� : ";
//	cin >> hero.Name;
//
//	cout << "���̵��� �Է��ϼ��� (1~3) : ";
//	cin >> game.difficulty;
//
//}
//
//void SetGameByDifficulty(DIFFICULTY diff)
//{
//	switch (diff)
//	{
//	case BEGINNER:
//		monster.remainMonster = 2;
//		hero.MaxHp = 10;
//		mapdata.size = 10;
//		cout << endl;
//		cout << "�ʱ����� �����Ǿ����ϴ�" << endl;
//		cout << "���� �� : " << monster.remainMonster << endl;
//		cout << "������ �ִ� ü�� : " << hero.MaxHp << endl;
//		cout << "�� ������ : " << mapdata.size << " X " << mapdata.size << endl;
//		cout << endl;
//		system("pause");
//		break;
//
//	case INTERMEDIATE:
//		monster.remainMonster = 4;
//		hero.MaxHp = 12;
//		mapdata.size = 12;
//		cout << endl;
//		cout << "�߱����� �����Ǿ����ϴ�" << endl;
//		cout << "���� �� : " << monster.remainMonster << endl;
//		cout << "������ �ִ� ü�� : " << hero.MaxHp << endl;
//		cout << "�� ������ : " << mapdata.size << " X " << mapdata.size << endl;
//		cout << endl;
//		system("pause");
//		break;
//
//	case EXPERT:
//		monster.remainMonster = 7;
//		hero.MaxHp = 15;
//		mapdata.size = 15;
//		cout << endl;
//		cout << "������� �����Ǿ����ϴ�" << endl;
//		cout << "���� �� : " << monster.remainMonster << endl;
//		cout << "������ �ִ� ü�� : " << hero.MaxHp << endl;
//		cout << "�� ������ : " << mapdata.size << " X " << mapdata.size << endl;
//		cout << endl;
//		system("pause");
//		break;
//
//	default:
//		cout << "�߸��� ���� �����ϼ̽��ϴ�" << endl;
//		break;
//	}
//
//}
//
//void SetMap(Tile*** map, Tile*** map_check)
//{
//	(*map) = new Tile * [mapdata.size];
//	for (int i = 0; i < mapdata.size; i++)
//		(*map)[i] = new Tile[mapdata.size];
//
//	(*map_check) = new Tile * [mapdata.size];
//	for (int i = 0; i < mapdata.size; i++)
//		(*map_check)[i] = new Tile[mapdata.size];
//
//	for (int j = 0; j < mapdata.size; j++)
//	{
//		for (int i = 0; i < mapdata.size; i++)
//		{
//			(*map)[j][i].type = (TILETYPE)(rand() % 3);
//			switch ((*map)[j][i].type)
//			{
//			case TILETYPE::FOREST:
//				(*map)[j][i].shape = 'Y';
//				(*map_check)[j][i].shape = 'Y';
//				break;
//			case TILETYPE::SWAMP:
//				(*map)[j][i].shape = 'E';
//				(*map_check)[j][i].shape = 'E';
//				break;
//			case TILETYPE::EARTH:
//				(*map)[j][i].shape = 'M';
//				(*map_check)[j][i].shape = 'M';
//				break;
//			}
//		}
//	}
//}
//
//void FreeMap(Tile** map)
//{
//
//	for (int i = 0; i < mapdata.size; i++)
//		delete[] map[i];
//	delete[] map;
//}
//
//void SetMonster()
//{
//	while (1)
//	{
//		monster.PosX = rand() % mapdata.size;
//		monster.PosY = rand() % mapdata.size;
//
//		if (monster.PosX != 0 && monster.PosY != 0)
//			break;
//	}
//
//}
//
//void SetHero(Tile** map)
//{
//	hero.PosX = 0;
//	hero.PosY = 0;
//	map[hero.PosX][hero.PosY].shape = 'O';
//}
//
//void MoveHero(Tile** map, Tile** map_check)
//{
//	char inputWay;
//	inputWay = _getch();
//
//	switch (inputWay)
//	{
//	case 'W': case 'w':
//		map[hero.PosX][hero.PosY].shape = map_check[hero.PosX][hero.PosY].shape;
//		hero.PosX--;
//		if (hero.PosX < 0)
//			hero.PosX = 0;
//		break;
//	case 'S': case 's':
//		map[hero.PosX][hero.PosY].shape = map_check[hero.PosX][hero.PosY].shape;
//		hero.PosX++;
//		if (hero.PosX >= mapdata.size-1)
//			hero.PosX = mapdata.size-1;
//		break;
//	case 'A': case 'a':
//		map[hero.PosX][hero.PosY].shape = map_check[hero.PosX][hero.PosY].shape;
//		hero.PosY--;
//		if (hero.PosY < 0)
//			hero.PosY = 0;
//		break;
//	case 'D': case 'd':
//		map[hero.PosX][hero.PosY].shape = map_check[hero.PosX][hero.PosY].shape;
//		hero.PosY++;
//		if (hero.PosY >= mapdata.size-1)
//			hero.PosY = mapdata.size-1;
//		break;
//	default:
//		break;
//	}
//
//	map[hero.PosX][hero.PosY].shape = 'O';
//}
//
//void MoveMonster()
//{
//	int randomIndex = rand() % 4;
//	if (randomIndex == 0)
//	{
//		monster.PosX++;
//		if (monster.PosX >= mapdata.size)
//			monster.PosX = mapdata.size;
//		if (monster.PosX == hero.PosX)
//			monster.PosX--;
//	}
//	else if (randomIndex == 1)
//	{
//		monster.PosX--;
//		if (monster.PosX < 0)
//			monster.PosX = 0;
//		if (monster.PosX == hero.PosX)
//			monster.PosX++;
//	}
//	else if (randomIndex == 2)
//	{
//		monster.PosY++;
//		if (monster.PosY >= mapdata.size)
//			monster.PosY = mapdata.size;
//		if (monster.PosY == hero.PosY)
//			monster.PosY--;
//	}
//	else
//	{
//		monster.PosY--;
//		if (monster.PosY < 0)
//			monster.PosY = 0;
//		if (monster.PosY == hero.PosY)
//			monster.PosY++;
//	}
//}
//
//void MeetCheck()
//{
//	if (hero.PosX == monster.PosX && hero.PosY == monster.PosY)
//		game.meetmonster = 1;
//	else
//		game.meetmonster = 0;
//}
//
//void FightMonster(Tile** map_check)
//{
//	system("cls");
//	cout << "!!!!! ���͸� �������ϴ�! ���� ����!" << endl;
//
//	if (map_check[hero.PosX][hero.PosY].shape == 'Y')
//	{
//		monster.Hp = 1;
//		monster.Exp = 1;
//	}
//	else if (map_check[hero.PosX][hero.PosY].shape == 'E')
//	{
//		monster.Hp = 2;
//		monster.Exp = 2;
//	}
//	else if (map_check[hero.PosX][hero.PosY].shape == 'M')
//	{
//		monster.Hp = 3;
//		monster.Exp = 3;
//	}
//
//	//���������� ����
//	while (monster.Hp > 0)
//	{
//		//���� ���������� ����
//		int monsterPick = rand() % 3;
//		cout << "Ȯ�ο� ���� �� ����(0) ����(1) ��(2) : " << monsterPick << endl << endl;
//		cout << "##### ������ ���� ü�� : " << monster.Hp << endl;
//
//		//����� ���������� ����
//		int userPick;
//		while (1)
//		{
//			cout << "����(0) ����(1) ��(2) �߿� ���ڷ� �Է� : ";
//			cin >> userPick;
//			if (userPick < 0 || userPick >3)
//			{
//				cout << "0,1,2 �߿� ������" << endl;
//				continue;
//			}
//			break;
//		}
//
//		//���� �Ǻ� - �¸�
//		if (monsterPick - userPick == 2 || monsterPick - userPick == -1)
//		{
//			cout << endl << endl << "�¸�!" << endl << endl;
//
//
//			//���� ü�� ����
//			monster.Hp -= hero.offensivePower;
//			if (monster.Hp <= 0) // 0���ϰ� �Ǹ� ���� ���� ����
//			{
//				cout << "���͸� �׿����ϴ�!" << endl << endl;
//				//��� ���
//				int getGold;
//				getGold = rand() % 30;
//				cout << getGold << "���� ������ϴ�!" << endl;
//				hero.Gold += getGold;
//				//����ġ ���
//				cout << "����ġ " << monster.Exp << "�� ������ϴ�!" << endl << endl;
//				hero.Exp += monster.Exp;
//
//				cout << "������ ���÷��� 1, ����Ͻ÷��� 0�� �Է��ϼ���" << endl;
//				cin >> game.goshop;
//				monster.remainMonster--;
//			}
//
//		}
//
//		//���� �Ǻ� - �й�
//		else if (monsterPick - userPick == 1 || monsterPick - userPick == -2)
//		{
//			cout << "�й�!" << endl << endl;
//			hero.Hp -= 1;
//			if (hero.Hp > 0) //����� ����� ��� ����
//			{
//				cout << "���� ��ȸ�� ���ҽ��ϴ�" << endl;
//				system("pause");
//				continue;
//			}
//			else if (hero.Hp <= 0)
//			{
//				cout << "������ �й�" << endl;
//				system("pause");
//			}
//			break;
//		}
//
//		//���� �Ǻ� - ���º�
//		else
//		{
//			cout << "�����ϴ�. �ٽ� ����մϴ�" << endl << endl;
//			continue;
//		}
//	}
//}
//
//void Shop()
//{
//	system("cls");
//	cout << "$$$$$ �Ǹ� ��ǰ ��� $$$$$" << endl << endl;
//	cout << "1�� " << store.potion.name[0] << " : ü�� ��ü ȸ��, ���� : " << store.potion.price[0] << endl;
//	cout << "2�� " << store.potion.name[1] << " : ü�� 10 ȸ��, ���� : " << store.potion.price[1] << endl;
//	cout << "3�� " << store.potion.name[2] << " : ü�� 5 ȸ��, ���� : " << store.potion.price[2] << endl;
//	cout << "4�� " << store.potion.name[3] << " : ü�� 1 ȸ��, ���� : " << store.potion.price[3] << endl << endl;
//	cout << "���� ü�� : " << hero.Hp << endl;
//	cout << "���� ��� : " << hero.Gold << endl << endl;
//
//	int selectPotion;
//	while (1)
//	{
//		cout << "������ �����Ͻ� �ǰ���? ��ǰ ��ȣ�� �Է��ϼ���" << endl;
//		cin >> selectPotion;
//
//		switch (selectPotion)
//		{
//		case 1:
//			if (hero.Gold < store.potion.price[0])
//			{
//				cout << "���� ���� �����մϴ�" << endl;
//				continue;
//			}
//			else
//			{
//				hero.Hp = hero.MaxHp;
//				hero.Gold -= store.potion.price[0];
//				break;
//			}
//
//		case 2:
//			if (hero.Gold < store.potion.price[1])
//			{
//				cout << "���� ���� �����մϴ�" << endl;
//				continue;
//			}
//			else
//			{
//				hero.Hp += 10;
//				hero.Gold -= store.potion.price[1];
//				break;
//			}
//
//		case 3:
//			if (hero.Gold < store.potion.price[2])
//			{
//				cout << "���� ���� �����մϴ�" << endl;
//				continue;
//			}
//			else
//			{
//				hero.Hp += 5;
//				hero.Gold -= store.potion.price[2];
//				break;
//			}
//		case 4:
//			if (hero.Gold < store.potion.price[3])
//			{
//				cout << "���� ���� �����մϴ�" << endl;
//				continue;
//			}
//			else
//			{
//				hero.Hp += 1;
//				hero.Gold -= store.potion.price[3];
//				break;
//			}
//		default:
//			cout << "���� ��ǰ�� ���̽��ϴ�" << endl;
//			continue;
//
//		}
//		break;
//	}
//
//}
//
//void CheckLevel()
//{
//	if (hero.Exp < 5)
//	{
//		hero.Level = 1;
//		hero.offensivePower = 1;
//	}
//
//	else if (hero.Exp < 10)
//	{
//		hero.Level = 2;
//		hero.offensivePower = 2;
//	}
//	else
//	{
//		hero.Level = 3;
//		hero.offensivePower = 3;
//	}
//}
//
//void PrintMap(Tile** map, MONSTER monster)
//{
//	system("cls");
//	for (int j = 0; j < mapdata.size; j++)
//	{
//		for (int i = 0; i < mapdata.size; i++)
//		{
//			cout << map[j][i].shape;
//		}
//		cout << endl;
//	}
//	cout << "(�����) ���� ��ǥ " << monster.PosX << ", " << monster.PosY;
//}
//
//void PrintStatus()
//{
//	cout << endl;
//	cout << "���� ü�� : " << hero.Hp << endl;
//	cout << "���� ��� : " << hero.Gold << endl;
//	cout << endl;
//}
//
//void CheckCondition()
//{
//	if (hero.Hp > 0 && monster.remainMonster == 0)
//		game.winCheck = 1;
//
//	if (hero.Hp <= 0)
//		game.loseCheck = 1;
//
//}
//
//#pragma endregion �Լ� ����