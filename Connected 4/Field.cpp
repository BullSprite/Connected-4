#include "Field.h"
#include <conio.h>
Field::Field() {
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 7; j++)
			field[i][j] = 0;
	result = DEFAULT;
	turnsLimit = 42;
}

Field::Field(Field & field) {
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 8; j++)
			this->field[i][j] = field[i][j];
	result = field.getResult();
	turnsLimit = field.getTurns();
}

int Field::getTurns() {
	return turnsLimit;
}

int Field::getResult() {
	return result;
}

void Field::checkResult(const int & i1, const int & i2, Player & player) {
	verticalStraight(i1, i2, player);
	if (result != DEFAULT) return;
	horizontalStraight(i1, i2, player);
	if (result != DEFAULT) return;
	leftDiagonalStraight(i1, i2, player);
	if (result != DEFAULT) return;
	rightDiagonalStraight(i1, i2, player);
	if (result != DEFAULT) return;
	if (turnsLimit == 0) result = DRAW;
}

int Field::verticalStraight(const int & i1, const int & i2, Player & player) {
	int end = i1 - 4 < -1 ? -1 : i1 - 4;
	int p = player.getPlayerTurn();
	int straight = 0;
	for (int i = i1; i > end; i--)
		if (field[i][i2] == p)
			straight++;
		else
			break;
	if (straight == 4)
		result = player.isHuman() ? MIN : MAX;
	return straight;
}

int * Field::horizontalStraight(const int & i1, const int & i2, Player & player) {
	int p = player.getPlayerTurn();
	int straight = 0;
	int spacesBefore = 0;
	int sameBefore = 0;
	int spacesAfter = 0;
	int start = i2 - 4 < 0 ? 0 : i2 - 4;
	int end = i2 + 4 > 7 ? 7 : i2 + 4;
	for (int i = start; i < i2; i++) {
		if (field[i1][i] == p) {
			sameBefore++;
			straight++;
		}
		else if (field[i1][i] == 0) {
			spacesBefore++;
			straight = 0;
		}
		else {
			sameBefore = 0;
			spacesBefore = 0;
			straight = 0;
		}
	}
	straight++;
	if (straight == 4)
		result = result = player.isHuman() ? MIN : MAX;
	else {
		for (int i = i2 + 1; i < end; i++) {
			if (field[i1][i] == p) {
				if (spacesAfter == 0) {
					straight++;
					if (straight == 4) {
						result = player.isHuman() ? MIN : MAX;
						break;
					}
				}
				else {
					break;
				}
			}
			else if (field[i1][i] == 0) {
				spacesAfter++;
			}
			else {
				break;
			}
		}
	}
	return new int[3]{ spacesBefore, sameBefore, spacesAfter };
}

int * Field::leftDiagonalStraight(const int & i1, const int & i2, Player & player) {
	int p = player.getPlayerTurn();
	int straight = 0;
	int spacesBefore = 0;
	int sameBefore = 0;
	int spacesAfter = 0;
	int delta = 0;
	if (i1-4 < i2 - 4) {
		delta = i1 - 4 < 0 ? i1 : 4;
	}
	else {
		delta = i2 - 4 < 0 ? i2 : 4;
	}
	int startI = i1 - delta;
	int startJ = i2 - delta;
	if ((7 - i1) > (8 - i2)) {
		delta = i1 + 4 > 7 ? 7 - i1 : 4;
	}
	else {
		delta = i2 + 4 > 8 ? 8 - i2 : 4;
	}
	int endI = i1 + delta;
	int endJ = i2 + delta;
	int j = startJ;
	for (int i = startI; i < i1; i++) {
		if (field[i][j] == p) {
			sameBefore++;
			straight++;
		}
		else if (field[i][j] == 0) {
			spacesBefore++;
			straight = 0;
		}
		else {
			sameBefore = 0;
			spacesBefore = 0;
			straight = 0;
		}
		j++;
	}
	straight++;
	if (straight == 4)
		result = result = player.isHuman() ? MIN : MAX;
	else {
		j = i2 + 1;
		for (int i = i1 + 1; i < endI; i++) {
			if (field[i][j] == p) {
				if (spacesAfter == 0) {
					straight++;
					if (straight == 4) {
						result = player.isHuman() ? MIN : MAX;
						break;
					}
				}
				else {
					break;
				}
			}
			else if (field[i][j] == 0) {
				spacesAfter++;
			}
			else {
				break;
			}
			j++;
		}
	}
	return new int[3]{ spacesBefore, sameBefore, spacesAfter };
}

int * Field::rightDiagonalStraight(const int & i1, const int & i2, Player & player) {
	int p = player.getPlayerTurn();
	int straight = 0;
	int spacesBefore = 0;
	int sameBefore = 0;
	int spacesAfter = 0;
	int delta = 0;
	if (i1 < (7 - i2)) {
		delta = i1 - 4 < 0 ? i1 : 4;
	}
	else {
		delta = i2 + 4 > 7 ? (7 - i2) : 4;
	}
	int startI = i1 - delta;
	int startJ = i2 + delta;
	if ((7 - i1 + 4) < i2 - 4) {
		delta = i1 + 4 > 7 ? 7 - i1 : 4;
	}
	else {
		delta = i2 - 4 < -1 ? -1 + i2 : 4;
	}
	int endI = i1 + delta;
	int endJ = i2 - delta;
	int j = startJ;
	for (int i = startI; i < i1; i++) {
		if (field[i][j] == p) {
			sameBefore++;
			straight++;
		}
		else if (field[i][j] == 0) {
			spacesBefore++;
			straight = 0;
		}
		else {
			sameBefore = 0;
			spacesBefore = 0;
			straight = 0;
		}
		j--;
	}
	straight++;
	if (straight == 4)
		result = result = player.isHuman() ? MIN : MAX;
	else {
		j = i2 - 1;
		for (int i = i1 + 1; i < endI; i++) {
			if (field[i][j] == p) {
				if (spacesAfter == 0) {
					straight++;
					if (straight == 4) {
						result = player.isHuman() ? MIN : MAX;
						break;
					}
				}
				else {
					break;
				}
			}
			else if (field[i][j] == 0) {
				spacesAfter++;
			}
			else {
				break;
			}
			j--;
		}
	}
	return new int[3]{ spacesBefore, sameBefore, spacesAfter };
}

bool Field::checkTurnPossibility(int & turn, Player & player) {
	bool possible = true;
	if (turn < 0 || turn > 7)
		possible = false;
	if (field[5][turn] != 0)
		possible = false;
	if (!possible && player.isHuman()) {
		cout << "¬веден некоректный ход, повторите попытку" << endl;
		cout << "¬ведите номер столбца от 1 до 7: ";
		cin >> turn;
		return checkTurnPossibility(--turn, player);
	}
	return possible;
}

void Field::setTurn(int j, Player & player) {
	checkTurnPossibility(j, player);
	int i = 5;
	while (field[i][j] == 0) i--; i++;
	field[i][j] = player.getPlayerTurn();
	turnsLimit--;
	checkResult(i, j, player);
}

int* Field::operator[](const int & ind) {
	return field[ind];
}

ostream& operator << (ostream& out, Field & field) {
	system("CLS");
	for (int i = 5; i > -1; i--) {
		out << "***************" << endl << "*";
		for (int j = 0; j < 7; j++)
			out << (field[i][j] == 1 ? "X" : field[i][j] == 2 ? "O" : " ") << "*";
		out << "\t" << i + 1 << endl;
	}

	out << "***************" << endl << " ";
	for (int i = 0; i < 7; i++)
		out << i + 1 << " ";
	out << endl;
	return out;
}