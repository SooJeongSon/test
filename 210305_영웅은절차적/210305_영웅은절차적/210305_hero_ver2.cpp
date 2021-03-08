#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <windows.h>
using namespace std;


//���� �и�
//�ʿ� ü�� ���� ����
//���� �ߺ� �̱� ����
//���� ���̱�

struct Hero
{
	int hp = 100;
	string name;
	int posX = 0; 
	int posY = 0;
	int difficulty = 0; //���� ������ ����ü�� �з��ؾ� �Ѵ�.
	int money = 0;
};

struct Monster
{
	int posX;
	int posY;
};


int main_1(void)
{
	srand(time(NULL));
	Hero user;
	Monster mon[10];
	int monsterRemain;

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

	//�̸� �Էº�
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
		cin >> user.difficulty;
		user.hp = 100 - user.difficulty * 2;
		monsterRemain = user.difficulty; //���̵� ���� ���� ���� ����

		char modify;
		cout << endl << "�Է��Ͻ� ���̵��� " << user.difficulty << endl;

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

	char escape[10][10];

	for (int i = 0; i < 10; i++) //��ü �ʱ�ȭ   
	{
		for (int j = 0; j < 10; j++)
		{
			escape[i][j] = '#';
		}
	}

	for (int i = 0; i < user.difficulty; i++) //���� ��ǥ ����
	{
		mon[i].posX = rand() % 10;
		mon[i].posY = rand() % 10;

		if (mon[i].posX == 0 && mon[i].posY == 0) //0,0 �� ��� �ٽ� �̴´�.
			i--;
	}

	escape[user.posX][user.posY] = 'O'; //���� ��ǥ�� �÷��̾� ���

#pragma endregion

#pragma region ���Ӻ�

	while (1)
	{
		system("cls");
		cout << endl;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				cout << escape[i][j];
			}
			cout << endl;
		}
		cout << endl;

		cout << "=== ���� ü�� : " << user.hp << "  ===" << endl;
		cout << "=== ���� ��� : " << user.money << "  ===" << endl;
		cout << "=== ���� ���� : " << monsterRemain << " ===" << endl << endl;
		cout << "=== �̵��Ͻ÷��� WASD�� �̿��ϼ���" << " ===" << endl;
		for (int i = 0; i < user.difficulty; i++)
		{
			cout << "����� ���� ��ǥ " << mon[i].posX << ", " << mon[i].posY << endl;
		}

		char inputWay;
		cin >> inputWay; 

		for (int i = 0; i < 10; i++) //��ü �ʱ�ȭ   
		{
			for (int j = 0; j < 10; j++)
			{
				escape[i][j] = '#';
			}
		}

		switch (inputWay)
		{
		case 'W': case 'w':
			escape[user.posX][user.posY] = '-'; //�̵� ����
			user.posX--;
			if (user.posX < 0)
				user.posX = 0;
			break;
		case 'S': case 's':
			escape[user.posX][user.posY] = '-';
			user.posX++;
			if (user.posX > 9)
				user.posX = 9;
			break;
		case 'A': case 'a':
			escape[user.posX][user.posY] = '-';
			user.posY--;
			if (user.posY < 0)
				user.posY = 0;
			break;
		case 'D': case 'd':
			escape[user.posX][user.posY] = '-';
			user.posY++;
			if (user.posY > 9)
				user.posY = 9;
			break;
		default:
			cout << "�߸��� ���� �Է��ϼ̽��ϴ�" << endl;
			break;
		}

		escape[user.posX][user.posY] = 'O'; //�÷��̾� �̵� ��Ŵ

		for (int m = 0; m < user.difficulty; m++) //���Ϳ� �������� �Ǻ�
		{
			if (user.posX == mon[m].posX && user.posY == mon[m].posY)
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
						int gold = rand() % 101;
						cout << gold << "���� ������ϴ�!" << endl;
						user.money += gold;
						bool market;
						cout << "��� �����Ϸ��� 0�� ������ ���÷��� 1�� �����ÿ� ";
						cin >> market;
						if (market == 0)
							break;
						else
						{
							
							while (1)
							{
								system("cls");
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

								if (user.money < inputMoney && inputMoney <=40)
								{
									cout << "���� ���� �����մϴ�. �¹���." << endl;
									cout << "1���� ���";
									Sleep(1000);
									break;
								}
								else if (inputMoney == 40)
								{
									user.hp += 50;
									user.money -= 40;
									break;
								}
								else if (inputMoney == 30)
								{
									user.hp += 40;
									user.money -= 30;
									break;
								}
								else if (inputMoney == 20)
								{
									user.hp += 30;
									user.money -= 20;
									break;
								}
								else if (inputMoney == 10)
								{
									user.hp += 10;
									user.money -= 10;
									break;
								}
								else
								{
									cout << "���� ��ǰ�Դϴ�. ���� ��ȸ��..." << endl;
									cout << "1���� ���";
									Sleep(1000);
									break;
								}//if�� ��


							}//���� while ��

						}//else ��//������ ��
						break;
					} //���������� if�� ��
					else if (monsterPick - userPick == 1 || monsterPick - userPick == -2)
					{
						cout << "�й�!" << endl << endl;
						user.hp -= 40;
						if (user.hp > 0)
						{
							cout << "1���� ���";
							Sleep(1000); //ȭ�� Ŭ���� �Ǿ������ �߰�
						}
						break;
					}
					else
					{
						cout << "�����ϴ�. �ٽ� ����մϴ�" << endl << endl;
						continue;
					}
				}//���������� while�� ��
				
			}
			break;
		}
		
		if (user.hp <= 0) //�й����� 
		{
			cout << "���� ����!" << endl;
			break;
		}

		if (monsterRemain == 0) //�¸�����
		{
			cout << "���� Ŭ����!" << endl;
			break;
		}


	} //���� while��
#pragma endregion





	

	return 0;
	
}