
#include "all.h"

int tutorial_state;
int tutorial_timer;
int counter;

Sprite* sprTutorial;
Sprite* sprTutorial2;
Sprite* sprTutorial3;
Sprite* sprTutorial4;

void tutorial_init()
{
	tutorial_state = 0;
	tutorial_timer = 0;
	counter = 0;
}
void tutorial_deinit() 
{
	music::stop(2);

}

void tutorial_update() {
	switch (tutorial_state) {
	case 0:
		//////// ‰Šúİ’è ////////

		audio_init();
		sprTutorial = sprite_load(L"./Data/Images/tutorial.png");
		sprTutorial2 = sprite_load(L"./Data/Images/tutorial2.png");
		sprTutorial3 = sprite_load(L"./Data/Images/tutorial3.png");
		sprTutorial4 = sprite_load(L"./Data/Images/tutorial4.png");
	

		tutorial_state++;
		/*fallthrough*/

	case 1:
		//////// ƒpƒ‰ƒ[ƒ^‚Ìİ’è ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);
		music::play(0);
		music::setVolume(2, 0.5f);
		tutorial_state++;
		/*fallthrough*/

	case 2:
		//////// ’Êí ////////
		if (TRG(0) & PAD_START&&counter==3) {
			music::play(4, false);
			nextScene = SCENE_GAME;
			break;
		}

		break;
	}



	tutorial_timer++;
}
void tutorial_render()
{
	GameLib::clear(0, 0, 0);

	sprite_render(sprTutorial, 0, 0);


}
