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
	int * tmp = horizontalStraight(i1, i2, player);
	delete(tmp);
	if (result != DEFAULT) return;
	tmp = leftDiagonalStraight(i1, i2, player);
	delete(tmp);
	if (result != DEFAULT) return;
	tmp = rightDiagonalStraight(i1, i2, player);
	delete(tmp);
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
		changeResult(player);
	return straight;
}

int * Field::horizontalStraight(const int & i1, const int & i2, Player & player) {
	int p = player.getPlayerTurn();
	int straight = 0;
	int spacesBefore = 0;
	int sameBefore = 0;
	int spacesAfter = 0;
	int start = i2 - 3 < 0 ? 0 : i2 - 3;
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
		changeResult(player);
	else {
		for (int i = i2 + 1; i < end; i++) {
			if (field[i1][i] == p) {
				if (spacesAfter == 0) {
					straight++;
					if (straight == 4) {
						changeResult(player);
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
	int step = 0;
	int startI = i1, startJ = i2;
	while (startI > 0 && startJ > 0 && step < 3) {
		startI--; startJ--; step++;
	}
	int endI = i1, endJ = i2;
	step = 0;
	while (endI < 5 && endJ < 6 && step < 3) {
		endI++; endJ++; step++;
	}
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
		changeResult(player);
	else {
		j = i2 + 1;
		for (int i = i1 + 1; i < endI; i++) {
			if (field[i][j] == p) {
				if (spacesAfter == 0) {
					straight++;
					if (straight == 4) {
						changeResult(player);
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
	int step = 0;
	int startI = i1, startJ = i2;
	while (startI > 0 && startJ < 6 && step < 3) {
		startI--; startJ++; step++;
	}
	step = 0;
	int endI = i1, endJ = i2;
	while (endI < 5 && endJ > 0 && step < 3) {
		endI++; endJ--; step++;
	}
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
		changeResult(player);
	else {
		j = i2 - 1;
		for (int i = i1 + 1; i < endI; i++) {
			if (field[i][j] == p) {
				if (spacesAfter == 0) {
					straight++;
					if (straight == 4) {
						changeResult(player);
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

bool Field::checkTurnPossibility(int & turn) {
	bool possible = true;
	if (turn < 0 || turn > 7)
		possible = false;
	if (field[5][turn] != 0)
		possible = false;
	return possible;
}

void Field::setTurn(int j, Player & player) {
	checkTurnPossibility(j);
	int i = 5;
	while (field[i][j] == 0 && i > -1) i--; i++;
	field[i][j] = player.getPlayerTurn();
	turnsLimit--;
	checkResult(i, j, player);
}

void Field::changeResult(Player & player) {
	result = player.isHuman() ? MIN : MAX;
}

int* Field::operator[](const int & ind) {
	return field[ind];
}

ostream& operator << (ostream& out, Field & field) {
	system("CLS");
	for (int i = 5; i > -1; i--) {
		//out << "_______________" << endl << "|";
		for (int j = 0; j < 7; j++)
			out << (field[i][j] == 1 ? "X" : field[i][j] == 2 ? "O" : " ") << "|";
		out << "\t" << i + 1 << endl;
	}

	//out << "______________" << endl << " ";
	for (int i = 0; i < 7; i++)
		out << i + 1 << " ";
	out << endl;

	return out;
}

