#pragma once

#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>

#include "Player.h"
#include "Warrior.h"
#include "Magician.h"
#include "Thief.h"
#include "Archer.h"

#include "Monster.h"
#include "Slime.h"
#include "Goblin.h"

#include "Potions.h"


using namespace std;

Player* player = nullptr;

vector<Potions*> potions;

string name = "";
int hp = 0;
int mp = 0;
int attack = 0;
int defense = 0;
map<ItemInfo*, int> inventory;

string eraseFrontPad(const string& str) {
    size_t firstNonSpace = str.find_first_not_of(' ');
    if (firstNonSpace == string::npos) {
        return str;
    }
	return str.substr(firstNonSpace);
}

int StringToPossitiveInt(const string& str, string statName, int minValue) {
    int value;
    try {
		value = stoi(str);
    } catch (const invalid_argument) {
		throw invalid_argument(statName + "은(는) 양수인 정수로 입력 해주세요.");
    } catch (const out_of_range&) {
		throw invalid_argument(str + "는 너무 큰 수입니다.");
    }

    if (value < 0) {
        throw invalid_argument(statName + "은(는) 양수인 정수로 입력 해주세요.");
    }
    else if (value < minValue) {
        throw invalid_argument(statName + "은(는) 최소 " + to_string(minValue) + " 이상이어야 합니다.");
    }
    return value;
}

void showStatus()
{
    cout << "====================================" << endl;
    cout << "  " << name << " 의 현재 능력치" << endl;
    cout << "====================================" << endl;
    cout << "HP : " << hp << "    " "MP : " << mp << endl;
    cout << "공격력 : " << attack << "    " << "방어력 : " << defense << endl;
    cout << "====================================" << endl;
}

void AddItemToInventory(ItemInfo* newItem, int itemCount = 1) {
    bool isFirst = false;
    auto itr = inventory.begin();
    bool isContain = false;
    for (itr; itr != inventory.end(); itr++) {
        if (itr->first->GetName() == newItem->GetName()) {
            isContain = true;
            break;
        }
    }
    if (!isContain) {
        inventory.insert({ newItem, itemCount });
        isFirst = true;
    }
    else {
        if (itemCount == 1) {
            itr->second++;
        }
        else {
            itr->second += itemCount;
        }
    }
    cout << "-> " << newItem->GetName() << itemCount << "개 획득!" << endl;
    cout << "인벤토리에 저장되었습니다." << endl;
    if (!isFirst) {
        delete newItem;
    }
}

vector<ItemInfo*> GetConsumableItem() {
    auto itr = inventory.begin();
    vector<ItemInfo*> consumableItems;
    while (itr != inventory.end())
    {
        const ItemInfo* item = itr->first;
        if (!item->IsConsumable()) {
            ++itr;
            continue;
        }
        consumableItems.push_back(itr->first);
        ++itr;
    }
    return consumableItems;
}

void ConsumeItemInInventory(ItemInfo* consumeItem, Player* target) {
    auto itr = inventory.begin();
    bool isContain = false;
    for (itr; itr != inventory.end(); itr++) {
        if (itr->first->GetName() == consumeItem->GetName()) {
            isContain = true;
            break;
        }
    }
    if (!isContain) {
        cout << "에러 : 해당 아이템은 소지하고 있지 않습니다" << endl;
        return;
    }
    ItemInfo* item = itr->first;
    item->Consume(target);
    itr->second--;
    if (itr->second <= 0) {
        inventory.erase(consumeItem);
        delete item;
    }
}

void ShowItemsInInventory() {
    cout << "\n\n\n\n";
    if (inventory.empty()) {
        cout << "인벤토리에 아무것도 없습니다." << endl;
        return;
    }
    auto itr = inventory.begin();
    while (itr != inventory.end())
    {
        cout << itr->first->GetName() << " " << itr->second << " 개" << endl;
        itr++;
    }
}

void ShowAllRecipe() {
    for (int i = 0; i < potions.size(); i++) {
        potions[i]->ShowRecipe();
    }
}

