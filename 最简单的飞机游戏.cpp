#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define High 15   	        
#define Width 25
#define EnemyNum 5
 
int position_x, position_y;
int canvas[High][Width] = {0};
int enemy_x[EnemyNum], enemy_y[EnemyNum];

int score;
int EnemyMoveSpeed;

void gotoxy(int x, int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

void startup() {
    position_x = High - 1;
	position_y = Width / 2; 
	canvas[position_x][position_y] = 1;
	int k;
	for (k = 0; k < EnemyNum; k++) {
		enemy_x[k] = rand() % 2;
		enemy_y[k] = rand() % Width;
		canvas[enemy_x[k]][enemy_y[k]] = 3;
	}
	score = 0;
	EnemyMoveSpeed = 20;
}

void show() {
	gotoxy(0, 0);
	int i, j;
	for (i = 0; i < High; i++) {
		for (j = 0; j < Width; j++) {
			if (canvas[i][j] == 0) {
				printf(" ");
			} else if (canvas[i][j] == 1) {
				printf("*");
			} else if (canvas[i][j] == 2) {
				printf("|");
			} else if (canvas[i][j] == 3) {
				printf("@");
			}
		}
		printf("\n");
	}
	printf("�÷֣� %d\n", score);;
	Sleep(20);
}

void updateWithoutInput() {
	int i, j, k;
    for (i = 0; i < High; i++) {
    	for (j = 0; j < Width; j++) {
    		if (canvas[i][j] == 2) {
    			for (k = 0; k < EnemyNum; k++) {
    				if (i == enemy_x[k] && j == enemy_y[k]) {
    					score++;
    					canvas[enemy_x[k]][enemy_y[k]] == 0;
    					enemy_x[k] = rand() % 2;
    					enemy_y[k] = rand() % Width;
    					canvas[enemy_x[k]][enemy_y[k]] = 3;
    					canvas[i][j] = 0;
					}
				}
				canvas[i][j] = 0;
				if (i > 0) {
					canvas[i-1][j] = 2;
				}
			}
		}
	}
	
	static int speed = 0; 
	if (speed < EnemyMoveSpeed) {
		speed++;
	}
	
	for (k = 0; k < EnemyNum; k++) {
		if ((position_x == enemy_x[k]) && (position_y == enemy_y[k])) {
			printf("ʧ�ܣ�\n");
			Sleep(3000);
			system("pause");
			exit(0);
		}
		if (enemy_x[k] > High) {
			canvas[enemy_x[k]][enemy_y[k]] = 0;
            enemy_x[k] = rand() % 2;
			enemy_y[k] = rand() % Width;
			canvas[enemy_x[k]][enemy_y[k]] = 3;
			score--;
		}
		if (speed == EnemyMoveSpeed) {
			for (k = 0; k < EnemyNum; k++) {
				canvas[enemy_x[k]][enemy_y[k]] = 0;
				enemy_x[k]++;
				speed = 0;
				canvas[enemy_x[k]][enemy_y[k]] = 3;
			}
		}
	}
}

void updateWithInput() {
	char input;
	if (kbhit()) {
		input = getch();
		if (input == 'w') {
		    canvas[position_x][position_y] = 0;
		    position_x--;
		    canvas[position_x][position_y] = 1;
		} else if (input == 's') {
		    canvas[position_x][position_y] = 0;
		    position_x++;
		    canvas[position_x][position_y] = 1;
		} else if (input == 'a' && position_y > 0) {
		    canvas[position_x][position_y] = 0;
		    position_y--;
		    canvas[position_x][position_y] = 1;
		} else if (input == 'd' && position_y < Width - 1) {
		    canvas[position_x][position_y] = 0;
		    position_y++;
		    canvas[position_x][position_y] = 1;
		} else if (input == ' ') {
			canvas[position_x-1][position_y] = 2;
		}
		
		
	}
}

int main() {
	startup();
	while (1) {
	    show();
	    updateWithoutInput();
	    updateWithInput();
	}
	
	return 0;
}
