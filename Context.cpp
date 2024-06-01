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
	cout << "========= ���� ���� ==========" << "\n\n";
	cout << "\t0. �ʺ���" << '\n'
		<< "\t1. ����" << '\n'
		<< "\t2. ������" << '\n'
		<< "\t3. �ü�" << "\n\n";
	cout << "==============================" << '\n';

	CHOICE:
	cout << "���� : ";

	int ChoiceJob;
	cin >> ChoiceJob;

	if (ChoiceJob > 0 && ChoiceJob <= 3)
	{
		Player->BaseSetCharacter(static_cast<Job>(ChoiceJob));
	}
	else
	{
		cout << "�ٽ� ";
		goto CHOICE;
	}

	Sleep(3000);
	system("cls");
}

void Context::MoveInterface()
{
	std::cout << "******************** �ΰ��� ********************" << "\n\n";
	mapManager->GetMap()->EnvironmentVariable();
	std::cout << "1. �̵��ϱ�" << '\n' << "2. �����ϱ�" << '\n' << "3. ������" << '\n' << "���� : ";

	int SecondChoice;
	std::cin >> SecondChoice;

	Sleep(700);
	system("cls");


	if (SecondChoice == 1)
	{
	BACK:
		std::cout << Player;
		std::cout << "1. ��" << '\n' << "2. �Ʒ�" << '\n' << "3. ��" << '\n' << "4. ��" << '\n' << "���� : ";
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
			std::cout << "�̵� �Է� ����" << '\n';
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

		// �÷��̾� ������ ����Ѵ�.
		cout << "====================== Player ======================" << '\n';
		cout << "�̸� : " << Player->GetName() << '\n';
		cout << "���� : " << Player->GetLevel() << "\t ����ġ : " << Player->GetXp() << '\n'; 
		cout << "���ݷ� : " << Player->GetDamage() << " - ";
		cout << "ü�� : " << Player->GetHp() << " / " << "\t���� : " << Player->GetMp() << '\n';

		// �÷��̾� ������ ����Ѵ�.
		cout << "====================== Monster ======================" << '\n';
		cout << "�̸� : " << Player->GetMonster()->GetName() << '\n';
		cout << "����ġ : " << Player->GetMonster()->GetXp() << '\n';
		cout << "���ݷ� : " << Player->GetMonster()->GetDamage() << " - ";
		cout << "ü�� : " << Player->GetMonster()->GetHp() << "\n\n";

		cout << "======================== ���� ========================" << '\n';
		cout << "1. ����" << '\n' << "2. ���" << '\n' << "3. ����" << '\n';
		cout << "���� : ";
		
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

