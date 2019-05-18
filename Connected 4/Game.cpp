#include "Game.h"
#include "Project.h"

Game::Game() {
	run = true;
}

int Game::execute() {
	HumanPlayer p1(1);
	HumanPlayer p2(2);
	while (run);
	return 0;
}

void Game::exit() {
	run = false;
}