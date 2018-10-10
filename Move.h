#pragma once
#include <windows.h>

static inline void move(int x, int y) {
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(hCon, Pos);
}