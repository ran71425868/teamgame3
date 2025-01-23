#include "all.h"

int result_state;
int result_timer;

Sprite* sprResult;
Sprite* sprScore;
Sprite* sprGame_clear;

extern int score;

void result_init() {
	result_state = 0;
}

void result_deinit() {

	music::stop(1);
}

void result_update() {
	switch (result_state) {
	case 0:
		////////‰Šúİ’è////////
		sprResult = sprite_load(L"./Data/Images/result_1.png");
		sprScore = sprite_load(L"./Data/Images/Score.png");
		sprGame_clear = sprite_load(L"./Data/Images/Congratulations.png");

		audio_init();
		result_state++;
		/*fallthrough*/

	case 1:
		//////// ƒpƒ‰ƒ[ƒ^‚Ìİ’è ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);
		sound::play(XWB_SYSTEM, XWB_SYSTEM_DONPATU);

		music::play(8);
		music::setVolume(8, 0.5f);
		result_state++;
		/*fallthrough*/

	case 2:
		if (TRG(0) & PAD_START) {
			nextScene = SCENE_TITLE;
			break;
		}
		break;
	}
	result_timer++;
}

void result_render() {
	GameLib::clear(0, 0, 2);
	/*sprite_render(sprResult, 0, 0, 1, 1);
	sprite_render(sprScore, 700, 100, 2, 2);
	sprite_render(sprGame_clear, 640, 50);*/

	text_out(0, std::to_string(score), 900, 300, 3, 3, 1, 1, 1, 1);

	if (result_timer / 32 % 2 == 1) {
		text_out(4, "Push Enter Key", 700, 500, 2, 2, 1, 1, 1);
	}
}