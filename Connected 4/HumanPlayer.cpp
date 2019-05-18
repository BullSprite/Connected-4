#include "HumanPlayer.h"

HumanPlayer :: HumanPlayer(int playerType) : Player::Player(playerType) {}

bool HumanPlayer::isHuman() {
	return true;
}