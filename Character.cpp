#include "Character.h"
#include "Monster.h"
#include "Context.h"
#include <random>
#include <Windows.h>


Character::Character() : 
    Name(""), Hp(0), MaxHp(0), Mp(0), Damage(0), RunFlag(true), Level(1), Xp(0), CurrentJob(nullptr)
{
    srand(unsigned int(time(NULL)));
}

void Character::BaseSetCharacter(Job job)
{
	switch (job)
	{
	case Job::Beginner:
		CurrentJob = std::make_unique<Beginner>();
		break;
	case Job::Warrior:
		CurrentJob = std::make_unique<Warrior>();
		break;
	case Job::Wizard:
		CurrentJob = std::make_unique<Wizard>();
		break;
	case Job::Archer:
		CurrentJob = std::make_unique<Archer>();
		break;
	default:
		std::cout << "�߸��� �Է�" << '\n';
		return;

	}

    CurrentJob->BaseSetCharacter(job);
    Name = CurrentJob->GetName();
    Hp = CurrentJob->GetHp();
    MaxHp = Hp;
    Mp = CurrentJob->GetMp();
    Damage = CurrentJob->GetDamage();
}

void Character::MoveForward(MapManager* mapManager)
{
    x += 1;
    CheckAndMoveToNextMap(mapManager);
    MeetMonster();
}

void Character::MoveBack(MapManager* mapManager)
{
    if (x <= 0)
    {
        std::cout << "���� �� ����" << '\n';
        Sleep(500);
        return;
    }
    x -= 1;
    MeetMonster();
}

void Character::MoveUp(MapManager* mapManager)
{
    if (y >= MaxHeight)
    {
        std::cout << "���� �� ����" << '\n';
        Sleep(500);
        return;
    }
    y += 1;
    MeetMonster();
}

void Character::MoveDown(MapManager* mapManager)
{
    if (y <= 0)
    {
        std::cout << "�Ʒ� �� ����" << '\n';
        Sleep(500);
        return;
    }
    y -= 1;
    MeetMonster();
}

void Character::CheckAndMoveToNextMap(MapManager* mapManager)
{
    if (x >= MaxWidth)
    {
        currentMapIndex++;
        mapManager->SetMapIndex(currentMapIndex);
        Map* nextMap = mapManager->GetMap();
        if (nextMap)
        {
            x = 0;
            y = 0;
            std::cout << '\n' << "************* ���� �� �̵� *************" << '\n';
            std::cout << "�ε���...";
            Sleep(2000);
        }
        else
        {
            MeetBoss();
        }
    }
}

void Character::MeetMonster()
{
    int MeetRatio = rand() % 3;
    int Type = rand() % 6;
    if (MeetRatio == 0)
    {
        RunFlag = true;
        monster = new Monster();
        if(Type >= 0 || Type <= 3) monster->BaseSetMonster(MType::GOBLIN);
        else if(Type >= 4 || Type <= 5)monster->BaseSetMonster(MType::OAK);
        DetectedMonster(monster);

        Context* context = Context::GetContext();
        std::cout << "���� ������" << '\n';
    
        context->BattleInterface();
    }
}

void Character::MeetBoss()
{
    RunFlag = true;
    monster = new Monster();
    monster->BaseSetMonster(MType::BOSS);
    DetectedMonster(monster);

    Context* context = Context::GetContext();
    std::cout << "���� ���� ������" << '\n';

    context->BattleInterface();
}

void Character::LevelUp(const int& InXp)
{    
    Xp += InXp;
    if ((Level * 5) <= Xp)
    {
        std::cout << "\n\n=========== ������ ===========" << '\n';
        std::cout << "\tHp ���� + 30" << '\n';
        std::cout << "\tMp ���� + 30" << '\n';
        std::cout << "\t����� ���� + 10" << "\n\n";

        Level++;
        Xp = 0;

        Hp = MaxHp + 30;
        Mp = Mp + 30;
        Damage = Damage + 10;
        Sleep(2000);
    }
}

void Character::Attack()
{
	std::cout << "=========== " << Name << "�� ���� ===========" << '\n' << monster->GetName() << "�� ü�� : "
		<< monster->GetHp() << '\n';
	monster->SetHp(Damage);
	std::cout << monster->GetName() << "�� ���� ü�� : " << monster->GetHp() << "\n\n";

    std::cout << "=========== " << monster->GetName() << "�� ���� ===========" << '\n' << Name << "�� ü�� : "
        << Hp << '\n';

    Hp -= monster->GetDamage();
    std::cout << Name << "�� ���� ü�� : " << Hp;

    if (monster->GetHp() <= 0)
    {
        std::cout << "\n\n========== ���� óġ �Ϸ� ==========" << '\n';

        if (monster->GetName() == "����")
        {
            Context* context = Context::GetContext();
            context->EndingFlag = true;
        }

        LevelUp(monster->GetXp());

        delete monster;
        monster = nullptr;
    }
}

void Character::Defend()
{
	std::cout << "Defend System" << '\n';
}

void Character::Run()
{
    int RunRatio = rand() % 3;
    if (RunRatio == 0 && RunFlag)
    {
        delete monster;
        monster = nullptr;
        std::cout << "���� ����" << '\n';
    }
    else
    {
        std::cout << "���� ����, ���� ���� ����" << '\n';
        RunFlag = false;

        std::cout << "==========" << monster->GetName() << "�� ���� ==========" << '\n' << Name << "�� ü�� : "
            << Hp << '\n';

        Hp -= monster->GetDamage();
        std::cout << Name << "�� ���� ü�� : " << Hp;
    }
}

void Character::DetectedMonster(Monster* InMonster)
{
	monster = InMonster;
}

Character::~Character()
{
}

std::ostream& operator<<(std::ostream& ost, Character* character)
{
    ost << "���� ��ǥ ( " << character->x << ", " << character->y << " )" << '\n';
    return ost;
}