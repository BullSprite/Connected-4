#ifndef _FIELD_H
#define _FIELD_H

#include "Project.h"

class Field {
private:
	int field[6][7];
	int result;

public:
	Field();
	Field(Field &);
	bool checkTurnPossibility(int &, Player &);

	int& operator [](const int&);
	int operator [](const int&);

};
#endif // !_FIELD_H
