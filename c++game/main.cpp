#include <iostream>
#include <conio.h>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void Draw() {
	system("cls");
	
	// Draw the top wall
	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;
	
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0)
				cout << "#";
			else if (i == y && j == x)
				cout << "O";
			else if (i == fruitX && j == fruitY)
				cout << "F";
			else if (j == width - 1)
				cout << "#" << endl;
			else 
				cout << " ";
			
		}

	}
	
	// Draw the bottom wall
	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;
}

void Input() {
	if (_kbhit()) {
		switch(_getch()) {
			case 'a':
				dir = LEFT;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 'w':
				dir = UP;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'x':
				gameOver = true;
				break;
		}
	}
}

void Logic() {

}

int main() {
	Setup();
	while(!gameOver) {
		Draw();
		Input();
		Logic();
	}
	
	
	return 0;
}

