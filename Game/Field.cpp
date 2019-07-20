#include "Game.h"

using namespace Game;
using namespace std;
Field::Field(int *stateGame) {
	sizePoint = 28;//������ ����� � ��������
	device = OpenDevice();
	sound = OpenSound(device, "music/click.mp3", false);//�������� ������ �����
	//�������� �������
	field = SOIL_load_OGL_texture("img/field.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	black = SOIL_load_OGL_texture("img/black.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	white = SOIL_load_OGL_texture("img/white.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	//�������� ������ �����
	bBack.setLocation(391,25);
	bBack.setSize(159,57);
	bBack.setTexture((char*)"img/back.png");

	this->stateGame = stateGame;
}
void Field::newGame() {
	//������� ����
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			points[j][i] = 0;
	move = WHITE;
}
void Field::check() {
	//�������� �� ����� ����, ���� ���� 5 ������ � ���, �� ��������� ����
	for (int i=0;i<15;i++)
		for (int j = 0; j < 11; j++) {
			if ((points[j][i] != 0) && (points[j][i] == points[j + 1][i] && points[j][i] == points[j + 2][i] && points[j][i] == points[j + 3][i] && points[j][i] == points[j + 4][i])) {
				if (points[j][i] == WHITE) *stateGame = 8;
				else *stateGame = 7;
			}
			if ((points[i][j] != 0) && (points[i][j] == points[i][j + 1] && points[i][j] == points[i][j + 2] && points[i][j] == points[i][j + 3] && points[i][j] == points[i][j + 4])) {
				if (points[i][j] == WHITE) *stateGame = 8;
				else *stateGame = 7;
			}
			if ((i<11)&&(points[j][i] != 0) && (points[j][i] == points[j + 1][i + 1] && points[j][i] == points[j + 2][i + 2] && points[j][i] == points[j + 3][i + 3] && points[j][i] == points[j + 4][i + 4])) {
				if (points[j][i] == WHITE) *stateGame = 8;
				else *stateGame = 7;
			}
			if ((i>=4)&&(points[i][j] != 0) && (points[i][j] == points[i - 1][j + 1] && points[i][j] == points[i - 2][j + 2] && points[i][j] == points[i - 3][j + 3] && points[i][j] == points[i - 4][j + 4])) {
				if (points[i][j] == WHITE) *stateGame = 8;
				else *stateGame = 7;
			}
		}
}
//����������� ����
//� � � �������� ��������� ���������� ����
//�� ���� ����������� ��������� ��������� ����� � �������� ������, �� ��� �����, ��� ��
//����� ���� ���������
void Field::mouseMotion(int x1,int y1) {
	static int x, y;
	if (x1 != -1 && y1 != -1) { //���� �������� -1,-1 �� ���������� ������ �� ����������� �����������
		x = x1;
		y = y1;
	}
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			if (x <= 91 + i * 30 + 15 && x >= 91 + i * 30 - 15)
				if (y <= 457 - j * 30 + 15 && y >= 457 - j * 30 - 15) {
					if (move == WHITE) drawTexture(white, 91 + i * 30 - (sizePoint/2), HEIGHT_GAME - (457 - j * 30 - (sizePoint / 2)), 91 + i * 30 + (sizePoint / 2), HEIGHT_GAME - (457 - j * 30 + (sizePoint / 2)), 0.8);
					else  drawTexture(black, 91 + i * 30 - (sizePoint / 2), HEIGHT_GAME - (457 - j * 30 - (sizePoint / 2)), 91 + i * 30 + (sizePoint / 2), HEIGHT_GAME - (457 - j * 30 + (sizePoint / 2)), 0.8);
				}
}
//��������� ������
void Field::mouse(int button, int state, int ax, int ay) {
	int x = ax;
	int y = ay;
	if ((button == GLUT_LEFT_BUTTON)&&(state==1)) {
		//��� � ��� ����� ������ ����� � ������� ����� ��������� ���� ����
		//���� ��������� �� ���� �������� ������
		for(int i = 0; i < 15; i++)
			for (int j = 0; j < 15; j++)
				if (x <= 91 + i * 30 + 15 && x >= 91 + i * 30 - 15)
					if (y <= 457 - j * 30 + 15 && y >= 457 - j * 30 - 15) {
						if (move == WHITE) drawTexture(white, 91 + i * 30 - 15, HEIGHT_GAME - (457 - j * 30 - 15), 91 + i * 30 + 15, HEIGHT_GAME - (457 - j * 30 + 15), 0.8);
						else  drawTexture(black, 91 + i * 30 - 15, HEIGHT_GAME - (457 - j * 30 - 15), 91 + i * 30 + 15, HEIGHT_GAME - (457 - j * 30 + 15), 0.8);
						if (points[i][j] == 0) {
							sound->play();
							sound->reset();
							points[i][j] = move;
							//������ ���
							if (move == WHITE) move = BLACK;
							else move = WHITE;
						}
						return;
					}
		//��������� ������� �� ������ �����
		if (bBack.click(ax, HEIGHT_GAME - ay)) *stateGame = 1;
	}
}
//��������� ����
void Field::draw() {
	drawTexture(field, 50, 100, 550, 600, 1);
	mouseMotion(-1, -1);
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			if (points[i][j] != 0) {
				if (points[i][j] == WHITE) drawTexture(white, 91 + i * 30 - (sizePoint / 2), HEIGHT_GAME - (457 - j * 30 - (sizePoint / 2)), 91 + i * 30 + (sizePoint / 2), HEIGHT_GAME - (457 - j * 30 + (sizePoint / 2)), 1);
				else  drawTexture(black, 91 + i * 30 - (sizePoint / 2), HEIGHT_GAME - (457 - j * 30 - (sizePoint / 2)), 91 + i * 30 + (sizePoint / 2), HEIGHT_GAME - (457 - j * 30 + (sizePoint / 2)), 1);
			}

	bBack.draw();
	check();
}
//����������� ����
void Field::save(std::ofstream *out) {
	*out << move << endl;
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			*out << points[i][j] << endl;
}
//�������� ����
void Field::load(std::ifstream *in) {
	*in >> move;
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			*in >> points[i][j];
}
//������� ��� ���� ����������
void Field::setMove() {
	//���� ����� ������
	if (move == BLACK) {
		bool haveBlack=false;
		move = WHITE;
		//��������� ���� �� ������ ����� �� ����
		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 15; j++)
				if (points[i][j] == BLACK) haveBlack = true;
		//���� ���� ������ ��� ��������
		if (!haveBlack) {
			randMove();
			return;
		}
		//���� ����, �� ��� ���� ����� ������������ �� ���
		int count = 0;
		int **moves = (int**)malloc(sizeof(int*)*2);
		moves[0] =(int*) malloc(0);
		moves[1] = (int*)malloc(1);
		//���� ������ �����
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++)
				if (points[i][j] == BLACK) {
					//���� �����, �� ��������� ����� �� �� ����� ��������� ������,
					//���� �� �� ���������� ���� ���
					if ((j > 0)&& points[i][j - 1] == 0) {
						count++;
						moves[0] = (int*)realloc(moves[0], sizeof(int)*count);
						moves[1] = (int*)realloc(moves[1], sizeof(int)*count);
						moves[0][count - 1] = i;
						moves[1][count - 1] = j - 1;
					}
					if ((j < 15 )&& points[i][j + 1] == 0) {
						count++;
						moves[0] = (int*)realloc(moves[0], sizeof(int)*count);
						moves[1] = (int*)realloc(moves[1], sizeof(int)*count);
						moves[0][count - 1] = i;
						moves[1][count - 1] = j + 1;
					}
					if ((i > 0)&& points[i - 1][j] == 0) {
						count++;
						moves[0] = (int*)realloc(moves[0], sizeof(int)*count);
						moves[1] = (int*)realloc(moves[1], sizeof(int)*count);
						moves[0][count - 1] = i-1;
						moves[1][count - 1] = j;
					}
					if ((i < 15 )&& points[i + 1][j] == 0) {
						count++;
						moves[0] = (int*)realloc(moves[0], sizeof(int)*count);
						moves[1] = (int*)realloc(moves[1], sizeof(int)*count);
						moves[0][count - 1] = i + 1;
						moves[1][count - 1] = j;
					}
				}
		}
	
		if (count!=0) {
			//���� ���� ���� �������, �� �������� ���� ��������
			int n = rand() % count;
			points[moves[0][n]][moves[1][n]] = BLACK;
		}
		else {
			//���� ����� ��� ������ ������ ���������
			randMove();
		}
	}
}
void Field::randMove() {
	int i, j;
	i = rand() % 15;
	j = rand() % 15;
	while (points[i][j] != 0) {
		i = rand() % 15;
		j = rand() % 15;
	}
	points[i][j] = BLACK;
}