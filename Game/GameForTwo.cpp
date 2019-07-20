#include "Game.h"
using namespace Game;
GameForTwo::GameForTwo(int *stateGame) {
	field = new Field(stateGame);
	this->stateGame = stateGame;
	bSave.setLocation(50, 33);
	bSave.setSize(151, 49);
	bSave.setTexture((char*)"img/save.png");
}
void GameForTwo::draw() {
	field->draw();
	bSave.draw();
}
void GameForTwo::mouse(int button, int state, int ax, int ay) {
	field->mouse(button, state,  ax,  ay);
	if ((button == GLUT_LEFT_BUTTON) && state == 1) {
		if (bSave.click(ax, HEIGHT_GAME - ay)) {
			this->save();
		}
	}
}
void GameForTwo::mouseMotion(int x, int y) {
	field->mouseMotion(x, y);
}
void GameForTwo::newGame() {
	field->newGame();
}
void GameForTwo::save() {
	std::ofstream out("save.txt");
	out << 2 <<std::endl;
	field->save(&out);
	out.close();
	MessageBox(0, "Игра сохранена", "Рэндзю", MB_OK);
}
void GameForTwo::load(std::ifstream *in) {
	field->load(in);
}