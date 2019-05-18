#ifndef _HUMAN_PLAYER_H
#define _HUMAN_PLAYER_H
#include "Player.h"

class HumanPlayer : public Player{
public:
	HumanPlayer(int);
	bool isHuman() override;
};

#endif // !_HUMAN_PLAYER_H