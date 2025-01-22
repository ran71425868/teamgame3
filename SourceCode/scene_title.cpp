#include "all.h"

int title_state;
int title_timer;

Sprite* sprTitle;
Sprite* sprTitle_Push;

void title_init() {
	title_state = 0;
	title_timer = 0;
}
void title_deinit() {
	music::stop(0);

}
void title_update() {
	switch (title_state) {
	case 0:
		//////// 初期設定 ////////

		audio_init();
		sprTitle = sprite_load(L"./Data/Images/title.png");
		sprTitle_Push = sprite_load(L"./Data/Images/Push.png");

		title_state++;
		/*fallthrough*/

	case 1:
		//////// パラメータの設定 ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);
		music::play(0, true);
		music::setVolume(2, 0.5f);
		title_state++;
		/*fallthrough*/

	case 2:
		//////// 通常時 ////////
		if (TRG(0) & PAD_START) {
			music::play(0, false);
			nextScene = SCENE_TUTORIAL;
			music::fade(0, 1);
			break;
		}

		break;
	}



	title_timer++;
}
void title_render() {
	GameLib::clear(0, 0, 0);

	sprite_render(sprTitle, 0, 0);
	//タイトル
	GameLib::text_out(5, "EXCITING SOCCER", 1800, 100, 3.5f, 3.5f, 1, 1, 1, 1, TEXT_ALIGN::UPPER_RIGHT);
	GameLib::text_out(5, "EXCITING SOCCER", 1800, 100, 3.6f, 3.6f, 0, 0, 0, 1, TEXT_ALIGN::UPPER_RIGHT);
	if (title_timer / 32 % 2 == 1) {
		sprite_render(sprTitle_Push, 300, 800, 2.0f, 2.0f);
	}

}