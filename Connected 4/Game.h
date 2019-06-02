#include "HumanPlayer.h"
#ifndef _GAME_H
#define _GAME_H

class Game {
private:
	bool run;
public:
	Game();
	int execute();
	void exit();
};

#endif // !_GAME_H
