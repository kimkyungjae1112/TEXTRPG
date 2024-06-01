#include "Context.h"
#include <random>
#include <Windows.h>

int main()
{
	Character* Player = new Character;

	MapManager* Manager = new MapManager;
	Manager->AddMap(Region::GROUND);
	Manager->AddMap(Region::FROZEN);
	Manager->AddMap(Region::VOLCANO);

	Context* context = Context::GetContext();
	context->MakeContext(Player, Manager);
	context->ChoiceJob();
	
	while (1)
	{	
		MAIN:
		std::cout << "******************** ���� ȭ�� ********************" << "\n\n";
		std::cout << "1. �����ϱ�" << '\n' << "2. ������" << '\n' << "���� : ";
		int FirstChoice;
		std::cin >> FirstChoice;
		system("cls");

		if (FirstChoice == 1)
		{
			while (1)
			{
				context->MoveInterface();
				if (context->EndingFlag)
				{
					context->EndingInterface();
				}

				if (context->ExitFlag)
				{
					goto MAIN;
				}
			}
		}
		else if (FirstChoice == 2) break;
		else std::cout << "�߸��� ����" << '\n';
	
		break;
	}

	return 0;
}

