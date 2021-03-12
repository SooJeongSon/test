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
	int m; //���� �ε���


#pragma region ����ȭ��

	cout << "----------------------------------------" << endl;
	cout << "|                                      |" << endl;
	cout << "|                                      |" << endl;
	cout << "|                                      |" << endl;
	cout << "|                                      |" << endl;
	cout << "|            ������ ������!            |" << endl;
	cout << "|                                      |" << endl;
	cout << "|                                      |" << endl;
	cout << "|                                      |" << endl;
	cout << "|                                      |" << endl;
	cout << "----------------------------------------" << endl << endl << endl << endl;

	system("pause"); //����Ϸ��� �ƹ�Ű�� �����ʽÿ�...

#pragma endregion

#pragma region ���� �Էº�

	////�̸� �Էº� -- ���� �̸� �Էº� ���� �߻�...
	while (1)
	{
		system("cls");
		cout << endl << "������ �̸��� �Է��ϼ��� : ";
		cin >> user.name;

		char modify;
		cout << endl << "����� �̸��� " << user.name << endl;

	errorNameKey: //goto...�Ⱦ��� �;����� ��Ȥ�� �����ߴ�!
		cout << endl << "�̸��� �����Ͻðڽ��ϱ�? (Y/N) : ";
		cin >> modify;

		if (modify == 'N' || modify == 'n')
			break;
		else if (modify == 'Y' || modify == 'y')
			continue;
		else
		{
			cout << "Y Ȥ�� N�� �����ּ���" << endl;
			goto errorNameKey;
		}
	}

	//���̵� �Էº�
	while (1)
	{
		system("cls");
		cout << endl << "���� ���̵��� �Է��ϼ���(1~9) : ";
		cin >> game.difficulty;
		

		char modify;
		cout << endl << "�Է��Ͻ� ���̵��� " << game.difficulty << endl;

	errorLevelKey:
		cout << endl << "���̵��� �����Ͻðڽ��ϱ�? (Y/N) : ";
		cin >> modify;

		if (modify == 'N' || modify == 'n')
			break;
		else if (modify == 'Y' || modify == 'y')
			continue;
		else
		{
			cout << "Y Ȥ�� N�� �����ּ���" << endl;
			goto errorLevelKey;
		}
	}
#pragma endregion

#pragma region �ʱ� ������

	user.hp = 100 - game.difficulty * 2;
	monsterRemain = game.difficulty; //���̵� ���� ���� ���� ����
	map.width = 10 + game.difficulty;
	map.height = 10 + game.difficulty;

	char** escape = new char*[map.height];
	for (int i = 0; i < map.height; i++)
	{
		escape[i] = new char[map.width];
	}
		

	for (int i = 0; i < map.height; i++) //��ü �ʱ�ȭ   
	{
		for (int j = 0; j < map.width; j++)
		{
			escape[i][j] = '#';
		}
	}

	for (int i = 0; i < game.difficulty; i++) //���� ��ǥ ����
	{
		mon[i].posX = rand() % map.width;
		mon[i].posY = rand() % map.height;
		if (mon[i].isDead == 1)
			escape[mon[i].posX][mon[i].posY] = '#';
		else
			escape[mon[i].posX][mon[i].posY] = 'M';

		if (mon[i].posX == 0 && mon[i].posY == 0) //0,0 �� ��� �ٽ� �̴´�.
			i--;

		for (int j = 0; j < i - 1; j++)
		{
			if (mon[i].posX == mon[j].posX && mon[i].posY == mon[j].posY)
				i--;
		}
	}

	escape[user.posX][user.posY] = 'O'; //���� ��ǥ�� �÷��̾� ���

#pragma endregion

