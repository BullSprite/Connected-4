#ifndef _PHAYER_H
#define _PLAYER_H

class Player {
protected:
	int player;
public:
	Player(int);
	int getPlayerTurn();
	virtual bool isHuman() = 0;
};

#endif // !_PHAYER_H
