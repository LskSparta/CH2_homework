#include "Monster.h"
#include "Player.h"

Monster::Monster(string name, int hp, int attack, int defense)
{
	this->name = name;
	this->maxHp = hp;
	this->hp = hp;
	this->attack = attack;
	this->defense = defense;
}

void Monster::Hit(int attackPower)
{
	int hitPoint = attackPower - defense;
	if (hitPoint <= 0) {
		hitPoint = 1;
	}
	cout << name << "은(는) " << hitPoint << "만큼의 피해를 입었다." << endl;
	hp -= hitPoint;
	cout << name << "의 체력 : " << hp << endl;
	if (this->IsDead()) {
		cout << name << " 사망" << endl;
	}
}

bool Monster::IsDead() const
{
	if (hp <= 0) {
		return true;
	}
	return false;
}