void SearchRecipeByStuff(string stuff) {
    int count = 0;
    for (int i = 0; i < potions.size(); i++) {
        bool hasStuff = potions[i]->IsStuffInRecipe(stuff);
        if (hasStuff) {
            count++;
            potions[i]->ShowRecipe();
        }
    }
    if (count != 0) {
        cout << "총 " << count << "개의 레시피를 찾았습니다." << endl;
        return;
    }
    cout << "찾을 수 없습니다" << endl;
}

void SearchPotionByName(string potionName) {
    for (int i = 0; i < potions.size(); i++) {
        if (potionName == potions[i]->GetName()) {
            potions[i]->ShowRecipe();
            return;
        }
    }
    cout << "찾을 수 없습니다" << endl;
}

void SetPotion(int count, int* ptrPotionHp = nullptr, int* ptrPotionMp = nullptr) {
    if (count < 0) {
        cout << "Func::SetPotion count 변수는 0 이상" << endl;
        return;
    }

    if (!ptrPotionHp || !ptrPotionMp) {
        cout << "Func::SetPotion nullptr 발생" << endl;
        return;
    }

    *ptrPotionHp = count;
    *ptrPotionMp = count;
}



void ShowMainMenu() {
    cout << "===========================================" << endl;
    cout << "   [ 던전 탈출 텍스트 RPG ]" << endl;
    cout << "===========================================" << endl;
    cout << "1. 던전 입장 -> 몬스터 전투 -> 아이템 드롭 -> 인벤토리 저장" << endl;
    cout << "2. 인벤토리 확인" << endl;
    cout << "3. 포션 제작소 -> 레시피 보기 / 검색" << endl;
    cout << "0. 게임 종료" << endl;
    cout << "===========================================" << endl;
}

bool SetStageUseItem() {
    cout << "[ 인벤토리 ]" << endl;
    vector<ItemInfo*> consumableItems = GetConsumableItem();
    if (consumableItems.empty()) {
        cout << "사용 가능한 아이템이 없습니다." << endl;
        return false;
    }

    bool isStageOver = false;
    while (!isStageOver)
    {
        for (int i = 0; i < consumableItems.size(); i++) {
            ItemInfo* item = consumableItems[i];
            int count = inventory.find(item)->second;
            cout << i + 1 << ". " << item->GetName() << " :: " << count << " 개" << endl;
            //item->ShowItemInfo();
        }
        cout << "0. 돌아가기" << endl;
        string choiceStr;
        getline(cin, choiceStr);
        int choiceNum;
        try
        {
            choiceNum = StringToPossitiveInt(choiceStr, "사용할 아이템 번호", 0);
            if (choiceNum > consumableItems.size()) {
                cout << "해당 번호 없음" << endl;
                continue;
            }
        }
        catch (const invalid_argument& e)
        {
            cout << e.what() << endl;
            continue;
        }
        if (choiceNum == 0) {
            return false;
        }

        //인덱스로 변경
        choiceNum--;
        ItemInfo* item = consumableItems[choiceNum];
        ConsumeItemInInventory(item, player);

        isStageOver = true;
    }
    return true;
}

