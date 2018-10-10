#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <list>
#include "Ship.h"
#include "Enemy.h"
#include "Move.h"
#include "ShipBullet.h"
void RemoveBlink() { //removes the blinking underscore
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO s;
	s.dwSize = 2;
	s.bVisible = FALSE;

	SetConsoleCursorInfo(hCon, &s);
}

//Create the border to set the game
void border() {
	//X-axis border
	for (int i = 2; i < 78; i++) {
		move(i, 3); printf("%c", 205);
		move(i, 33); printf("%c", 205);
	}
	//Y-axis border
	for (int i = 4; i < 33; i++) {
		move(2, i); printf("%c", 186);
		move(77, i); printf("%c", 186);
	}

	//create the corners
	move(2, 3); printf("%c", 201);
	move(2, 33); printf("%c", 200);
	move(77, 3); printf("%c", 187);
	move(77, 33); printf("%c", 188);
}

int main() {
	RemoveBlink(); //remove the blinking underscore
	border(); //create border
	SHIP N(33, 31,3); //position player ship
	N.update(); //create player ship drawing
	N.printLives(); //inititate lives

	//ENEMY level1(10,4,158);------------------

	//Enemy constructor
	std::list<ENEMY*> level;
	std::list<ENEMY*>::iterator spawn;
	for (int i = 0; i < 5; i++) {//create # of enemies
		level.push_back(new ENEMY(rand() % 75 + 3, rand() % 5 + 4,158));
	}

	//Ship constructor
	std::list<SHIPBULLET*> B;
	std::list<SHIPBULLET*>::iterator bullet;

	bool gameOver = false; //loop the game
	int score = 0; // score
	int movement = 0; //enemy speed limiter

	while (!gameOver) { //loop game
		move(4, 2);

		std::cout << "Score: " << score;

		if (_kbhit()) { //if keyboard hit
			char hit = _getch(); //get the character keyboard hit
			if (hit == 'x') // 'x' to shoot
				B.push_back(new SHIPBULLET(N.X() + 2, N.Y() - 1));
		}

		//create and delete the shoot nodes
		for (bullet = B.begin(); bullet != B.end(); bullet++) {
			(*bullet)->shoot();
			if ((*bullet)->deleteBullet()) { 
				move((*bullet)->X(), (*bullet)->Y());
				std::cout << " ";
				delete(*bullet);
				bullet = B.erase(bullet);
				break;
			}
		}
		//level1.enemyMove();
		
		//move the enemies
		for (spawn = level.begin(); spawn != level.end(); spawn++) {
			movement++;
			if (movement == 4) {
				(*spawn)->enemyMove();
				movement = 0;
			}
			//(*spawn)->coll(N, level);----

			//collsion with ship
			if ((*spawn)->X() >= N.X() && (*spawn)->X() < N.X() + 5 && (*spawn)->Y() >= N.Y() && (*spawn)->Y() <= N.Y() + 2) {
				N.Lives();
				N.printLives();
				(*spawn)->death();
			}
		}
		//
		for (spawn = level.begin(); spawn != level.end(); spawn++){
			for (bullet = B.begin(); bullet != B.end(); bullet++) {
				if ((*spawn)->X() == (*bullet)->X() && ((*spawn)->Y() + 1 == (*bullet)->Y() || (*spawn)->Y() == (*bullet)->Y())) {
					move((*bullet)->X(), (*bullet)->Y());
					std::cout << " ";
					delete(*bullet);
					bullet = B.erase(bullet);

					level.push_back(new ENEMY(rand() % 75 + 3, 4, 158));
					move((*spawn)->X(), (*spawn)->Y());
					std::cout << " ";
					delete(*spawn);
					spawn = level.erase(spawn);

					score += 2;
					break;
				}
			}
		}
		//coll(N,level1);
		if (N.LIVES() == 0) {
			N.death();
			break;
		}
		N.moving();
		Sleep(30);
	}
	system("cls");
	std::cout << "GAME OVER!\nSCORE IS " << score;
	return 0;
}