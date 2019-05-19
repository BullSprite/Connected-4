#include "Project.h"
#include <Conio.h>

Game::Game() {
	setlocale(LC_ALL, "Rus");
	run = true;
}

int Game::execute() {
	HumanPlayer p1(1);
	HumanPlayer p2(2);
	Field field;
	while (run) {
		while (field.getResult() == 0 && field.getTurns() != 0) {
			cout << field;
			cout << "Введите ход игрока " << (((field.getTurns() % 2) == 0) ? "1" : "2") << ": ";
			int turn;
			cin >> turn;
			field.setTurn(--turn, ((field.getTurns() % 2) == 0) ? p1 : p2);
		}
		cout << field;
		if (field.getResult() == MIN)
			cout << "Победил игрок 1" << endl;
		else if (field.getResult() == MAX)
			cout << "Победил игрок 2" << endl;
		else
			cout << "Ничья" << endl;
		_getch();
		exit();
	}
	return 0;
}

void Game::exit() {
	run = false;
}