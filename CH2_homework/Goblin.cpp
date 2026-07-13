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

ItemInfo* Goblin::DropItem()
{
    ItemInfo* dropItem = new ItemInfo("고블린 토벌 증거", 20, false);
    return dropItem;
}
