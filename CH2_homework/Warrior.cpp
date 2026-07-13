#include<iostream>

#include "Warrior.h"
#include "Monster.h"

void Warrior::Attack(Monster* monster)
{
	cout << "* 대검으로 적을 베어냅니다." << endl;
	if (monster == nullptr) {
		return;
	}
	monster->Hit(attack);
}
