#include "Menu.h"
using namespace Menu;
MainMenu::MainMenu(int *stateGame) {
	texture=SOIL_load_OGL_texture("img/menu.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	this->stateGame = stateGame;
	bWithComputer.setLocation(58,450);
	bWithComputer.setSize(483, 99);
	bWithComputer.setTexture((char*)"img/withComputer.png");

	bForTwo.setLocation(112,300);
	bForTwo.setSize(375,99);
	bForTwo.setTexture((char*)"img/forTwo.png");

	bLoad.setLocation(220,193);
	bLoad.setSize(159,57);
	bLoad.setTexture((char*)"img/bLoad.png");

	bExit.setLocation(233,94);
	bExit.setSize(133,49);
	bExit.setTexture((char*)"img/exit.png");

	gameForTwo = new GameForTwo(stateGame);
	gameComputer = new GameComputer(stateGame);
}
void MainMenu::draw() {
	drawTexture(texture, 0, 0, WIDTH_MENU, HEIGHT_MENU, 1);
	bWithComputer.draw();
	bForTwo.draw();
	bLoad.draw();
	bExit.draw();
}
void MainMenu::mouse(int button, int state, int ax, int ay) {
	if ((button == GLUT_LEFT_BUTTON)&&state==1) {
		if (bExit.click(ax, HEIGHT_MENU - ay)) exit(0);
		if (bForTwo.click(ax, HEIGHT_MENU - ay)) *stateGame = 6;
		if (bWithComputer.click(ax, HEIGHT_MENU - ay)) *stateGame = 5;
		if (bLoad.click(ax, HEIGHT_MENU - ay)) {
			std::cout << "click";
			std::ifstream in("save.txt");
			int n;
			in >> n;
			if (n == 2) {
				gameForTwo->load(&in);
				*stateGame = 3;
			}
			else {
				gameComputer->load(&in);
				*stateGame = 2;
			}
			in.close();
		}
	}
}
GameForTwo* MainMenu::getGameForTwo() {
	return gameForTwo;
}
GameComputer* MainMenu::getGameComputer() {
	return gameComputer;
}