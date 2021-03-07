#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <windows.h>
using namespace std;


//상점 분리
//초월 체력 문제 정리
//몬스터 중복 뽑기 문제
//몬스터 죽이기

struct Hero
{
	int hp = 100;
	string name;
	int posX = 0; 
	int posY = 0;
	int difficulty = 0; //게임 데이터 구조체로 분류해야 한다.
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

	//이름 입력부
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
		cin >> user.difficulty;
		user.hp = 100 - user.difficulty * 2;
		monsterRemain = user.difficulty; //난이도 수에 따라 몬스터 설정

		char modify;
		cout << endl << "입력하신 난이도는 " << user.difficulty << endl;

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

	char escape[10][10];

	for (int i = 0; i < 10; i++) //전체 초기화   
	{
		for (int j = 0; j < 10; j++)
		{
			escape[i][j] = '#';
		}
	}

	for (int i = 0; i < user.difficulty; i++) //몬스터 좌표 설정
	{
		mon[i].posX = rand() % 10;
		mon[i].posY = rand() % 10;

		if (mon[i].posX == 0 && mon[i].posY == 0) //0,0 일 경우 다시 뽑는다.
			i--;
	}

	escape[user.posX][user.posY] = 'O'; //시작 좌표에 플레이어 출력

#pragma endregion

#pragma region 게임부

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

		cout << "=== 현재 체력 : " << user.hp << "  ===" << endl;
		cout << "=== 현재 골드 : " << user.money << "  ===" << endl;
		cout << "=== 남은 몬스터 : " << monsterRemain << " ===" << endl << endl;
		cout << "=== 이동하시려면 WASD를 이용하세요" << " ===" << endl;
		for (int i = 0; i < user.difficulty; i++)
		{
			cout << "참고용 몬스터 좌표 " << mon[i].posX << ", " << mon[i].posY << endl;
		}

		char inputWay;
		cin >> inputWay; 

		for (int i = 0; i < 10; i++) //전체 초기화   
		{
			for (int j = 0; j < 10; j++)
			{
				escape[i][j] = '#';
			}
		}

		switch (inputWay)
		{
		case 'W': case 'w':
			escape[user.posX][user.posY] = '-'; //이동 연출
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
			cout << "잘못된 값을 입력하셨습니다" << endl;
			break;
		}

		escape[user.posX][user.posY] = 'O'; //플레이어 이동 시킴

		for (int m = 0; m < user.difficulty; m++) //몬스터와 만났는지 판별
		{
			if (user.posX == mon[m].posX && user.posY == mon[m].posY)
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
						int gold = rand() % 101;
						cout << gold << "원을 얻었습니다!" << endl;
						user.money += gold;
						bool market;
						cout << "계속 진행하려면 0을 상점에 가시려면 1을 누르시오 ";
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

								if (user.money < inputMoney && inputMoney <=40)
								{
									cout << "가진 돈이 부족합니다. 굿바이." << endl;
									cout << "1초후 계속";
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
									cout << "없는 상품입니다. 다음 기회에..." << endl;
									cout << "1초후 계속";
									Sleep(1000);
									break;
								}//if문 끝


							}//상점 while 끝

						}//else 끝//상점부 끝
						break;
					} //가위바위보 if문 끝
					else if (monsterPick - userPick == 1 || monsterPick - userPick == -2)
					{
						cout << "패배!" << endl << endl;
						user.hp -= 40;
						if (user.hp > 0)
						{
							cout << "1초후 계속";
							Sleep(1000); //화면 클리어 되어버려서 추가
						}
						break;
					}
					else
					{
						cout << "비겼습니다. 다시 대결합니다" << endl << endl;
						continue;
					}
				}//가위바위보 while문 끝
				
			}
			break;
		}
		
		if (user.hp <= 0) //패배조건 
		{
			cout << "게임 오버!" << endl;
			break;
		}

		if (monsterRemain == 0) //승리조건
		{
			cout << "게임 클리어!" << endl;
			break;
		}


	} //게임 while문
#pragma endregion





	

	return 0;
	
}