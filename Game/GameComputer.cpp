#include"Game.h"

using namespace Game;
void GameComputer::draw() {
	GameForTwo::draw();
	field->setMove();
}
GameComputer::GameComputer(int* stateGame):GameForTwo(stateGame) {
}
void GameComputer::save() {
	std::ofstream out("save.txt");
	out << 1 << std::endl;
	field->save(&out);
	out.close();
	MessageBox(0, "Игра сохранена", "Рэндзю", MB_OK);
}