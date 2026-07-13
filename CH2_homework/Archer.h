#pragma once
#include"Player.h"
class Archer : public Player
{
	protected:
		int attackMultiple = 3;
	public:
		Archer(string name, int hp, int mp, int attack, int defense) :Player(name, hp, mp, attack, defense) {
			job = "궁수";
		};

		// Player을(를) 통해 상속됨
		void Attack(Monster* monster) override;
};

