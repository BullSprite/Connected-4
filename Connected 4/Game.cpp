#include "Project.h"
#include <Conio.h>
#include <string>

int tryInputInt() {
	int tmp = - 1000;
	string t;
	try {
		getline(cin, t);
		if (t.size() > 1 || t.size() < 0)
			throw -1;
		tmp = t[0] - '0';
		if (tmp < 0 || tmp > 9)
			throw -1;
		return tmp;
	}
	catch (std::ios_base::failure &fail) {
		cin.clear();
		cin.sync();
		return -1000;
	}
	catch (int i) {
		cin.clear();
		cin.sync();
		return -1000;
	}
}

Game::Game() {
	setlocale(LC_ALL, "Rus");
	run = true;
}

int Game::execute() {
	Field field;
	Player * players[2];
	cin.exceptions(std::istream::failbit);

	cout << "������� 1, ���� ������ ������� � ��������� ��� 2, ���� ������ ������� � �����������" << endl;
	int t = tryInputInt();
	while (t < 1 || t > 2) {
		cout << "�� ����� �������� �����, ��������� �������!" << endl;
		t = tryInputInt();
	}
	if (t == 1) {
		players[0] = &HumanPlayer(1);
		players[1] = &HumanPlayer(2);
	}
	else {
		cout << "������� ��������� ���������� �� 0 �� 4" << endl;
		int d = tryInputInt();
		while (d < 0 || d > 4) {
			cout << "�� ����� �������� �����, ��������� �������!" << endl;
			d = tryInputInt();
		}
		cout << "������� 1, ���� �� ������ ������ 1-� ��� 2, ��� ������ ����� ���������" << endl;
		t = tryInputInt();
		while (t < 1 || t > 2) {
			cout << "�� ����� �������� �����, ��������� �������!" << endl;
			t = tryInputInt();
		}
		if (t == 1) {
			players[0] = &HumanPlayer(1);
			players[1] = &AIPlayer(2, d);
		}
		else {
			players[0] = &AIPlayer(1, d);
			players[1] = &HumanPlayer(2);
		}
	}



	t = 0;
	while (run) {
		int pTurn = -1;
		while (field.getResult() == DEFAULT && field.getTurns() != 0) {
			if (players[t]->isHuman()) {
				cout << field;
				if (pTurn != -1)
					cout << "����� " << players[!t]->getPlayerTurn() << " ������ ���: " << pTurn + 1 << endl;
				cout << "������� ��� ������ " << players[t]->getPlayerTurn() << ": ";
				int turn = tryInputInt();
				while (!field.checkTurnPossibility(--turn))
				{
					cout << "������ ����������� ���, ��������� �������:";
					turn = tryInputInt();
				}
				field.setTurn(turn, *players[t]);
				pTurn = turn;
			}
			else {

				pTurn = (static_cast<AIPlayer*>(players[t]))->runMiniMax(field, players, 1, 0);
				field.setTurn(pTurn, *players[t]);
			}
			t = !t;
		}

		cout << field;

		if (players[0]->isHuman() == players[1]->isHuman()) {
			if (field.getResult() == DRAW)
				cout << "�����" << endl;
			else cout << "������� ����� " << (*players[!t]).getPlayerTurn();
			return 0;
		}

		if (field.getResult() == DRAW)
			cout << "�����" << endl;
		else if (field.getResult() == MIN)
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