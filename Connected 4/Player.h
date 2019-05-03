#ifndef _PHAYER_H
#define _PLAYER_H

enum playerType { HUMAN = 1, MINMAX };

class Player {
protected:
	int player;
public:
	virtual int getPlayerType() = 0;
};

#endif // !_PHAYER_H
