#ifndef _PHAYER_H
#define _PLAYER_H

class Player {
protected:
	int player;
public:
	Player(int);
	virtual int getPlayerType() = 0;
	virtual bool isHuman() = 0;
};

#endif // !_PHAYER_H
