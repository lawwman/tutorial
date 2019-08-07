#include <iostream>
#include <ctime>
#include <conio.h>
#include <Windows.h>

using namespace std;

bool gameOver;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void setFruitLocation() {
	fruitX = (rand() % (width - 4)) + 2;
	fruitY = (rand() % (height - 4)) + 2;
}

void Setup() {
	srand(time(NULL));
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	setFruitLocation();
	score = 0;
}

void Draw() {
	system("cls");
	
	// Draw the top wall
	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;
	
	
	
	for (int i = 0; i < height; i++) {
		int print_tail = 0;
		for (int j = 0; j < width; j++) {
			if (j == 0)
				cout << "#";
			else if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else if (j == width - 1)
				cout << "#" << endl;
			else {
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print_tail++;
					}
				}
				if (print_tail == 0)
				cout << " ";
			}
			if (print_tail > 0) print_tail--;
		}

	}
	
	// Draw the bottom wall
	for (int i = 0; i < width; i++)
		cout << "#";
	cout << endl;
	
	cout << "Score: " << score << endl;
	cout << x << " " << y << endl;
	cout << fruitX << " " << fruitY << endl;
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
	// Store old tailX[0] and tailY[0] values
	int prevX = tailX[0];
	int prevY = tailY[0];
	tailX[0] = x; // update tailX[0]
	tailY[0] = y; // update tailY[0]
	
	for (int i = 1; i < nTail; i++) {
		int tempX, tempY;
		tempX = tailX[i];
		tempY = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = tempX;
		prevY = tempY;
		
	}
	
	switch(dir) {
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		default:
			break;
	}
	
	if (x < 0 || x >= width || y < 0 || y >= height) gameOver = true;
	
	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) gameOver = true;
	}
	
	if (x == fruitX && y == fruitY) {
		score ++;
		nTail ++;
		setFruitLocation();
	}
}

int main() {
	Setup();
	while(!gameOver) {
		Draw();
		Input();
		Logic();
		Sleep(50);
	}
	
	
	return 0;
}

