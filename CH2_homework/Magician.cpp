#include<iostream>

#include "Magician.h"
#include "Monster.h"

void Magician::Attack(Monster* monster)
{
	cout << "* 파이어볼을 발사한다." << endl;
	if (monster == nullptr) {
		return;
	}
	monster->Hit(attack);
}
