#include "Context.h"
#include "Monster.h"
#include <random>
#include <Windows.h>
using std::cout;
using std::cin;
Context* Context::context = nullptr;

Context* Context::GetContext()
{
	if (!context)
	{
		context = new Context();
	}
	return context;
}

void Context::MakeContext(Character* Player, MapManager* mapManager)
{
	this->Player = Player;
	this->mapManager = mapManager;
}

void Context::ChoiceJob()
{
	cout << "========= 직업 선택 ==========" << "\n\n";
	cout << "\t0. 초보자" << '\n'
		<< "\t1. 전사" << '\n'
		<< "\t2. 마법사" << '\n'
		<< "\t3. 궁수" << "\n\n";
	cout << "==============================" << '\n';

	CHOICE:
	cout << "선택 : ";

	int ChoiceJob;
	cin >> ChoiceJob;

	if (ChoiceJob > 0 && ChoiceJob <= 3)
	{
		Player->BaseSetCharacter(static_cast<Job>(ChoiceJob));
	}
	else
	{
		cout << "다시 ";
		goto CHOICE;
	}

	Sleep(3000);
	system("cls");
}

void Context::MoveInterface()
{
	std::cout << "******************** 인게임 ********************" << "\n\n";
	mapManager->GetMap()->EnvironmentVariable();
	std::cout << "1. 이동하기" << '\n' << "2. 저장하기" << '\n' << "3. 나가기" << '\n' << "선택 : ";

	int SecondChoice;
	std::cin >> SecondChoice;

	Sleep(700);
	system("cls");


	if (SecondChoice == 1)
	{
	BACK:
		std::cout << Player;
		std::cout << "1. 위" << '\n' << "2. 아래" << '\n' << "3. 뒤" << '\n' << "4. 앞" << '\n' << "선택 : ";
		int MoveChoice;
		std::cin >> MoveChoice;

		switch (MoveChoice)
		{
		case 1:
			Player->MoveUp(mapManager);
			break;
		case 2:
			Player->MoveDown(mapManager);
			break;
		case 3:
			Player->MoveBack(mapManager);
			break;
		case 4:
			Player->MoveForward(mapManager);
			break;
		default:
			std::cout << "이동 입력 오류" << '\n';
			goto BACK;
		}

	}
	else if(SecondChoice == 3)
	{
		ExitFlag = true;
	}

	Sleep(700);
	system("cls");

}

void Context::BattleInterface()
{
	while (1)
	{
		system("cls");

		// 플레이어 정보를 출력한다.
		cout << "====================== Player ======================" << '\n';
		cout << "이름 : " << Player->GetName() << '\n';
		cout << "레벨 : " << Player->GetLevel() << "\t 경험치 : " << Player->GetXp() << '\n'; 
		cout << "공격력 : " << Player->GetDamage() << " - ";
		cout << "체력 : " << Player->GetHp() << " / " << "\t마나 : " << Player->GetMp() << '\n';

		// 플레이어 정보를 출력한다.
		cout << "====================== Monster ======================" << '\n';
		cout << "이름 : " << Player->GetMonster()->GetName() << '\n';
		cout << "경험치 : " << Player->GetMonster()->GetXp() << '\n';
		cout << "공격력 : " << Player->GetMonster()->GetDamage() << " - ";
		cout << "체력 : " << Player->GetMonster()->GetHp() << "\n\n";

		cout << "======================== 선택 ========================" << '\n';
		cout << "1. 공격" << '\n' << "2. 방어" << '\n' << "3. 도망" << '\n';
		cout << "선택 : ";
		
		int Choice;
		cin >> Choice;

		if (Choice == 1)
		{
			Player->Attack();
		}
		else if (Choice == 2)
		{
			Player->Defend();
		}
		else if (Choice == 3)
		{
			Player->Run();
		}

		Sleep(2000);
		
		if (!Player->GetMonster()) break;
	}

}

void Context::EndingInterface()
{
	system("cls");
	cout << "============ ENDING ============" << '\n';
}

