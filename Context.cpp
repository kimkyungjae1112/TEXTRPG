#include "Context.h"
#include "Monster.h"
#include "MonsterType.h"
#include <random>
#include <Windows.h>
#include <mysql.h>
#include <string>
#include <typeinfo>
using std::to_string;
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

void Context::MakeContext(Character* Player, MapManager* mapManager, MYSQL* conn)
{
	this->Player = Player;
	this->mapManager = mapManager;
	this->conn = conn;

	mapManager->AddMap(Region::GROUND);
	InsertMap(Region::GROUND);

	mapManager->AddMap(Region::FROZEN);
	if (conn) InsertMap(Region::FROZEN);

	mapManager->AddMap(Region::VOLCANO);
	if (conn) InsertMap(Region::VOLCANO);

	InsertJob(new Beginner);
	InsertJob(new Warrior);
	InsertJob(new Wizard);
	InsertJob(new Archer);
	InsertMonster(new Goblin);
	InsertMonster(new Oak);
	InsertMonster(new Boss);
	InsertMapManager();
	InsertManage();
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

	cout << "캐릭터 닉네임 설정 : ";
	std::string name;
	cin >> name;
	cout << '\n';
	Player->SetName(name);

	if (ChoiceJob >= 0 && ChoiceJob <= 3)
	{
		Player->BaseSetCharacter(static_cast<Job>(ChoiceJob));
		
	}
	else
	{
		cout << "다시 ";
		goto CHOICE;
	}

	InsertPlayerXp();	// PlayerXp 데이터 삽입
	InsertPlayer();  // Player 데이터 삽입
	InsertPlayerStat(); // PlayerStat 데이터 삽입


	Sleep(3000);
	system("cls");
}

void Context::InGameInterface()
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
	else if (SecondChoice == 2)
	{
		std::cout << "저장중...";
		InsertPlayer();
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
		cout << "공격력 : " << Player->GetDamage() << '\n';
		cout << "체력 : " << Player->GetHp() << " / " << "\t마나 : " << Player->GetMp() << '\n';

		// 플레이어 정보를 출력한다.
		cout << "====================== Monster ======================" << '\n';
		cout << "이름 : " << Player->GetMonster()->GetName() << '\n';
		cout << "경험치 : " << Player->GetMonster()->GetXp() << '\n';
		cout << "공격력 : " << Player->GetMonster()->GetDamage() << '\n';
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

		InsertBattle(Choice);

		Sleep(2000);
		
		if (!Player->GetMonster()) break;
	}
}

void Context::EndingInterface()
{
	system("cls");
	cout << "============ ENDING ============" << '\n';
}

void Context::InsertPlayerStat()
{
	std::string QueryStat = "INSERT INTO playerstat(Hp, Mp, Damage, PlayerXp_Level) VALUES ("
		+ to_string(Player->GetHp()) + ", " + to_string(Player->GetMp()) + ", " + to_string(Player->GetDamage()) + ", " + to_string(Player->GetLevel()) + ")";

	if (mysql_query(conn, QueryStat.c_str()))
	{
		std::cerr << "INSERT Stat 실패: " << mysql_error(conn) << std::endl;
	}
	else
	{
		std::cout << "INSERT Stat 성공" << std::endl;
	}
}

void Context::InsertPlayerXp()
{
	std::string QueryXp = "INSERT INTO playerxp(Xp, Level) VALUES (" + to_string(Player->GetXp()) + ", " + to_string(Player->GetLevel()) + ")";

	if (mysql_query(conn, QueryXp.c_str()))
	{
		std::cerr << "INSERT Xp 실패: " << mysql_error(conn) << std::endl;
	}
	else
	{
		std::cout << "INSERT Xp 성공" << std::endl;
	}
}

