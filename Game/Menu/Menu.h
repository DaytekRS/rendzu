#pragma once
#include <iostream>
#include <fstream>
#include "../../Controllers/Controllers.h"
#include "../../lib/Soil/SOIL.h"
#include "../../lib/gl/glut.h"
#include "../../Draw/Draw.h"
#include "../Game.h"
#define WIDTH_MENU 600
#define HEIGHT_MENU 600
using namespace Game;
using namespace Controllers;
namespace Menu {
	class MainMenu {
		public:
			MainMenu(int *stateGame);
			void draw();
			void mouse(int button, int state, int ax, int ay);
			GameForTwo* getGameForTwo();
			GameComputer* getGameComputer();
		private:
			Button bWithComputer, bForTwo, bExit, bLoad;
			GLuint texture;
			int *stateGame;
			GameForTwo *gameForTwo;
			GameComputer *gameComputer;
	};
}