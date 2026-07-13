#pragma once

#include"Monster.h"
class Slime : public Monster 
{
public:
	Slime(string name, int hp, int attak, int defense) :Monster(name, hp, attak, defense) {};

	// Monster을(를) 통해 상속됨
	void Attack(Player* player) override;

	// Monster을(를) 통해 상속됨
	ItemInfo DropItem() override;
};

