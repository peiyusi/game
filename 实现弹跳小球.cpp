#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int i, j;
int x, y;
int top, bottom;
int left, right; 
int velocity_x, velocity_y;

void startup() {
	x = 1;
	y = 10;
	top = 0;
	bottom = 10;
	left = 0;
	right = 20;
	velocity_x = 1;
	velocity_y = 1; 
}

void show() {
	while (1) {
	    x += velocity_x;
		y += velocity_y;
				
		system("cls");
		
		for (i = 0; i < x; i++) {
			printf("\n");
		}
		for (j = 0; j < y; j++) {
			printf(" ");
		}
		printf("o");
		printf("\n");
		Sleep(50);
		
		if (x == top || x == bottom) {
			velocity_x = -velocity_x;
			printf("\a");
		}
		if (y == left || y == right) {
			velocity_y = -velocity_y;
			printf("\a");
		}
    }
}
int main() {
    startup();
    show();   
	return 0;
}
