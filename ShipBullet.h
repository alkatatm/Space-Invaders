#pragma once
#include "Move.h"
#include <iostream>

class SHIPBULLET {
private: int x, y;
public:
	SHIPBULLET(int _x, int _y) : x(_x), y(_y) {}
	int X() { return x; }
	int Y() { return y; }
	void shoot() {
	
		move(x, y); std::cout << " ";
		y--;
		move(x, y); std::cout << "*";
	}
	bool deleteBullet() {
		if (y == 4) 
			return true;
		return false;
	}
};