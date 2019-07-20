#include "Draw.h"
#include <Windows.h>
#include <iostream>
//функция отрисовки текстур
void drawTexture(GLuint texture, int x, int y, int x1, int y1,float a) {
	glColor4f(1, 1, 1,a);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 1); glVertex2f(x, y1);
	glTexCoord2f(1, 1); glVertex2f(x1, y1);
	glTexCoord2f(1, 0); glVertex2f(x1, y);
	glTexCoord2f(0, 0); glVertex2f(x, y);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void centerOnScreen(int width, int height) {
	//центрируем окно на экране
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	glutPositionWindow((desktop.right - width) / 2, (desktop.bottom - height) / 2);
}
void resizeScreen(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutReshapeWindow(width, height);
}
void drawLoad(int x,int y,int x2,int y2) {
	static GLuint load = SOIL_load_OGL_texture("img/load.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	glClearColor(0.83, 0.83, 0.83, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawTexture(load, x, y, x2, y2, 1);
	glutSwapBuffers();
}