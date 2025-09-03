# TEXT RPG
- MySQL 데이터베이스를 통한 저장 기능이 추가된 TEXT RPG 게임입니다.

<br>

# 개요

<img width="402" height="197" alt="image (3) (1)" src="https://github.com/user-attachments/assets/3c02eb77-2800-4ac9-8701-fce510e959f1" />


전남대학교 데이터베이스 시스템 수업 중 DBMS 구축 과제를 받아 C++로 직접 TEXT 게임을 제작해보았습니다. TEXT 게임에서 나온 데이터를 제가 만든 DBMS에 저장하고 게임을 껐다 켰을 때 불러오기 기능 구현을 목표로 DBMS와 게임을 설계 했습니다.

<br>

구동 환경

- Visual Studio 2022
- MySQL server 8.0.36

개발 내용

- TEXT RPG
- DBMS

<br>

### 게임 소개
데이터베이스를 설계하기 전 설계한 데이터베이스를 사용할 수 있는 실제 프로그램이 있는게 설계가 제대로 되었는지 판단하기 쉽다고 생각했습니다. 그래서 설계를 마친 후 C++를 사용해 간단한 TEXT RPG 게임을 제작했습니다.

<br>

게임은 단순히 마지막 보스를 처치하면 이기는 게임입니다. 플레이어는 x( 0 ~ 10 ), y( 0 ~ 10 ) 좌표공간을 이동하며 몬스터를 처치 혹은 도망가며 성장할 수 있고 플레이어의 x 좌표가 10에 도달하게 되면 다음 맵으로 넘어갑니다. 마지막 맵에 도달해 x 좌표가 10에 도달하게 되면 보스 몬스터를 만나며 처치 시 게임을 클리어 할 수 있습니다.

<br>

<img width="328" height="132" alt="image" src="https://github.com/user-attachments/assets/f7ee92ee-decb-4da5-b6fd-29c9a4e31091" />


C++과 MySQL을 연동하여 게임이 진행될 때 저장되어야 할 데이터를 데이터베이스에 저장할 수 있도록 코드를 작성했습니다. 

<br>

### 플레이 영상

