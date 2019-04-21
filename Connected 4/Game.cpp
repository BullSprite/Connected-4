#include "Game.h"

Game::Game() {
	run = true;
}

int Game::execute() {
	while (run);
	return 0;
}

void Game::exit() {
	run = false;
}