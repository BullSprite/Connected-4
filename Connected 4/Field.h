#ifndef _FIELD_H
#define _FIELD_H

#include "Player.h"

class Field {
private:
	int field[6][7];
	int result;
	int turnsLimit;

public:
	Field();
	Field(Field &);
	bool checkTurnPossibility(int &, Player &);
	int getResult();
	int getTurns();
	void checkResult(const int &, const int &, Player &);
	int verticalStraight(const int &, const int &, Player &);
	int* horizontalStraight(const int &, const int &, Player&);
	int* leftDiagonalStraight(const int &, const int &, Player &);
	int* rightDiagonalStraight(const int &, const int &, Player &);
	void setTurn(int &, Player &);

	int* operator [](const int&);
	friend ostream& operator << (ostream&, Field&);
};
#endif // !_FIELD_H
