#include<iostream>

#include "Archer.h"
#include "Monster.h"

void Archer::Attack(Monster* monster)
{
	cout << "* 저격을 합니다." << endl;
	if (monster == nullptr) {
		return;
	}
	int attackPower = max(attack / attackMultiple, 1);
	for (int i = 0; i < attackMultiple; i++) {
		monster->Hit(attackPower);
	}
}
