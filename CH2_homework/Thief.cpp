#include<iostream>

#include "Thief.h"
#include "Monster.h"

void Thief::Attack(Monster* monster)
{
    cout << "* 단검으로 적을 찌릅니다." << endl;
    if (monster == nullptr) {
        return;
    }
	int attackPower = max(attack / attackMultiple, 1);
	for (int i = 0; i < attackMultiple; i++) {
		monster->Hit(attackPower);
	}
}