void StartBattle(Player* player) {
    //STEP 5 - Monster 클래스 + 1:1 전투 (클래스 설계, 전투 루프) 시작
    //STEP 6 - 인벤토리 + 아이템 드롭 (STL vector)시작
    Monster* slime = new Slime("슬라임", 120, 20, 10);
    Monster* goblin = new Goblin("고블린", 120, 30, 20);
    vector<Monster*> monsters = { slime, goblin };
    cout << "\n\n\n" << "[ 전투 시작! ]" << endl;
    PotionHp* potionHp = new PotionHp("HP 포션", 50, true);
    PotionMp* potionMp = new PotionMp("MP 포션", 50, true);
    int potionHpInitCount = 2;
    int potionMpInitCount = 2;
    AddItemToInventory(potionHp, potionHpInitCount);
    AddItemToInventory(potionMp, potionMpInitCount);
    cout << "HP 포션 " << potionHpInitCount << "개 MP 포션 " << potionMpInitCount << "개 지급 됨";
    while (!player->IsDead())
    {
        cout << "\n--- 플레이어 턴 ---" << endl;
        cout << "1. 공격" << endl;
        cout << "2. 아이템 사용" << endl;
        string actionStr;
        getline(cin, actionStr);
        int actionNum;
        try
        {
            actionNum = StringToPossitiveInt(actionStr, "선택 : ", 1);
            if (actionNum > 2) {
                cout << "선택은 1 ~ 2 정수만 가능합니다." << endl;
                continue;
            }
        }
        catch (const std::invalid_argument& e)
        {
            cout << e.what() << endl;
            continue;
        }
        bool isDoBattle = true;
        bool isItemChoosed = true;
        switch (actionNum)
        {
        case 1:
            break;
        case 2:
            isDoBattle = false;
            isItemChoosed = SetStageUseItem();
            break;
        }
        if (!isItemChoosed) {
            continue;
        }

        if (isDoBattle) {
            for (int i = 0; i < monsters.size(); i++) {
                Monster* monsterTarget = monsters[i];
                if (monsterTarget->IsDead()) {
                    continue;
                }
                player->Attack(monsterTarget);
                break;
            }

        }

        bool isVictory = true;
        for (int i = 0; i < monsters.size(); i++) {
            if (!monsters[i]->IsDead()) {
                isVictory = false;
                break;
            }
        }

        if (isVictory) {
            cout << "\n★ 전투 승리!" << endl;
            for (int i = 0; i < monsters.size(); i++) {
                ItemInfo* dropItem = monsters[i]->DropItem();
                AddItemToInventory(dropItem);
            }
            player->AddExp(500);
            break;
        }


        cout << "\n--- 몬스터 턴 ---" << endl;
        for (int i = 0; i < monsters.size(); i++) {
            Monster* monsterTurn = monsters[i];
            if (monsterTurn->IsDead()) {
                continue;
            }
            monsterTurn->Attack(player);
            if (player->IsDead()) {
                cout << "\n★ 전투 패배!" << endl;
                break;
            }
        }
    }


    for (int i = 0; i < monsters.size(); i++) {
        delete monsters[i];
    }

    player->healHp(player->getMaxHp()); //다음 전투를 위해서 체력 회복

    //STEP 5 - Monster 클래스 + 1:1 전투 (클래스 설계, 전투 루프) 종료
    //STEP 6 - 인벤토리 + 아이템 드롭 (STL vector)종료
}

void StartPotionStage() {
    bool isPotionStageOver = false;
    while (!isPotionStageOver)
    {
        cout << "\n\n\n\n";
        cout << "=== 포션 제작소 ===" << endl;
        cout << "1. 전체 레시피 보기" << endl;
        cout << "2. 포션 이름으로 검색" << endl;
        cout << "3. 재료로 검색" << endl;
        cout << "0. 돌아가기" << endl;
        cout << "\n\n";

        string choiceStr;
        getline(cin, choiceStr);
        int choiceNum;
        try
        {
            choiceNum = StringToPossitiveInt(choiceStr, "선택 ", 0);
        }
        catch (const invalid_argument& e)
        {
            cout << e.what() << "\n";
            continue;
        }
        if (choiceNum > 3) {
            cout << "선택은 0~3 사이의 정수로 입력 해주세요\n\n\n";
            continue;
        }

        string searchStr = "";
        switch (choiceNum)
        {
        case 0:
            isPotionStageOver = true;
            break;
        case 1:
            ShowAllRecipe();
            break;
        case 2:
            getline(cin, searchStr);
            SearchPotionByName(searchStr);
            break;
        case 3:
            getline(cin, searchStr);
            SearchRecipeByStuff(searchStr);
            break;
        }
    }
}

