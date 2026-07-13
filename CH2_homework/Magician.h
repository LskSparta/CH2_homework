#pragma once
#include"Player.h"
class Magician : public Player
{

	public:
		Magician(string name, int hp, int mp, int attack, int defense) :Player(name, hp, mp, attack, defense) {
			job = "마법사";
		};

		// Player을(를) 통해 상속됨
		void Attack(Monster* monster) override;
};

