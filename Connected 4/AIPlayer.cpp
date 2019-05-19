#include "AIPlayer.h"
#include <vector>
#include <cstdlib>
#include <ctime>

AIPlayer::AIPlayer(int playerType) : Player::Player(playerType) {}

bool AIPlayer::isHuman() {
	return false;
}

void AIPlayer::setMaxDepth(const int & maxDepth) {
	this->maxDepth = maxDepth;
}

int AIPlayer::runMiniMax(Field & oldField, Player** players, const int & tPlayer, const int & depth) {
	if (oldField.getResult() != DEFAULT)
		return oldField.getResult();
	int test = DEFAULT;
	vector<int> bestMoves;
	bestMoves.push_back(DEFAULT);
	int minMax = players[tPlayer]->isHuman() ? MAX : MIN;

	for (int i = 0; i < 7; i++) {
		Field newField = oldField;
		if (newField.checkTurnPossibility(i)) {
			newField.setTurn(i, *players[tPlayer]);
			if (depth != 0) {
				test = runMiniMax(newField, players, (tPlayer + 1) % 2, depth - 1);
			}
			else {
				test = getScore(newField, players);
			}

			if ((test > minMax && !players[tPlayer]->isHuman()) || (test < minMax && players[tPlayer]->isHuman())) {
				minMax = test;
				bestMoves.clear();
				bestMoves.push_back(i);
			}
			else if (test == minMax) bestMoves.push_back(i);
		}
	}

	srand(time(NULL));

	if (depth == maxDepth) {
		if (bestMoves[0] == DEFAULT) {
			bestMoves.clear();
			for (int i = 0; i < 7; i++)
				if (oldField.checkTurnPossibility(i))
					bestMoves.push_back(i);
			return bestMoves[rand() % bestMoves.size()];
		}
		return bestMoves[rand() % bestMoves.size()];
	}
	return minMax;
}

int AIPlayer::getScore(Field & field, Player** p) {
	if (field.getResult() != DEFAULT)
		return field.getResult();

	int oppPossible2 = 0, oppPossible3 = 0, oppPossible4 = 0;
	int possible2 = 0, possible3 = 0, possible4 = 0;
	int posScore = 0, oppPosScore = 0;

	for (int j = 0; j < 7; j++) {
		int i = 5;
		while (field[i][j] == 0 && i >= 0) i--;
		if (i < 0) continue;
		int tPlayer = field[i][j];

		int straight = 0, oppStraight = 0;

		if (i < 5) {
			(tPlayer == player ? straight : oppStraight) = field.verticalStraight(i, j, *p[tPlayer % 2]);
			switch (tPlayer == player ? straight : oppStraight)
			{
			case 3: (tPlayer == player ? possible4 : oppPossible4)++; break;
			case 2: if (i < 4) (tPlayer == player ? possible3 : oppPossible3)++; break;
			case 1: if (i < 3) (tPlayer == player ? possible2 : oppPossible2)++; break;
			}
		}
		for (; i > -1; i--) {
			tPlayer = field[i][j];
			tPlayer == player ? posScore : oppPosScore = 4 - abs(3 - j);
			int * pos = field.horizontalStraight(i, j, *p[tPlayer % 2]);
			switch (pos[1] + 1) {
			case 3: if (pos[0] > 0) (tPlayer == player ? possible4 : oppPossible4)++;
				if (pos[2] > 0) (tPlayer == player ? possible4 : oppPossible4)++; break;
			case 2: if (pos[0] > 0) (tPlayer == player ? possible3 : oppPossible3)++;
				if (pos[2] > 0) (tPlayer == player ? possible3 : oppPossible3)++; break;
			case 1: if (pos[0] > 0) (tPlayer == player ? possible2 : oppPossible2)++;
				if (pos[0] > 0) (tPlayer == player ? possible2 : oppPossible2)++; break;
			}
			pos = field.rightDiagonalStraight(i, j, *p[tPlayer % 2]);
			switch (pos[1] + 1) {
			case 3: if (pos[0] > 0) (tPlayer == player ? possible4 : oppPossible4)++;
				if (pos[2] > 0) (tPlayer == player ? possible4 : oppPossible4)++; break;
			case 2: if (pos[0] > 0) (tPlayer == player ? possible3 : oppPossible3)++;
				if (pos[2] > 0) (tPlayer == player ? possible3 : oppPossible3)++; break;
			case 1: if (pos[0] > 0) (tPlayer == player ? possible2 : oppPossible2)++;
				if (pos[0] > 0) (tPlayer == player ? possible2 : oppPossible2)++; break;
			}
			pos = field.leftDiagonalStraight(i, j, *p[tPlayer % 2]);
			switch (pos[1] + 1) {
			case 3: if (pos[0] > 0) (tPlayer == player ? possible4 : oppPossible4)++;
				if (pos[2] > 0) (tPlayer == player ? possible4 : oppPossible4)++; break;
			case 2: if (pos[0] > 0) (tPlayer == player ? possible3 : oppPossible3)++;
				if (pos[2] > 0) (tPlayer == player ? possible3 : oppPossible3)++; break;
			case 1: if (pos[0] > 0) (tPlayer == player ? possible2 : oppPossible2)++;
				if (pos[0] > 0) (tPlayer == player ? possible2 : oppPossible2)++; break;
			}
		}

	}
	return posScore + possible2 + possible3 * 4 + possible4 * 10 -
		(oppPosScore + oppPossible2 + oppPossible3 * 4 + oppPossible4 * 10);
}