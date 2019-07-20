#pragma once
#include<Windows.h>
#include "..\Draw\Draw.h"
#include "..\lib\Soil\SOIL.h"
#include "..\Controllers\Controllers.h"
#include <iostream>
#include <fstream>
#include "..\lib\audiere.h"
#define HEIGHT_GAME 600
#define WIDTH_GAME 600
#define WHITE 100
#define BLACK 101
using namespace audiere;
using namespace Controllers;
namespace Game {
	class Field {
	public:
		Field(int *stateGame);
		void draw();
		void mouseMotion(int x,int y);
		void mouse(int button, int state, int ax, int ay);
		void check();
		void newGame();
		void save(std::ofstream *out);
		void load(std::ifstream *in);
		void setMove();
		void randMove();
	private:
		GLuint field,black,white;
		Button bBack;
		int points[15][15];
		int move;
		int sizePoint;
		int *stateGame;
		AudioDevicePtr device; // переменные для воспроизводства звука
		OutputStreamPtr sound;
	};

	class GameForTwo {
	public:
		GameForTwo(int *stateGame);
		virtual void draw();
		void mouseMotion(int x, int y);
		void mouse(int button, int state, int ax, int ay);
		void newGame();
		virtual void save();

		void load(std::ifstream *in);
	protected:
		Field *field;
		int *stateGame;
		Button bSave;
	};

	class GameComputer:public GameForTwo {
	public:
		GameComputer(int *stateGame);
		void draw();
		void save();
	};
}