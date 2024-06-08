#include "Context.h"
#include <string>
#include <random>
#include <Windows.h>
#include <mysql.h>
using std::to_string;

void InsertMap(MYSQL* conn, Region region)
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

int main()
{
	MYSQL* conn;
	MYSQL_RES* res;
	MYSQL_ROW row;

	const char* server = "127.0.0.1";
	const char* user = "root";
	const char* password = "0000"; // 사용자 비밀번호
	const char* database = "databaseproject";

	CharacterJob* Cj = new Beginner;
	std::cout << "캐릭터 직업 : " << Cj->GetName();

	// MySQL 초기화
	conn = mysql_init(NULL);
	conn = mysql_real_connect(conn, server, user, password, database, 3306, NULL, 0);
	if (conn) cout << "MYSQL 초기화 완료" << '\n';

	Character* Player = new Character;

	MapManager* Manager = new MapManager;
	Manager->AddMap(Region::GROUND);
	if (conn) InsertMap(conn, Region::GROUND);

	Manager->AddMap(Region::FROZEN);
	if (conn) InsertMap(conn, Region::FROZEN);

	Manager->AddMap(Region::VOLCANO);
	if (conn) InsertMap(conn, Region::VOLCANO);
	
	Context* context = Context::GetContext();
	context->MakeContext(Player, Manager, conn);
	context->ChoiceJob();
	

	while (1)
	{	 
		MAIN:
		std::cout << "******************** 메인 화면 ********************" << "\n\n";
		std::cout << "1. 모험하기" << '\n' << "2. 떠나기" << '\n' << "선택 : ";
		int FirstChoice;
		std::cin >> FirstChoice;
		system("cls");

		if (FirstChoice == 1)
		{
			while (1)
			{
				context->InGameInterface();
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
		else std::cout << "잘못된 선택" << '\n';
	
		break;
	}

	//데이터 베이스 모두 삭제
	context->CleanupDatabase();
	
	// MySQL 연결 종료
	mysql_close(conn);
	return 0;
}