#pragma once

#include"Monster.h"
class Goblin : public Monster
{
public:
	Goblin(string name, int hp, int attak, int defense) :Monster(name, hp, attak, defense) {};

	// Monster을(를) 통해 상속됨
	void Attack(Player* player) override;
	ItemInfo* DropItem() override;
};

