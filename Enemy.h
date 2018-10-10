#pragma once
#include <iostream>
#include "EnemyBullet.h"
#include "Move.h"
class ENEMY{
private: int x, y, pic;
public:
	ENEMY(int _x, int _y, int _pic) : x(_x), y(_y), pic(_pic) {};
	int X() { return x; }
	int Y() { return y; }
	void image() {
		move(x, y); printf("%c", pic);
	}
	void enemyMove() {
		move(x, y); 
		std::cout << " ";
		y++;
		if (y > 32) {
			x = rand() % 71 + 4;
			y = 4;
		}
		image();
	}
	void death() {
		x = rand() % 71 + 4;
		y = 4;
	}
	void aliens() {
		move(x, y);
		std::cout << " ";
		x++;
		image();
		Sleep(100);
	}
};
