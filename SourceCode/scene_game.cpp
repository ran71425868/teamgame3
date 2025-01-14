#include "all.h"
#include <sstream>
#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>

using namespace std;


int game_state;
int game_timer;

float playerX;
float playerY;

int score;
int goalflug;
float comboscore;
int combo;

Sprite* sprBack;

std::ostringstream oss;                                 // 文字列ストリーム
POINT point;

// 現在のスクロール量
float scrollValue = 0.0f;

void game_init() {
	game_state = 0;
	game_timer = 0;
	score = 0;
	combo = 0;
	comboscore = 1.0f;
	goalflug = 0;
}
void game_deinit() {
	music::stop(0);
	player_deinit();
	boal_deinit();
}
void game_update()
{
	switch (game_state)
	{
	case 0:
		sprBack = sprite_load(L"./Data/Images/map_1.png");


		audio_init();
		player_init();
		boal_init();

		game_state++;
		/*fallthrough*/

	case 1:
		GameLib::setBlendMode(Blender::BS_ALPHA);

		music::play(0);
		music::setVolume(0, 0.1f);

		score = 0;

		game_state++;
		/*fallthrough*/

	case 2:
		if (TRG(0) & PAD_SELECT) {
			nextScene = SCENE_TITLE;
			break;
		}

		player_update();
		boal_update();
		
		judge();
		

		break;
	}

	/*scrollValue -= 5;
	if (scrollValue < -9000)
	{
		scrollValue = 0;
	}*/

	game_timer++;
}
void game_render() {

	sprite_render(sprBack, 0.0f, scrollValue); // 背景をカメラの位置に合わせて描画

	player_render();
	boal_render();

	text_out(0, "score", 1700, 450, 2, 2);
	text_out(0, std::to_string(score), 1700, 500, 2, 2);
	text_out(0, "combo", 1700, 550, 2, 2);
	text_out(0, std::to_string(combo), 1700, 600, 2, 2);
}
void game_score()
{
	if (combo >= 10)
		comboscore = 2.5f;
	else if (combo >= 5)
		comboscore = 2.0f;
	else
		comboscore = 1.0f;
}

void game_clear()
{
	nextScene = SCENE_RESULT;
}