[플레이영상.mp4](https://prod-files-secure.s3.us-west-2.amazonaws.com/7ebf7000-f855-492a-973c-2e002d905ac7/d4993394-2156-4b82-896b-6e9b0919afad/%ED%94%8C%EB%A0%88%EC%9D%B4%EC%98%81%EC%83%81.mp4)

<br>

# DBMS

DBMS를 구축하기 위해 MySQL Workbench를 사용했습니다. 

<img width="473" height="380" alt="image" src="https://github.com/user-attachments/assets/bd4f3424-99bb-4098-8137-32268e757b66" />


MySQL Workbench에서 ER 다이어그램을 만들면 MySQL 코드로 바꿔주는 도구를 사용해 구축할 수 있었습니다. 게임을 진행하며 데이터베이스에 데이터가 쌓이는 것을 확인할 수 있습니다.

<br>

### 1. 게임 시작시

<img width="226" height="252" alt="image" src="https://github.com/user-attachments/assets/bd325b03-49ba-4a06-b956-582b69f88abf" />


게임 시작시 Map, Job, Monster,MapManager, Manage 테이블 등에 기본 데이터가 들어가게 됩니다.

<br>

<img width="608" height="298" alt="image (5)" src="https://github.com/user-attachments/assets/98805c3a-9caf-41a8-a78a-2e13bbcba7bf" />

MySQL 서버에 데이터가 삽입된 모습

<br>

### 2. 직업 선택시

<img width="237" height="241" alt="image" src="https://github.com/user-attachments/assets/85717b23-7a02-4aa0-9e85-d9454e0e4b38" />

직업 선택시 PlayerXp, Player, PlayerStat 테이블 등에 기본 데이터가 들어가게 됩니다.

<br>

<img width="616" height="205" alt="image (6)" src="https://github.com/user-attachments/assets/1555429a-fbe2-4a55-85d2-6578f26796b0" />

MySQL 서버에 데이터가 삽입된 모습

<br>

### 3. 전투 상황

<img width="495" height="458" alt="image (8)" src="https://github.com/user-attachments/assets/8de8c8cc-33db-43f7-8961-7c061d662e90" />

몬스터와 마주쳐 전투 상황시 Battle 테이블에 전투 기록이 남게됩니다.

<br>

<img width="336" height="90" alt="image (7)" src="https://github.com/user-attachments/assets/302995dc-9118-48f1-903f-8fcfb1d17092" />

MySQL 서버에 데이터가 삽입된 모습

<br>

### 4. 몬스터 처치시

<img width="418" height="218" alt="image (10)" src="https://github.com/user-attachments/assets/838be540-bd24-4463-b759-a98bd9afc055" />

몬스터 처치시 Xp가 오르게 되며 일정 수준 오르면 레벨업을 하게 됩니다. 따라서 몬스터를 처치하거나 레벨업시 PlayerStat 테이블과 PlayerXp 테이블에 데이터가 저장됩니다.

<br>

<img width="520" height="147" alt="image (9)" src="https://github.com/user-attachments/assets/4380c94a-b924-4d65-a887-9ec3a1caf0ca" />

MySQL 서버에 데이터가 삽입된 모습

<br>

### 5. 맵 이동시

<img width="430" height="119" alt="image (5)" src="https://github.com/user-attachments/assets/d6c22ca9-9cff-431b-a63f-2fc027f33892" />

맵 이동시 MapManager, Manager 테이블에 추가 데이터가 입력됩니다.

<br>

<img width="533" height="130" alt="image (6)" src="https://github.com/user-attachments/assets/67273a76-9fe7-45ae-a04a-a1b20a9aecb8" />

MySQL 서버에 데이터가 삽입된 모습

<br>

### 6. 저장시

<img width="313" height="104" alt="image (7)" src="https://github.com/user-attachments/assets/3fe2ccdb-6b99-4cac-a070-03741c3c8ac7" />

저장시 Player 테이블에 현재 플레이어의 상태를 저장합니다. 플레이어의 상태에는 현재 좌표와 캐릭터 이름, 현재 레벨과 경험치, 직업, 맵의 위치 정보가 있습니다.

<br>

<img width="636" height="186" alt="image (8)" src="https://github.com/user-attachments/assets/4146c075-ba58-4762-a880-41bb448d42c0" />

MySQL 서버에 데이터가 삽입된 모습

<br>

### 7. 클리어 및 종료시

<img width="237" height="183" alt="image" src="https://github.com/user-attachments/assets/3c97b3ac-14ab-4ee7-ac85-325463537ce1" />

클리어 및 종료시 모든 테이블에 있는 데이터가 삭제되며 프로그램이 종료됩니다.

<br>

# 구현 기술

### 클래스 구조

<img width="1673" height="650" alt="image (9)" src="https://github.com/user-attachments/assets/9ac998fc-f9e2-4499-98f1-1f366553e10e" />

<br>

### 디자인 패턴

- 파사드 패턴
    - 파사드 패턴은 일련의 저수준 인터페이스들을 하나의 고수준 인터페이스로 묶어주는 패턴이다.
    - 파사드 패턴이 적용된 클래스  :  Context
    - 캐릭터 직업 선택, 공격, 이동, 몬스터 생성, 맵 이동 등 모든 객체의 행동을 Context 클래스로 감싸, 게임의 메인 루프에서 Context 객체만으로 간단하게 구현함
    - Context 클래스에 서버에 데이터를 등록하는 로직을 작성해 각각의 객체에서 MySQL문을 사용하지 않고 Context 클래스에서 작업을 가능하게 함
- 싱글톤 패턴
    - 싱글톤 패턴이 적용된 클래스 :  Context
- 팩토리 패턴
    - CharacterBase와 MonsterBase는 추상 팩토리로 작동하며, 캐릭터와 몬스터 생성을 위한 인터페이스를 아래와 같은 순수 가상 함수를 통해 제공함
    
    ```cpp
    // 캐릭터의 팩토리 메소드
    virtual void BaseSetCharacter(Job job) = 0;
    
    // 몬스터의 팩토리 메소드
    virtual void BaseSetMonster(MType Type) = 0;
    ```
    
    - 위의 함수들을 각각 Character 클래스와 Monster 클래스에서 재정의 하여 해당 인터페이스를 통해 객체를 생성할 수 있음
    - Character는 Job 열거형, Monster는 MType 열거형으로 직업을 구체적으로 가짐

- 종합 코드
    
    ```cpp
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
        
            context->BattleInterface();
        }
    }
    ```
    
    - 캐릭터가 맵을 이동하면 특정 확률로 몬스터를 만나게 됨
    - 몬스터를 만나면 일정 확률에 따라 만나는 몬스터의 종류가 결정되고, 이때 팩토리 메소드를 통해 몬스터를 결정
    - 캐릭터는 만난 몬스터를 싸울 대상으로 등록
    - 싱글톤 패턴으로 작성된 Context 포인터를 받아와서, Context의 BattleInterface() 함수 호출로 전투 장면으로 화면이 전환됨

<br>

### 인터페이스 사용

- BattleSystemInterface
    
    ```cpp
    class BattleSystem
    {
    public:
    	virtual void Attack() = 0;
    	virtual void Defend() = 0;
    	virtual void Run() = 0;
    	virtual ~BattleSystem() {}
    };
    ```
    
    - 캐릭터 클래스에 공격, 방어, 도망 기능을 하드 코딩 하지 않고, 인터페이스를 구현하여 기능들을 구현함
    - 현재 몬스터의 공격 방식이 캐릭터의 Attack 함수 안에 구현되어 있지만, 후에 몬스터의 공격 패턴을 바꾸고 싶을 때 해당 인터페이스를 구현함으로써 기능 확장을 열어놓음

<br>

# 회고

### 알게된 점

1. 이론으로만 배웠던 디자인 패턴들을 직접 작성한 코드에 적용해보며 막연히 어렵게만 느껴졌던 디자인 패턴을 사용한 깔끔한 코드 설계에 자신감을 얻게 되었다.
2. 특정 엔진을 사용하는 것이 아닌 C++ 언어만을 사용해 게임을 만들며 메모리 할당과 해제의 중요성, 댕글링 포인터와 참조같이 자원 관리의 중요성과 게임의 메인 루프같이 엔진의 주요 기능에 대해 알 수 있었다.

<br>

### 아쉬운점

1. 데이터베이스에 데이터를 넣을 때 인코딩 방식이 달라 한글로는 데이터를 넣지 못했다. Workbench의 인코딩 바꾸는 방법을 찾지 못해 모든 데이터를 영어로 넣게 되어 아쉬웠다.
2. 맵을 종류별로 나눴는데, 맵별 특징을 넣었다면 게임의 컨텐츠가 더욱 풍부했을 것 같다.
3. 데이터 저장 기능만 존재하고 불러오기 기능을 넣지 못했다.
