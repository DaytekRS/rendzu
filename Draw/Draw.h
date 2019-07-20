#pragma once

#include "..\lib\gl\glut.h"
#include "..\lib\Soil\SOIL.h"
void drawTexture(GLuint texture, int x, int y, int x1, int y1,float a);
void centerOnScreen(int width, int height);
void resizeScreen(int width, int height);
void drawLoad(int x, int y, int x2, int y2);