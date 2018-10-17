#include <iostream>
#include <chrono>
#include <thread>
#include <time.h>       //for rand
#define xAxis 5
#define yAxis 4

int main() {
	//gameboard
	char game[yAxis][xAxis] = {
	' ',' ',' ',' ',' ',
	' ',' ',' ',' ',' ',
	' ',' ',' ',' ',' ',
	' ',' ','X',' ',' '
	};

	bool gameLoop = true;//loop game
	bool left = true;//ship moves left till reach end
	bool right = false;//ship moves right till reach end
	bool bulletRelease = false; //keep one bullet in the board at a time
	int bulletTime = rand() % 20;//randomly generate when the bullet is on board
	srand(time(NULL)); // initialize random seed:
	int moveShip = 2; //Position of ship
	int moveBullet = 2; //Position of bullet
	int moveXBullet = 0; //Save position of where the ship was when bullet was shot

	//Keep the game going
	while (gameLoop) {
		//clear previous position
		game[yAxis-1][moveShip] = ' ';
		
		//Move Ship 'X' left and right
		if (left == true) {
			moveShip--;
			if (moveShip == -1) {
				left = false;
				right = true;
			}
		}
		if (right == true) {
			moveShip++;
			if (moveShip == 4) {
				left = true;
				right = false;
			}		
		}
		//display ship in gameboard
		game[yAxis - 1][moveShip] = 'X';

		/************ Display bullet ****************/
		//start bullet on game
		if (bulletTime == 0) {
			std::cout << "In Bullet Time" << std::endl;
			bulletTime++;
			bulletRelease = true;
		}
		//make the bullet go up
		else if (bulletRelease == true) {
			std::cout << "Bullet Position: " << moveBullet << " , " << moveXBullet << std::endl;
			game[moveBullet][moveXBullet] = ' ';
			if (moveBullet == 0) {
				//std::cout << bulletRelease << std::endl;
				bulletRelease = false;
				moveBullet = 2;
			}
			else {
				moveBullet--;
				game[moveBullet][moveXBullet] = '^';
			}
		}
		//randomize when bullet spawns
		else if (bulletRelease == false) {
			std::cout << "Bullet: INACTIVE" << std::endl;
			// generate number between 0 and 9
			bulletTime = rand() % 20;
			moveXBullet = moveShip;
		}
		//display ship coordinates
		std::cout << "Ship position at: 3 ," << moveShip << std::endl << std::endl;

		//display game
		for (int i = 0; i < yAxis; i++) {
			for (int j = 0; j < xAxis; j++) {
				std::cout << game[i][j] << ' ';
			}
			std::cout << std::endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		system("CLS");
	}

	return 0;
}