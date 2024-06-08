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
		std::cout << "�˸��� ���� �� ����" << '\n';
		break;
	}

	if (mysql_query(conn, QueryMap.c_str()))
	{
		std::cerr << "INSERT Map ����: " << mysql_error(conn) << std::endl;
	}
	else
	{
		std::cout << "INSERT Map ����" << std::endl;
	}

}

int main()
{
	MYSQL* conn;
	MYSQL_RES* res;
	MYSQL_ROW row;

	const char* server = "127.0.0.1";
	const char* user = "root";
	const char* password = "0000"; // ����� ��й�ȣ
	const char* database = "databaseproject";

	CharacterJob* Cj = new Beginner;
	std::cout << "ĳ���� ���� : " << Cj->GetName();

	// MySQL �ʱ�ȭ
	conn = mysql_init(NULL);
	conn = mysql_real_connect(conn, server, user, password, database, 3306, NULL, 0);
	if (conn) cout << "MYSQL �ʱ�ȭ �Ϸ�" << '\n';

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
		std::cout << "******************** ���� ȭ�� ********************" << "\n\n";
		std::cout << "1. �����ϱ�" << '\n' << "2. ������" << '\n' << "���� : ";
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
		else std::cout << "�߸��� ����" << '\n';
	
		break;
	}

	//������ ���̽� ��� ����
	context->CleanupDatabase();
	
	// MySQL ���� ����
	mysql_close(conn);
	return 0;
}