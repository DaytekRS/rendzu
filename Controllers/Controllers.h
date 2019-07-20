#pragma once
#include "../lib/gl/glut.h"
#include "../lib/Soil/SOIL.h"
namespace Controllers {
	//����� ��� ������
	class Button
	{
	public:
		void setWidth(int n);
		void setHeight(int n);
		void setSize(int width, int height);
		void setX(int x);
		void setY(int y);
		void setLocation(int x, int y);
		int getWidth();
		int getHeigth();
		int getX();
		int getY();
		void setTexture(char* patch);
		void draw();
		bool click(int x, int y); //���������� ���������� �����, ���� �������� �� ������, �� ��� ������
	private:
		int width, height;
		int x, y;
		GLuint texture;
	};
}

