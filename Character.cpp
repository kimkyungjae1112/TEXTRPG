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
		std::cout << "잘못된 입력" << '\n';
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
        std::cout << "뒤쪽 길 없음" << '\n';
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
        std::cout << "위에 길 없음" << '\n';
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
        std::cout << "아래 길 없음" << '\n';
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
            std::cout << '\n' << "************* 다음 맵 이동 *************" << '\n';
            std::cout << "로딩중...";
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
        std::cout << "몬스터 만났다" << '\n';
    
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
    std::cout << "보스 몬스터 만났다" << '\n';

    context->BattleInterface();
}

void Character::LevelUp(const int& InXp)
{    
    Xp += InXp;
    if ((Level * 5) <= Xp)
    {
        std::cout << "\n\n=========== 레벨업 ===========" << '\n';
        std::cout << "\tHp 증가 + 30" << '\n';
        std::cout << "\tMp 증가 + 30" << '\n';
        std::cout << "\t공경력 증가 + 10" << "\n\n";

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
	std::cout << "=========== " << Name << "의 공격 ===========" << '\n' << monster->GetName() << "의 체력 : "
		<< monster->GetHp() << '\n';
	monster->SetHp(Damage);
	std::cout << monster->GetName() << "의 남은 체력 : " << monster->GetHp() << "\n\n";

    std::cout << "=========== " << monster->GetName() << "의 공격 ===========" << '\n' << Name << "의 체력 : "
        << Hp << '\n';

    Hp -= monster->GetDamage();
    std::cout << Name << "의 남은 체력 : " << Hp;

    if (monster->GetHp() <= 0)
    {
        std::cout << "\n\n========== 몬스터 처치 완료 ==========" << '\n';

        if (monster->GetName() == "보스")
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
        std::cout << "도망 성공" << '\n';
    }
    else
    {
        std::cout << "도망 실패, 이제 도망 못감" << '\n';
        RunFlag = false;

        std::cout << "==========" << monster->GetName() << "의 공격 ==========" << '\n' << Name << "의 체력 : "
            << Hp << '\n';

        Hp -= monster->GetDamage();
        std::cout << Name << "의 남은 체력 : " << Hp;
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
    ost << "현재 좌표 ( " << character->x << ", " << character->y << " )" << '\n';
    return ost;
}