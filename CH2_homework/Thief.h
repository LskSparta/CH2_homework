#pragma once
#include"Player.h"
class Thief : public Player 
{
	protected:
		int attackMultiple = 5;
	public:
		Thief(string name, int hp, int mp, int attack, int defense) :Player(name, hp, mp, attack, defense) {
			job = "도적";
		};

		// Player을(를) 통해 상속됨
		void Attack(Monster* monster) override;
};