void Context::InsertPlayer()
{
	std::string name = Player->GetName();
	int xp = Player->GetXp();
	int level = Player->GetLevel();
	std::string jobName = Player->GetJobName();
	int mapManagerId = mapManager->GetMapIndex();

	std::string query = "INSERT INTO player (id, X, Y, Name, PlayerXp_Xp, PlayerXp_Level, Job_JobName, MapManager_MapIndex) VALUES (" +
		to_string(PlayerId) + ", " +
		to_string(Player->GetX()) + ", " +
		to_string(Player->GetY()) + ", '" +
		name + "', " +
		to_string(xp) + ", " +
		to_string(level) + ", '" +
		jobName + "', " +
		to_string(mapManagerId) + ")";

	if (mysql_query(conn, query.c_str()))
	{
		std::cerr << "INSERT Player 실패: " << mysql_error(conn) << std::endl;
	}
	else
	{
		cout << "INSERT Player 성공" << std::endl;
		PlayerId++;
	}
}

void Context::InsertMonster(MonsterType* Mt)
{
	std::string QueryMonster = "";
	Mt->InsertDatabase();

	QueryMonster = "INSERT INTO monster(MonName, Hp, Damage, Xp) VALUES ('" + Mt->GetName() + "' ," + to_string(Mt->GetHp()) + ", " + to_string(Mt->GetDamage()) + ", " + to_string(Mt->GetXp()) + ")";

	if (mysql_query(conn, QueryMonster.c_str()))
	{
		std::cerr << "INSERT Monster 실패: " << mysql_error(conn) << '\n';
	}
	else
	{
		cout << "INSERT Monster 성공" << '\n';
	}

}

void Context::InsertJob(CharacterJob* Cj)
{
	std::string QueryJob = "";
	Cj->InsertDatabase();
	QueryJob = "INSERT INTO job(JobName) VALUES ('" + Cj->GetName() + "'" + ")";
	
	if (mysql_query(conn, QueryJob.c_str()))
	{
		std::cerr << "INSERT Job 실패: " << mysql_error(conn) << '\n';
	}
	else
	{
		cout << "INSERT Job 성공" << '\n';
	}
}

void Context::InsertBattle(const int RunFlag)
{
	Monster* monster = Player->GetMonster();
	if (monster)
	{
		std::string Query = "INSERT INTO battle (BattleLog ,Run, Monster_MonName, Player_id) VALUES ('" +
			to_string(BattleLog) + "', '" +
			"No" + "', '" +
			monster->GetName() + "', " +
			to_string(PlayerId - 1) + ")";

		if (mysql_query(conn, Query.c_str()))
		{
			std::cerr << "INSERT Battle 실패: " << mysql_error(conn) << std::endl;
		}
		else
		{
			std::cout << "INSERT Battle 성공" << std::endl;
		}

		if (RunFlag == 3 && Player->GetRunFlag())
		{
			std::string UpdateQuery = "UPDATE battle SET Run = 'Yes' WHERE BattleLog = " + to_string(BattleLog);
			if (mysql_query(conn, UpdateQuery.c_str()))
			{
				std::cerr << "INSERT Battle Update 실패: " << mysql_error(conn) << std::endl;
			}
		}
		BattleLog++;
	}
	
}
void Context::InsertMapManager()
{
	std::string Query = "INSERT INTO mapmanager (MapIndex, MapEa) VALUES (" +
		to_string(mapManager->GetMapIndex()) + ", " +
		to_string(mapManager->GetMapSize()) + ")";

	if (mysql_query(conn, Query.c_str()))
	{
		std::cerr << "INSERT MapManager 실패: " << mysql_error(conn) << std::endl;
	}
	else
	{
		std::cout << "INSERT MapManager 성공" << std::endl;
	}
}

void Context::InsertManage()
{
	std::string Query = "INSERT INTO manage (MapManager_MapIndex, Map_MapName) VALUES (" +
		to_string(mapManager->GetMapIndex()) + ", '" +
		mapManager->GetMap()->GetMapName() + "')";

	if (mysql_query(conn, Query.c_str()))
	{
		std::cerr << "INSERT Manage 실패: " << mysql_error(conn) << std::endl;
	}
	else
	{
		std::cout << "INSERT Manage 성공" << std::endl;
	}
}

