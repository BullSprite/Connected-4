#ifndef _AI_PLAYER_H
#define _AI_PLAYER_H

#include "Project.h"

class AIPlayer : public Player {
private:
	int maxDepth;
public:
	friend class Field;
	AIPlayer(int);
	bool isHuman() override;
	int runMiniMax(Field &, Player**, const int &, const int &);
	int getScore(Field &, Player**);
	void setMaxDepth(const int &);
};

#endif // !_AI_PLAYER_H
