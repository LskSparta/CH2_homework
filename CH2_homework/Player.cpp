#include <iostream>

#include "Player.h"

using namespace std;

void Player::setName(string name)
{
	this->name = name;
}

Player::Player(string name, int hp, int mp, int attack, int defense)
{
	this->name = name;
	this->maxHp = hp;
	this->hp = hp;
	this->maxMp = mp;
	this->mp = mp;
	this->attack = attack;
	this->defense = defense;
}

string Player::getName()
{
	return name;
}

void Player::setMaxHp(int maxHp)
{
	this->maxHp = maxHp;
}

int Player::getMaxHp() const
{
	return maxHp;
}

void Player::setHp(int hp)
{
	this->hp = min(maxHp, hp);
}

int Player::getHp() const
{
	return hp;
}

void Player::setMaxMp(int maxMp)
{
	this->maxMp = maxMp;
}

int Player::getMaxMp() const
{
	return maxMp;
}

void Player::setMp(int mp)
{
	this->mp = min(maxMp, mp);
}

int Player::getMp() const
{
	return mp;
}

void Player::setAttack(int attack)
{
	this->attack = attack;
}

int Player::getAttack() const
{
	return attack;
}

void Player::setDeffense(int defense)
{
	this->defense = defense;
}

int Player::getDefense() const
{
	return defense;
}

void Player::healHp(int healHp)
{
	hp = min(maxHp, hp + healHp);
}

void Player::healMp(int healMp)
{
	mp = min(maxMp, mp + healMp);
}

void Player::printPlayerStatus()
{
	cout << "====================================" << endl;
	cout << "닉네임: " << name << " | 직업: " << job << " | Lv : " << level << endl;
	cout << "HP: " << hp << " | 공격력: " << attack << " | 방어력: " << defense << endl;
	cout << "====================================" << endl;
}

void Player::Hit(int attackPower)
{
	int hitPoint = attackPower - defense;
	if (hitPoint <= 0) {
		hitPoint = 1;
	}
	cout << name << "은(는) " << hitPoint << "만큼의 피해를 입었다." << endl;
	hp = max(hp - hitPoint, 0) ;
	cout << name << "의 체력 : " << hp << endl;
}

bool Player::IsDead() const
{
	if (hp <= 0) {
		return true;
	}
	return false;
}

