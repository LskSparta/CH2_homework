#include<iostream>

#include "StructItem.h"
#include "Player.h"

void ItemInfo::ShowItemInfo() const
{
	cout << name << " (" << price << "G)" << endl;
}

string ItemInfo::GetName() const
{
	return name;
}

int ItemInfo::GetPrice() const
{
	return price;
}

bool ItemInfo::IsConsumable() const
{
	return consumable;
}

ItemInfo::ItemInfo(string name, int price, bool consumable)
{
	this->name = name;
	this->price = price;
	this->consumable = consumable;
}

void PotionHp::Consume(Player* player) const
{
	int beforeHp = player->getHp();
	player->healHp(pointHp);
	int afterHp = player->getHp();
	cout << "* HP 포션 사용! HP " << pointHp << " 회복 (" << beforeHp << " -> " << afterHp << ")" << endl;
}

void PotionMp::Consume(Player* player) const
{
	int beforeMp = player->getMp();
	player->healMp(pointMp);
	int afterMp = player->getMp();
	cout << "* Mp 포션 사용! Mp " << pointMp << " 회복 (" << beforeMp << " -> " << afterMp << ")" << endl;
}