#pragma region ���� - �̵���

	while (1)//���� ��ü while��
	{
		if (user.hp <= 0) //�й����� 
		{
			system("cls");
			cout << "----------------------------------------" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "|              ���� ����!              |" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "----------------------------------------" << endl << endl << endl << endl;

			system("pause");
			break;
		}

		if (monsterRemain == 0) //�¸�����
		{
			system("cls");
			cout << "----------------------------------------" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "|                                      |" << endl;
			cout << "|             ���� Ŭ����!             |" << endl;
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
			for (int i = 0; i < map.height; i++) //��ü �ʱ�ȭ   
			{
				for (int j = 0; j < map.width; j++)
				{
					escape[i][j] = '#';
				}
			}

			for (int i = 0; i < game.difficulty; i++) //���� ��ǥ ����
			{
				mon[i].posX = rand() % map.width;
				mon[i].posY = rand() % map.height;
				if (mon[i].isDead == 1)
					escape[mon[i].posX][mon[i].posY] = '#';
				else
					escape[mon[i].posX][mon[i].posY] = 'M';

				if (mon[i].posX == 0 && mon[i].posY == 0) //0,0 �� ��� �ٽ� �̴´�.
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

		cout << "=== ���� ü�� : " << user.hp << "  ===" << endl;
		cout << "=== ���� ��� : " << user.money << "  ===" << endl;
		cout << "=== ���� ���� : " << monsterRemain << " ===" << endl << endl;
		cout << "=== �̵��Ͻ÷��� WASD�� �̿��ϼ���(�ȵ� �� �ѿ�Ű)" << " ===" << endl;
		
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
			if (user.posY > map.width)
				user.posY = map.width;
			break;
		default:
			break;
		}

		escape[user.posX][user.posY] = 'O'; //�÷��̾� �̵� ��Ŵ
		game.count++;

		for (m = 0; m < game.difficulty; m++) //���Ϳ� �������� �Ǻ�
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

#pragma region ����-������

		while (game.monMeet == 1)
		{
			system("cls");
			cout << "���͸� �������ϴ�! ���� ����!" << endl;
			while (1)
			{
				int monsterPick = rand() % 3; //���� ����,����,�� ���� �����ϱ� ����. ����=0, ����=1, ��=2
				cout << "Ȯ�ο� ���� �� (����0 ����1 ��2)  " << monsterPick << endl;

				//���� ����, ����, �� �Է�
				string strUserPick; //����, ����, �� �Է°� ������ ����
				cout << "����, ����, �� �߿� �Է� : ";
				cin >> strUserPick;

				//���� ���� ���ϱ� ���� strUserPick�� ���ڷ� ��ȯ
				int userPick = 0; //���ڷ� ��ȯ�� ���� ����,����,�� �� ������ ����
				if (strUserPick == "����")
					userPick = 0;
				else if (strUserPick == "����")
					userPick = 1;
				else if (strUserPick == "��")
					userPick = 2;
				else
				{
					cout << "�߸��� ���� �Է��ϼ̽��ϴ�. �ٽ� �����մϴ�." << endl;
					continue;
				}

				//���� �Ǻ� ���
				//����=0, ����=1, ��=2 ��� ������ 
				//monsterPick - userPick = 2 or -1 �� ��쿡 �¸�, monsterPick - userPick = 1 or -2 �� ��쿡 �й�
				if (monsterPick - userPick == 2 || monsterPick - userPick == -1)
				{
					cout << "�¸�!" << endl << endl;
					monsterRemain--;
					mon[m].isDead = 1;
					int gold = rand() % 101;
					cout << gold << "���� ������ϴ�!" << endl;
					user.money += gold;
					cout << "��� �����Ϸ��� 0�� ������ ���÷��� 1�� �����ÿ� ";
					cin >> game.goMarket;

					break;
				}
				else if (monsterPick - userPick == 1 || monsterPick - userPick == -2)
				{
					cout << "�й�!" << endl << endl;
					user.hp -= 40;
					if (user.hp > 0)
					{
						cout << "�ѿ�Ű�� �����ּ���! ��� �� ���";
						Sleep(5000);
					}
					break;
				}
				else
				{
					cout << "�����ϴ�. �ٽ� ����մϴ�" << endl << endl;
					continue;
				}
			}
			game.monMeet = 0;


		}
#pragma endregion

#pragma region ����-������

		while (game.goMarket == 1)
		{
			system("cls");
			game.goMarket = 0;
			int inputMoney;

			cout << "----------------------------------------" << endl;
			cout << "|                                      |" << endl;
			cout << "|            10ȸ�� = 10��             |" << endl;
			cout << "|                                      |" << endl;
			cout << "|            30ȸ�� = 20��             |" << endl;
			cout << "|                                      |" << endl;
			cout << "|            40ȸ�� = 30��             |" << endl;
			cout << "|                                      |" << endl;
			cout << "|            50ȸ�� = 40��             |" << endl;
			cout << "|                                      |" << endl;
			cout << "----------------------------------------" << endl << endl << endl << endl;
			cout << "���� ���� �Է� : ";
			cin >> inputMoney;

			if (user.money < inputMoney && inputMoney <= 40)
			{
				cout << "���� ���� �����մϴ�. �¹���." << endl;
				cout << "1���� ���";
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
				cout << "���� ��ǰ�Դϴ�. ���� ��ȸ��..." << endl;
				cout << "1���� ���";
				Sleep(1000);
				break;
			}//if�� ��
		}

#pragma endregion

	} //���� while��

	for (int i = 0; i < map.height; i++)
	{
		delete[] escape[i];
	}
	delete[] escape;

	return 0;

}