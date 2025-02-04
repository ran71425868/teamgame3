#include "all.h"
#include <sstream>
#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>

using namespace std;

int title=0;

extern OBJ2D goal[GOAL_MAX];
extern OBJ2D boal;

int game_state;
int game_timer;
float cooldown;

float playerX;
float playerY;

int score;
int goalflug;

Sprite* sprBack;

std::ostringstream oss;                                 // 文字列ストリーム
POINT point;

// 現在のスクロール量
float scrollValue = 0.0f;

void game_init() {
	game_state = 0;
	game_timer = 0;
	score = 0;
	goalflug = 0;
	cooldown = 4;
}
void game_deinit() {
	safe_delete(sprBack);
	music::stop(0);
	player_deinit();
	goal_deinit();
	boal_deinit();
    title_deinit();
}
void game_update()
{
	switch (game_state)
	{
	case 0:
		sprBack = sprite_load(L"./Data/Images/map01.png");


		audio_init();
		player_init();
		goal_init();
		boal_init();

		game_state++;
		/*fallthrough*/

	case 1:
		GameLib::setBlendMode(Blender::BS_ALPHA);

		music::play(1, true);
		music::setVolume(1, 0.2f);
		sound::play(XWB_SE, XWB_SE_KANSEI);
		



		score = 0;

		game_state++;
		/*fallthrough*/

	case 2:
		if (game_timer % 100 == 0)
		{
			if (cooldown > 0)
			{
				cooldown--;
			}
			else if (cooldown <= 0)
			{

				sound::play(XWB_SE, XWB_SE_KANSEI);
				cooldown = 2.5;
			}
		}

		player_update();
		goal_update();
		boal_update();
		title_update();
		
		judge();
		
		game_timer++;

		break;
	}

	
	

	game_timer++;
}
void game_render() {

	sprite_render(sprBack, scrollValue, 0.0f); // 背景をカメラの位置に合わせて描画
	sprite_render(sprBack, scrollValue - 1920, 0.0f); // 背景をカメラの位置に合わせて描画

	player_render();
	goal_render();
	boal_render();
	

	text_out(0, "score", 1700, 550, 2, 2);
	text_out(0, std::to_string(score), 1700, 600, 2, 2);
}
void game_score()
{
	score += 10;

	if (goal[0].moveAlg == -1 && goal[1].moveAlg == -1 && goal[2].moveAlg == -1) {
		score += 50;
	}
	if (goal[3].moveAlg == -1 && goal[4].moveAlg == -1 && goal[5].moveAlg == -1) {
		score += 50;
	}
	if (goal[6].moveAlg == -1 && goal[7].moveAlg == -1 && goal[8].moveAlg == -1) {
		score += 50;
	}
	if (goal[0].moveAlg == -1 && goal[3].moveAlg == -1 && goal[6].moveAlg == -1) {
		score += 50;
	}
	if (goal[1].moveAlg == -1 && goal[4].moveAlg == -1 && goal[7].moveAlg == -1) {
		score += 50;
	}
	if (goal[2].moveAlg == -1 && goal[5].moveAlg == -1 && goal[8].moveAlg == -1) {
		score += 50;
	}
	if (goal[0].moveAlg == -1 && goal[4].moveAlg == -1 && goal[8].moveAlg == -1) {
		score += 50;
	}
	if (goal[2].moveAlg == -1 && goal[4].moveAlg == -1 && goal[6].moveAlg == -1) {
		score += 50;
	}

}

void game_clear()
{
	nextScene = SCENE_RESULT;
}

