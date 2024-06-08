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

    virtual void InsertDatabase() {}
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
    void InsertDatabase()
    {
        Name = "Beginner";
        Hp = 100;
        Mp = 50;
        Damage = 10;
    }

    void BaseSetCharacter(Job job) override
    {
        Name = "Beginner";
        Hp = 100;
        Mp = 50;
        Damage = 10;

        cout << "========= �ʺ��� ���� ==========" << "\n\n";
        cout << "ü�� : " << Hp << '\n'
            << "���� : " << Mp << '\n'
            << "���ݷ� : " << Damage << "\n\n";
        cout << "==============================" << '\n';
    }
};

class Warrior : public CharacterJob
{
public:
    void InsertDatabase() 
    {
        Name = "Warrior";
        Hp = 200;
        Mp = 30;
        Damage = 20;
    }

    void BaseSetCharacter(Job job) override
    {
        Name = "Warrior";
        Hp = 200;
        Mp = 30;
        Damage = 20;

        cout << "========= ���� ���� ==========" << "\n\n";
        cout << "\tü�� : " << Hp << '\n'
            << "\t���� : " << Mp << '\n'
            << "\t���ݷ� : " << Damage << "\n\n";
        cout << "==============================" << '\n';
    }
};

class Wizard : public CharacterJob
{
public:
    void InsertDatabase()
    {
        Name = "Wizard";
        Hp = 80;
        Mp = 150;
        Damage = 100;
    }


    void BaseSetCharacter(Job job) override
    {
        Name = "Wizard";
        Hp = 80;
        Mp = 150;
        Damage = 100;

        cout << "========= ������ ���� =========" << "\n\n";
        cout << "\tü�� : " << Hp << '\n'
            << "\t���� : " << Mp << '\n'
            << "\t���ݷ� : " << Damage << "\n\n";
        cout << "==============================" << '\n';
    }
};

class Archer : public CharacterJob
{
public:
    void InsertDatabase()
    {
        Name = "Archer";
        Hp = 120;
        Mp = 60;
        Damage = 50;
    }

    void BaseSetCharacter(Job job) override
    {
        Name = "Archer";
        Hp = 120;
        Mp = 60;
        Damage = 50;

        cout << "========= �ʺ��� ���� ==========" << "\n\n";
        cout << "\tü�� : " << Hp << '\n'
            << "\t���� : " << Mp << '\n'
            << "\t���ݷ� : " << Damage << "\n\n";
        cout << "==============================" << '\n';
    }
};

#endif //__CHARACTERJOB_H__