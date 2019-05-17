#include "Project.h"

Field::Field() {
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 7; j++)
			field[i][j] = 0;
	result = 0;
}

Field::Field(Field & field) {

}

bool Field::checkTurnPossibility(int & turn, Player & player) {
	bool possible = true;
	if (turn < 0 || turn > 7)
		possible = false;
	if (field[turn][0] != 0)
		possible = false;
	if (!possible && player.isHuman()) {
		cout << "¬веден некоректный ход, повторите попытку" << endl;
		cout << "¬ведите номер столбца от 0 до 7: ";
		cin >> turn;
		return checkTurnPossibility(turn, player);
	}
	return possible;
}

int Field::operator[](const int & ind) {

}
