#pragma once

#include"StructItem.h"
#include "FLevelUp.h"
#include<string>
#include<map>

using namespace std;

class Monster;

class Player
{
	protected:
		string name;
		int maxHp;
		int hp;
		int maxMp;
		int mp;
		int attack;
		int defense;
		string job = "미정";
		int level = 1;
		int exp = 0;
		int expMax = 100;
		FLevelUp fLevelUp = FLevelUp();

		void LevelUp();
	public:
		virtual ~Player() {};
		Player(string name, int hp, int mp, int attack, int defense);
		void setName(string name);
		string getName();
		void setMaxHp(int maxHp);
		int getMaxHp() const;
		void setHp(int hp);
		int getHp() const;
		void setMaxMp(int maxMp);
		int getMaxMp() const;
		void setMp(int mp);
		int getMp() const;
		void setAttack(int attack);
		int getAttack() const;
		void setDeffense(int defense);
		int getDefense() const;

		void healHp(int healHp);
		void healMp(int healMp);

		void printPlayerStatus();
		void Hit(int attackPower);

		void AddExp(int exp);

		virtual void Attack(Monster* monster = nullptr) = 0;

		bool IsDead() const;

};

