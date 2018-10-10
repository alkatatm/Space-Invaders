#pragma once
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "ShipBullet.h"
#include "Move.h"
#include "Enemy.h"
#define LEFT 75
#define RIGHT 77


class SHIP {
private: int x, y, lives;
public:
	SHIP(int _x, int _y, int _lives) : x(_x), y(_y), lives(_lives) {}
	int X() { return x; }
	int Y() { return y; }
	int LIVES() { return lives; }
	void Lives() { lives--; }
	void moving() {
		if (_kbhit()) {
			char input = _getch();
			deletePast();
			if (input == LEFT && x>3) x--; //x>3 to not get out of left border
			if (input == RIGHT && x + 6 < 77) x++; //x + 6 < 77 to not get out of right border ----
			if (input == 'a') lives--;
			update();
			printLives();
		}
	}
	void deletePast() {
		move(x, y); std::cout << "     ";
		move(x, y + 1); std::cout << "      ";
	}
	void update() {
		move(x, y); std::printf(" %c%c%c", 220, 219, 220);
		move(x, y + 1); std::printf("%c%c%c%c%c", 223, 223, 223, 223, 223);
	}

	void printLives() {
		move(64, 2); std::cout << "Lives: ";
		move(70, 2); std::cout << "       ";
		for (int i = 0; i < lives; i++) {
			move(70 + i, 2); std::printf("%c  ", 158);
		}
	
	}

	void death() {
		if (lives == 0) {
			deletePast();
			move(x, y);	std::cout << "   XXX   ";
			move(x, y+1);	std::cout << "  XXXXX  ";
			Sleep(200);

			deletePast();
			move(x, y);	std::cout << " X X ";
			move(x, y + 1);	std::cout << " X X X ";
			Sleep(200);
			deletePast();
			
			lives--;
			printLives();
		}
	
	}
};
