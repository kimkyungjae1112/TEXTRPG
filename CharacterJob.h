#pragma once
#ifndef __CHARACTERJOB_H__
#define __CHARACTERJOB_H__
using std::cout;
class CharacterJob : public CharacterBase
{
public:
	CharacterJob() : Name(""), Hp(0), Mp(0), Damage(0) {}
	virtual void BaseSetCharacter(Job job) override = 0;

    std::string GetName() const { return Name; }
	int GetHp() const { return Hp; }
	int GetMp() const { return Mp; }
	int GetDamage() const { return Damage; }

	virtual ~CharacterJob() {}

protected:
	std::string Name;
	int Hp;
	int Mp;
	int Damage;
};

class Beginner : public CharacterJob
{
public:
    void BaseSetCharacter(Job job) override
    {
        Name = "초보자";
        Hp = 100;
        Mp = 50;
        Damage = 10;

        cout << "========= 초보자 스텟 ==========" << "\n\n";
        cout << "체력 : " << Hp << '\n'
            << "마나 : " << Mp << '\n'
            << "공격력 : " << Damage << "\n\n";
        cout << "==============================" << '\n';
    }
};

class Warrior : public CharacterJob
{
public:
    void BaseSetCharacter(Job job) override
    {
        Name = "전사";
        Hp = 200;
        Mp = 30;
        Damage = 20;

        cout << "========= 전사 스텟 ==========" << "\n\n";
        cout << "\t체력 : " << Hp << '\n'
            << "\t마나 : " << Mp << '\n'
            << "\t공격력 : " << Damage << "\n\n";
        cout << "==============================" << '\n';
    }
};

class Wizard : public CharacterJob
{
public:
    void BaseSetCharacter(Job job) override
    {
        Name = "마법사";
        Hp = 80;
        Mp = 150;
        Damage = 100;

        cout << "========= 마법사 스텟 ==========" << "\n\n";
        cout << "\t체력 : " << Hp << '\n'
            << "\t마나 : " << Mp << '\n'
            << "\t공격력 : " << Damage << "\n\n";
        cout << "==============================" << '\n';
    }
};

class Archer : public CharacterJob
{
public:
    void BaseSetCharacter(Job job) override
    {
        Name = "궁수";
        Hp = 120;
        Mp = 60;
        Damage = 50;

        cout << "========= 초보자 스텟 ==========" << "\n\n";
        cout << "\t체력 : " << Hp << '\n'
            << "\t마나 : " << Mp << '\n'
            << "\t공격력 : " << Damage << "\n\n";
        cout << "==============================" << '\n';
    }
};

#endif //__CHARACTERJOB_H__