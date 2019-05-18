#include "Player.h"

Player::Player(int playerType) {
	player = playerType;
}

int Player::getPlayerTurn() {
	return player;
}