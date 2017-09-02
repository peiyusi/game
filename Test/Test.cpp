#include "stdafx.h"

#include <stdio.h>
#include <conio.h>
#include<math.h>
#include <graphics.h>

// 引用 Windows Multimedia API
#pragma comment(lib, "Winmm.lib")

// 游戏窗体尺寸
#define High 800   
#define Width 590

// 游戏图片
IMAGE img_bk;
IMAGE img_planeNormal1, img_planeNormal2;
IMAGE img_planeExplode1, img_planeExplode2;
IMAGE img_bullet1, img_bullet2;
IMAGE img_enemyPlane1, img_enemyPlane2;

// 游戏元素位置
float position_x, position_y;
float bullet_x, bullet_y;
float enemy_x, enemy_y;

int isExplode; // 判断飞机是否爆炸
int score; // 得分

void startup() {
	isExplode = 0;
	score = 0;
	mciSendString("open ../素材/game_music.mp3 alias bkmusic", NULL, 0, NULL);//打开背景音乐
	mciSendString("play bkmusic repeat", NULL, 0, NULL);  // 循环播放
	initgraph(Width, High);
	loadimage(&img_bk, "../素材/background.jpg");
	loadimage(&img_planeNormal1, "../素材/planeNormal_1.jpg");
	loadimage(&img_planeNormal2, "../素材/planeNormal_2.jpg");
	loadimage(&img_bullet1, "../素材/bullet1.jpg");
	loadimage(&img_bullet2, "../素材/bullet2.jpg");
	loadimage(&img_enemyPlane1, "../素材/enemyPlane1.jpg");
	loadimage(&img_enemyPlane2, "../素材/enemyPlane2.jpg");
	loadimage(&img_planeExplode1, "../素材/planeExplode_1.jpg");
	loadimage(&img_planeExplode2, "../素材/planeExplode_2.jpg");
	position_x = Width*0.5;
	position_y = High*0.7;
	bullet_x = position_x;
	bullet_y = -85;
	enemy_x = Width*0.5;
	enemy_y = 10;
	BeginBatchDraw();
}

void show() {
	putimage(0, 0, &img_bk);	// 显示背景	
	if (isExplode == 0) {
		putimage(position_x - 50, position_y - 60, &img_planeNormal1, NOTSRCERASE); // 显示正常飞机	
		putimage(position_x - 50, position_y - 60, &img_planeNormal2, SRCINVERT);

		putimage(bullet_x - 7, bullet_y, &img_bullet1, NOTSRCERASE); // 显示子弹	
		putimage(bullet_x - 7, bullet_y, &img_bullet2, SRCINVERT);
		putimage(enemy_x, enemy_y, &img_enemyPlane1, NOTSRCERASE); // 显示敌机	
		putimage(enemy_x, enemy_y, &img_enemyPlane2, SRCINVERT);
	} else {
		putimage(position_x - 50, position_y - 60, &img_planeExplode1, NOTSRCERASE); // 显示爆炸飞机	
		putimage(position_x - 50, position_y - 60, &img_planeExplode2, SRCINVERT);
	}
	outtextxy(Width*0.48, High*0.95, "得分：");
	char s[5];
	sprintf_s(s, "%d", score);
	outtextxy(Width*0.55, High*0.95, s);
	FlushBatchDraw();
	Sleep(2);
}

void updateWithoutInput() {
	if (isExplode == 0) {
		if (bullet_y>-25) {
			bullet_y = bullet_y - 2;
		}
		if (enemy_y<High - 25) {
			enemy_y = enemy_y + 0.5;
		} else {
			enemy_y = 10;
		}
		if (fabs(bullet_x - enemy_x) + fabs(bullet_y - enemy_y) < 80) {  // 子弹击中敌机
			enemy_x = rand() % Width;
			enemy_y = -40;
			bullet_y = -85;
			mciSendString("close gemusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
			mciSendString("open ../素材/gotEnemy.mp3 alias gemusic", NULL, 0, NULL); // 打开音乐
			mciSendString("play gemusic", NULL, 0, NULL); // 仅播放一次
			score++;
			if (score>0 && score % 5 == 0 && score % 2 != 0) {
				mciSendString("close 5music", NULL, 0, NULL); // 先把前面一次的音乐关闭
				mciSendString("open ../素材/5.mp3 alias 5music", NULL, 0, NULL); // 打开音乐
				mciSendString("play 5music", NULL, 0, NULL); // 仅播放一次
			}
			if (score % 10 == 0) {
				mciSendString("close 10music", NULL, 0, NULL); // 先把前面一次的音乐关闭
				mciSendString("open E:\\10.mp3 alias 10music", NULL, 0, NULL); // 打开音乐
				mciSendString("play 10music", NULL, 0, NULL); // 仅播放一次
			}
		}

		if (fabs(position_x - enemy_x) + fabs(position_y - enemy_y) < 150) {  // 敌机击中我们
			isExplode = 1;
			mciSendString("close exmusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
			mciSendString("open ../素材/explode.mp3 alias exmusic", NULL, 0, NULL); // 打开音乐
			mciSendString("play exmusic", NULL, 0, NULL); // 仅播放一次		
		}
	}
}

void updateWithInput() {
	if (isExplode == 0) {
		MOUSEMSG m;		// 定义鼠标消息
		while (MouseHit()) {  //这个函数用于检测当前是否有鼠标消息
			m = GetMouseMsg();
			if (m.uMsg == WM_MOUSEMOVE) {
				// 飞机的位置等于鼠标所在的位置
				position_x = m.x;
				position_y = m.y;
			} else if (m.uMsg == WM_LBUTTONDOWN) {
				// 按下鼠标左键，发射子弹
				bullet_x = position_x;
				bullet_y = position_y - 85;
				mciSendString("close fgmusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
				mciSendString("open ../素材/f_gun.mp3 alias fgmusic", NULL, 0, NULL); // 打开音乐
				mciSendString("play fgmusic", NULL, 0, NULL); // 仅播放一次
			}
		}
	}
}

void gameover() {
	EndBatchDraw();
	_getch();
	closegraph();
}

int main() {
	startup();
	while (1)  //  游戏循环执行
	{
		show();  // 显示画面
		updateWithoutInput();  // 与用户输入无关的更新
		updateWithInput();     // 与用户输入有关的更新
	}
	gameover();
	return 0;
}