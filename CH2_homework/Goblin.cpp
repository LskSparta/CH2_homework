#include "Goblin.h"
#include "Player.h"

void Goblin::Attack(Player* player)
{
    if (player == nullptr) {
        return;
    }
    cout << "고블린의 공격" << endl;
    player->Hit(attack);
}

ItemInfo Goblin::DropItem()
{
    ItemInfo dropItem;
    dropItem.consumable = false;
    dropItem.name = "고블린 토벌 증거";
    dropItem.price = 20;
    return dropItem;
}
