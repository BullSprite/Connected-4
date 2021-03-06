#ifndef _FIELD_H
#define _FIELD_H

#include "Project.h"
#include <iostream>

using namespace std;

class Field {
private:
	int field[6][7];
	int result;
	int turnsLimit;
	int verticalStraight(const int &, const int &, Player &);
	int* horizontalStraight(const int &, const int &, Player&);
	int* leftDiagonalStraight(const int &, const int &, Player &);
	int* rightDiagonalStraight(const int &, const int &, Player &);

public:
	friend class AIPlayer;
	Field();
	Field(Field &);
	bool checkTurnPossibility(int &);
	int getResult();
	int getTurns();
	void checkResult(const int &, const int &, Player &);
	void setTurn(int, Player &);
	void changeResult(Player &);

	int* operator [](const int&);
	friend ostream & operator << (ostream&, Field&);
};
#endif // !_FIELD_H
