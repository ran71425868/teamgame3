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
	music::stop(2);

}
void title_update() {
	switch (title_state) {
	case 0:
		//////// ‰Šúİ’è ////////

		audio_init();
		sprTitle = sprite_load(L"./Data/Images/title.png");
		sprTitle_Push = sprite_load(L"./Data/Images/Push.png");

		title_state++;
		/*fallthrough*/

	case 1:
		//////// ƒpƒ‰ƒ[ƒ^‚Ìİ’è ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);
		music::play(0);
		music::setVolume(2, 0.5f);
		title_state++;
		/*fallthrough*/

	case 2:
		//////// ’Êí ////////
		if (TRG(0) & PAD_START) {
			music::play(4, false);
			nextScene = SCENE_GAME;
			break;
		}

		break;
	}



	title_timer++;
}
void title_render() {
	GameLib::clear(0, 0, 0);

	sprite_render(sprTitle, 0, 0);

	if (title_timer / 32 % 2 == 1) {
		sprite_render(sprTitle_Push, 300, 800, 2.0f, 2.0f);
	}

}