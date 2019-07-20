#include "Controllers.h"
#include "../Draw/Draw.h"
void Controllers::Button::setWidth(int n)
{
	this->width = n;
}
void Controllers::Button::setHeight(int n)
{
	this->height = n;
}
void Controllers::Button::setSize(int width, int height)
{
	this->width = width;
	this->height = height;
}
void Controllers::Button::setX(int x)
{
	this->x = x;
}
void Controllers::Button::setY(int y)
{
	this->y = y;
}
void Controllers::Button::setLocation(int x, int y)
{
	this->x = x;
	this->y = y;
}
int Controllers::Button::getWidth()
{
	return this->width;
}
int Controllers::Button::getHeigth()
{
	return this->height;
}
int Controllers::Button::getX()
{
	return this->x;
}
int Controllers::Button::getY()
{
	return this->y;
}
void Controllers::Button::setTexture(char* patch) {
	this->texture=SOIL_load_OGL_texture(patch, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
}
void Controllers::Button::draw() {
	drawTexture(this->texture, this->x, this->y, this->x + this->width, this->y + this->height,1);
}

//передаются координаты клика, если попадают на кпопку, то она нажата
bool Controllers::Button::click(int x, int y) {
	if (this->x < x&&x < this->x + this->width)
		if (this->y < y&&y < this->y + this->height) return true;
	return false;
}

