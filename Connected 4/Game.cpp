#include "Project.h"
#include <Conio.h>

Game::Game() {
	setlocale(LC_ALL, "Rus");
	run = true;
}

int Game::execute() {
	HumanPlayer p1(1);
	AIPlayer p2(2);
	p2.setMaxDepth(1);
	Field field;
	while (run) {
		int aiTurn = -1;
		while (field.getResult() == DEFAULT && field.getTurns() != 0) {
			if (field.getTurns() % 2 == 0) {
				cout << field;
				if (aiTurn != -1)
					cout << "����� 2 ������ ���: " << aiTurn << endl;
				cout << "������� ��� ������ " << "1: ";
				int turn;
				cin >> turn;
				field.setTurn(--turn, p1);
			}
			else {
				Player ** players = new Player*[2];
				players[0] = &p1;
				players[1] = &p2;
				aiTurn = p2.runMiniMax(field, players, 1, 1);
				field.setTurn(aiTurn, p2);
			}

		}
		cout << field;
		if (field.getResult() == 0)
			cout << "�����" << endl;
		else if (field.getTurns() % 2 != 0)
			cout << "������� ����� 1" << endl;
		else 
			cout << "������� ����� 2" << endl;
		_getch();
		exit();
	}
	return 0;
}

void Game::exit() {
	run = false;
}