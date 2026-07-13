#include "Slime.h"

#include "Player.h"
#include "StructItem.h"

void Slime::Attack(Player* player)
{
	if (player == nullptr) {
		return;
	}
	cout << "슬라임의 공격" << endl;
	player->Hit(attack);
}

ItemInfo Slime::DropItem()
{
	ItemInfo dropItem;
	dropItem.name = "슬라임의 끈적한 젤리";
	dropItem.consumable = false;
	dropItem.price = 20;
	return dropItem;
}
