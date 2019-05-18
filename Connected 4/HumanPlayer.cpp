#include "HumanPlayer.h"

HumanPlayer :: HumanPlayer(int playerType) : Player::Player(playerType) {}

int HumanPlayer::getPlayerType()
{
	return 0;
}

bool HumanPlayer::isHuman() {
	return true;
}