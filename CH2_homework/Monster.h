#pragma once
#include<string>
#include<iostream>

using namespace std;

class Player;
struct ItemInfo;


class Monster
{
protected:
	string name;
	int maxHp;
	int hp;
	int attack;
	int defense;
public:
	virtual ~Monster() {
		cout << name << " 제거됨." << endl;
	};
	Monster(string name, int hp, int attak, int defense);
	virtual void Attack(Player* player = nullptr) = 0;
	virtual ItemInfo DropItem() = 0;
	void Hit(int attackPower);
	bool IsDead() const;
};