int main()
{
    //STEP 1 - 캐릭터 생성 화면 시작
    cout << "===========================================\n";
    cout << "   [ 던전 탈출 텍스트 RPG ]\n";
    cout << "===========================================\n";
    cout << "용사의 이름을 입력해주세요: ";
	getline(cin, name);


	bool isValidInput = false;
    //STEP 1 - 캐릭터 생성 화면 종료

    cout << "\n";
    
    //STEP 2 - 입력 유효성 검사 시작
    while (!isValidInput)
    {
        cout << "HP와 MP를 입력해주세요: \n";
        string inputHpMp = "";
        getline(cin, inputHpMp);
        inputHpMp = eraseFrontPad(inputHpMp);
        size_t spacePos = inputHpMp.find(' ');
        if (spacePos == string::npos) {
            cout << "HP와 MP를 공백으로 구분하여 입력 해주세요\n";
            continue;
        }
        try {
            hp = StringToPossitiveInt(inputHpMp.substr(0, spacePos), "HP", 50);
            mp = StringToPossitiveInt(inputHpMp.substr(spacePos + 1), "MP", 50);
        }
        catch (const invalid_argument& e) {
            cout << e.what() << "\n";
            continue;
        }
        isValidInput = true;
    }

    isValidInput = false;
    while (!isValidInput) {
        cout << "\n";
        cout << "공격력과 방어력을 입력해주세요: \n";
        string inputAttackDefense = "";
        getline(cin, inputAttackDefense);
        inputAttackDefense = eraseFrontPad(inputAttackDefense);
        size_t spacePos = inputAttackDefense.find(' ');
        if (spacePos == string::npos) {
            cout << "공격력과 방어력을 공백으로 구분하여 입력 해주세요\n";
            continue;
        }
        try {
            attack = StringToPossitiveInt(inputAttackDefense.substr(0, spacePos), "공격력", 20);
            defense = StringToPossitiveInt(inputAttackDefense.substr(spacePos + 1), "방어력", 20);
        }
        catch (const invalid_argument& e) {
            cout << e.what() << "\n";
            continue;
        }
        isValidInput = true;
    }

    //STEP 2 - 입력 유효성 검사 종료


    //STEP 3 - 스탯 관리 메뉴 시작
    cout << "\n";
    showStatus();

    int startHpPotionNum = 0;
    int startMpPotionNum = 0;
    //도전 STEP 1 - setPotion 함수 (포인터 심화) 시작
    SetPotion(5, &startHpPotionNum, &startMpPotionNum);
    //도전 STEP 1 - setPotion 함수 (포인터 심화) 종료
    int hpPotionHeal = 20;
    int mpPotionHeal = 20;
    cout << "\n\n";
    cout << "* HP 포션 " << startHpPotionNum << "개, MP 포션 " << startMpPotionNum << "개가 기본 지급되었습니다.\n";

    bool isGameStart = false;

    while (!isGameStart)
    {
        cout << "\n\n";
        cout << "============================================\n";
        cout << " < 캐릭터 강화 >\n";
        cout << "1. HP UP    2. MP UP    3. 공격력 2배\n";
        cout << "4. 방어력 2배  5. 현재 능력치  0. 게임 시작\n";
        cout << "============================================\n";
        cout << "남은 HP 포션: " << startHpPotionNum << "개, 남은 MP 포션: " << startMpPotionNum << "개\n";
        cout << "번호를 선택해주세요: ";
        string choiceStr;
        int choiceNum = 0;
        getline(cin, choiceStr);
        try
        {
            choiceNum = StringToPossitiveInt(choiceStr, "선택 번호", 0);
        }
        catch (const invalid_argument& e)
        {
            cout << e.what() << "\n";
            continue;
        }

        if (choiceNum > 5) {
            cout << "선택 번호는 0~5 사이의 정수로 입력 해주세요\n";
            continue;
        }

        cout << "\n\n";

        switch (choiceNum)
        {
        case 0:
            cout << "게임을 시작합니다!\n";
            isGameStart = true;
            break;
        case 1:
            if (startHpPotionNum < 1) {
                cout << "* HP 포션이 부족합니다.\n";
                break;
            }
            if (hp + hpPotionHeal < 0) {// HP가 int 범위를 넘어가는 경우
                cout << "* HP가 너무 커서 증가할 수 없습니다.\n";
                break;
            }
            hp += hpPotionHeal;
            startHpPotionNum--;
            cout << "* HP가 20 증가했습니다. 현재 HP : " << hp << " (HP 포션 차감: 남은 포션 " << startHpPotionNum << "개)\n\n";
            break;
        case 2:
            if (startMpPotionNum < 1) {
                cout << "* MP 포션이 부족합니다.\n";
                break;
            }
            if (mp + mpPotionHeal < 0) {// MP가 int 범위를 넘어가는 경우
                cout << "* MP가 너무 커서 증가할 수 없습니다.\n";
                break;
            }
            mp += mpPotionHeal;
            startMpPotionNum--;
            cout << "* MP가 20 증가했습니다. 현재 MP : " << mp << " (MP 포션 차감: 남은 포션 " << startMpPotionNum << "개)\n\n";
            break;
        case 3:
            if (attack * 2 < 0) {// 공격력이 int 범위를 넘어가는 경우
                cout << "* 공격력이 너무 커서 2배 증가할 수 없습니다.\n";
                break;
            }
            attack *= 2;
            cout << "* 공격력이 2배 증가했습니다. (현재 공격력: " << attack << ")\n";
            break;
        case 4:
            if (defense * 2 < 0) {// 방어력이 int 범위를 넘어가는 경우
                cout << "* 방어력이 너무 커서 2배 증가할 수 없습니다.\n";
                break;
            }
            defense *= 2;
            cout << "* 방어력이 2배 증가했습니다. (현재 방어력: " << defense << ")\n";
            break;
        case 5:
            cout << "\n\n";
            showStatus();
            break;
        default:
            break;
        }
    }

    //STEP 3 - 스탯 관리 메뉴 종료

    //STEP 4 - Player 클래스 + 직업 선택 (클래스, 상속, 다형성) 시작
    
    int bonusStat = 30;
    while (true)
    {
        cout << "\n\n\n";
        cout << name << "님, 직업을 선택해주세요!" << endl;
        cout << "1. 전사   2. 마법사   3. 도적   4. 궁수" << endl;
        string choiceStr;
        int choiceNum;
        getline(cin, choiceStr);
        try
        {
            choiceNum = StringToPossitiveInt(choiceStr, "선택 번호", 1);
        }
        catch (const invalid_argument& e)
        {
            cout << e.what() << "\n";
            continue;
        }
        if (choiceNum > 4) {
            cout << "선택 번호는 1~4 사이의 정수로 입력 해주세요\n";
            continue;
        }

        switch (choiceNum)
        {
            case 1 :
                cout << "* 전사로 전직하였습니다. (HP +30)" << endl;
                player = new Warrior(name, hp, mp, attack, defense);
                break;
            case 2:
                cout << "* 마법사로 전직하였습니다. (MP +30)" << endl;
                player = new Magician(name, hp, mp, attack, defense);
                break;
            case 3:
                cout << "* 도적으로 전직하였습니다. (공격력 +30)" << endl;
                player = new Thief(name, hp, mp, attack, defense);
                break;
            case 4:
                cout << "* 궁사로 전직하였습니다. (공격력 +30)" << endl;
                player = new Archer(name, hp, mp, attack, defense);
                break;
        }
        player->Attack();
        player->printPlayerStatus();
        break;
    }
    
    //STEP 4 - Player 클래스 + 직업 선택 (클래스, 상속, 다형성) 종료


    potions.push_back(new Potions("HP 포션", { { "허브", 1 } , {"맑은 물", 1} }));
    potions.push_back(new Potions("스테미나포션", { { "허브", 1 } , {"베리", 1} }));
    
    bool isContinue = true;
    while (isContinue)
    {
        cout << "\n\n\n\n";
        ShowMainMenu();
        string choiceStr;
        getline(cin, choiceStr);
        int choiceNum;
        try
        {
            choiceNum = StringToPossitiveInt(choiceStr, "선택", 0);
        }
        catch (const invalid_argument& e)
        {
            cout << e.what() << endl;
            continue;
        }

        if (choiceNum > 3) {
            cout << "선택은 0~3 사이의 정수로 입력 해주세요." << endl;
            continue;
        }

        switch (choiceNum)
        {
        case 0:
            isContinue = false;
            break;
        case 1:
            StartBattle(player);
            break;
        case 2:
            ShowItemsInInventory();
            break;
        case 3:
            StartPotionStage();
            break;
        }
    }

    for (int i = 0; i < potions.size(); i++) {
        delete potions[i];
    }
    delete player;
    return 0;
}