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
	player->healHp(pointHp);
}

void PotionMp::Consume(Player* player) const
{
	player->healMp(pointMp);
}
