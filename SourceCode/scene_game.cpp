#include "all.h"
#include <sstream>
#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>

using namespace std;

extern OBJ2D goal[GOAL_MAX];


int game_state;
int game_timer;

float playerX;
float playerY;

int score;
int goalflug;
float comboscore;
int combo;

Sprite* sprBack;

std::ostringstream oss;                                 // ï∂éöóÒÉXÉgÉäÅ[ÉÄ
POINT point;

// åªç›ÇÃÉXÉNÉçÅ[Éãó 
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
		goal_update();
		boal_update();
		title_update();
		
		judge();
		

		break;
	}

	/*
	if (scrollValue < -9000)
	{
		scrollValue = 0;
	}*/

	game_timer++;
}
void game_render() {

	sprite_render(sprBack, scrollValue, 0.0f); // îwåiÇÉJÉÅÉâÇÃà íuÇ…çáÇÌÇπÇƒï`âÊ
	sprite_render(sprBack, scrollValue - 1920, 0.0f); // îwåiÇÉJÉÅÉâÇÃà íuÇ…çáÇÌÇπÇƒï`âÊ

	player_render();
	goal_render();
	boal_render();
	

	/*text_out(0, "score", 1700, 450, 2, 2);
	text_out(0, std::to_string(score), 1700, 500, 2, 2);
	text_out(0, "combo", 1700, 550, 2, 2);
	text_out(0, std::to_string(combo), 1700, 600, 2, 2);*/
	//debug::setString("scrollValue%f", scrollValue);
}
void game_score()
{
	score = 10;

}

void game_clear()
{
	nextScene = SCENE_RESULT;
}
