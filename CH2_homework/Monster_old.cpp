#include"Monster_old.h"
#include"Player.h"

void Monster_old::Attack(Player* player) {
	if (player == nullptr) {
		return;
	}
	player->Hit(attack);
}