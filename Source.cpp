#include <iostream>
#include <Windows.h>
#include "Game\Game.h"
#include "lib\gl\glut.h"
#include "lib\Soil\SOIL.h"
#include "lib\audiere.h"
#include "Draw\Draw.h"
#include "Game\Menu\Menu.h"
#include<ctime>
using namespace std;
using namespace Game;
using namespace audiere;
using namespace Menu;
#define WIDTH 600
#define HEIGHT 600
#define LOAD 0
#define MENU 1
#define GAME_WITH_COMPUTER 2
#define GAME_FOR_TWO 3
#define EXIT 4
#define LOAD_GAME_WITH_COMPUTER 5
#define LOAD_GAME_FOR_TWO 6
#define BLACK_WIN 7
#define WHITE_WIN 8
int stateGame;
GLuint winBlack, winWhite;
MainMenu *mainMenu;
AudioDevicePtr device; // переменные дл€ воспроизводства звука
OutputStreamPtr sound;
//загрузка текстур
void newGame() {
	winBlack = SOIL_load_OGL_texture("img/blackWin.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	winWhite = SOIL_load_OGL_texture("img/whiteWin.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}
void timer(int value) {
	glutPostRedisplay(); //  обновить окно
	glutTimerFunc(1, timer, 0);
}
//инициализваци€ окна
void initialize() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIDTH, 0, HEIGHT, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//рисование игры
void draw() {
	glClearColor(0.83, 0.83, 0.83, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//смотритс€ текущий статус игры и отприсоваетс€ именно он
	switch (stateGame)
	{
	case(LOAD):
		drawLoad(0, 0, WIDTH, HEIGHT);
		device = OpenDevice();
		sound = OpenSound(device, "music/music.mp3", false);
		sound->setRepeat(true);
		sound->play();
		mainMenu = new MainMenu(&stateGame);
		newGame();
		stateGame = MENU;
		break;
	case (MENU):
		mainMenu->draw();
		break;
	case (LOAD_GAME_WITH_COMPUTER):
		drawLoad(0, 0, WIDTH, HEIGHT);
		mainMenu->getGameComputer()->newGame();
		stateGame = GAME_WITH_COMPUTER;
		break;
	case (LOAD_GAME_FOR_TWO):
		drawLoad(0, 0, WIDTH, HEIGHT);
		mainMenu->getGameForTwo()->newGame();
		stateGame = GAME_FOR_TWO;
		break;
	case(GAME_WITH_COMPUTER):
		mainMenu->getGameComputer()->draw();
		break;
	case(GAME_FOR_TWO):
		mainMenu->getGameForTwo()->draw();
		break;
	case (BLACK_WIN):
		drawTexture(winBlack, 0, 0, WIDTH, HEIGHT, 1);
		break;
	case (WHITE_WIN):
		drawTexture(winWhite, 0, 0, WIDTH, HEIGHT, 1);
		break;
	}
	glutSwapBuffers();
}
//отслеживает перемещение мыши поэкрану
void mouseMotion(int x , int y) {
	//cout << "x " << x << " y " << y << endl;
	switch (stateGame)
	{
	case (MENU):
		break;
	case (GAME_FOR_TWO):
		mainMenu->getGameForTwo()->mouseMotion(x, y);
		break;
	case(GAME_WITH_COMPUTER):
		mainMenu->getGameComputer()->mouseMotion(x, y);
		break;
	default:
		break;
	}
	

}
//отслеживает клики мыши
void mouse(int button, int state, int ax, int ay) {
	switch (stateGame)
	{
	case(MENU):
		mainMenu->mouse(button, state, ax, ay);
		break;
	case(GAME_FOR_TWO):
		mainMenu->getGameForTwo()->mouse(button, state, ax, ay);
		break;
	case(GAME_WITH_COMPUTER):
		mainMenu->getGameComputer()->mouse(button, state, ax, ay);
		break;
	case (BLACK_WIN):
	case (WHITE_WIN):
		if (state == 1)
			stateGame = MENU;
			break;
	}
}
void main(int argc, char** argv) {
	srand(time(0));
	stateGame = LOAD;
	glutInit(&argc, argv);
	glutInitWindowSize(WIDTH, HEIGHT);
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	glutInitWindowPosition((desktop.right - WIDTH) / 2, (desktop.bottom - HEIGHT) / 2);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("–эндзю");
	initialize();
	glutDisplayFunc(draw);
	drawLoad(0, 0, WIDTH, HEIGHT);

	glutMouseFunc(mouse);
	glutTimerFunc(1, timer, 0);
	glutPassiveMotionFunc(mouseMotion);

	glutMainLoop();
}