void Context::InsertMap(Region region)
{
	std::string QueryMap = "";
	switch (region)
	{
	case Region::GROUND:
		QueryMap = "INSERT INTO Map(MapName, MapAttribute) VALUES ('GROUND', 'gr')";
		break;
	case Region::FROZEN:
		QueryMap = "INSERT INTO Map(MapName, MapAttribute) VALUES ('FROZEN', 'fro')";
		break;
	case Region::VOLCANO:
		QueryMap = "INSERT INTO Map(MapName, MapAttribute) VALUES ('VOLCANO', 'vol')";
		break;
	default:
		std::cout << "알맞지 않은 맵 삽입" << '\n';
		break;
	}

	if (mysql_query(conn, QueryMap.c_str()))
	{
		std::cerr << "INSERT Map 실패: " << mysql_error(conn) << std::endl;
	}
	else
	{
		std::cout << "INSERT Map 성공" << std::endl;
	}
}

void Context::CleanupDatabase()
{
	std::string DeleteBattleQuery = "DELETE FROM battle";
	std::string DeleteManageQuery = "DELETE FROM manage";
	std::string DeletePlayerStatQuery = "DELETE FROM playerstat";
	std::string DeletePlayerQuery = "DELETE FROM player";
	std::string DeletePlayerXpQuery = "DELETE FROM playerxp";
	std::string DeleteMonsterQuery = "DELETE FROM monster";
	std::string DeleteJobQuery = "DELETE FROM job";
	std::string DeleteMapQuery = "DELETE FROM map";
	std::string DeleteMapManagerQuery = "DELETE FROM mapmanager";

	if (mysql_query(conn, DeleteBattleQuery.c_str()))
	{
		std::cerr << "DELETE battle 실패: " << mysql_error(conn) << std::endl;
	}
	else
	{
		std::cout << "DELETE battle 성공" << std::endl;
	}

	if (mysql_query(conn, DeleteManageQuery.c_str()))
	{
		std::cerr << "DELETE manage 실패: " << mysql_error(conn) << std::endl;
	}
	else
	{
		std::cout << "DELETE manage 성공" << std::endl;
	}

	if (mysql_query(conn, DeletePlayerStatQuery.c_str()))
	{
		std::cerr << "DELETE playerstat 실패: " << mysql_error(conn) << std::endl;
	}
	else
	{
		std::cout << "DELETE playerstat 성공" << std::endl;
	}

	if (mysql_query(conn, DeletePlayerQuery.c_str()))
	{
		std::cerr << "DELETE player 실패: " << mysql_error(conn) << std::endl;
	}
	else
	{
		std::cout << "DELETE player 성공" << std::endl;
	}

	if (mysql_query(conn, DeletePlayerXpQuery.c_str()))
	{
		std::cerr << "DELETE playerxp 실패: " << mysql_error(conn) << std::endl;
	}
	else
	{
		std::cout << "DELETE playerxp 성공" << std::endl;
	}

	if (mysql_query(conn, DeleteMonsterQuery.c_str()))
	{
		std::cerr << "DELETE monster 실패: " << mysql_error(conn) << std::endl;
	}
	else
	{
		std::cout << "DELETE monster 성공" << std::endl;
	}

	if (mysql_query(conn, DeleteJobQuery.c_str()))
	{
		std::cerr << "DELETE job 실패: " << mysql_error(conn) << std::endl;
	}
	else
	{
		std::cout << "DELETE job 성공" << std::endl;
	}

	if (mysql_query(conn, DeleteMapQuery.c_str()))
	{
		std::cerr << "DELETE map 실패: " << mysql_error(conn) << std::endl;
	}
	else
	{
		std::cout << "DELETE map 성공" << std::endl;
	}

	if (mysql_query(conn, DeleteMapManagerQuery.c_str()))
	{
		std::cerr << "DELETE mapmanager 실패: " << mysql_error(conn) << std::endl;
	}
	else
	{
		std::cout << "DELETE mapmanager 성공" << std::endl;
	}
}
