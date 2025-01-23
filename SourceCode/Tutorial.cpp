
#include "all.h"

int tutorial_state;
int tutorial_timer;
int counter;

Sprite* sprTutorial;
Sprite* sprTutorial2;
Sprite* sprTutorial3;
Sprite* sprTutorial4;
Sprite* sprTutorial5;

void tutorial_init()
{
	tutorial_state = 0;
	tutorial_timer = 0;
	counter = 0;
}
void tutorial_deinit() 
{
	music::stop(0);

}

void tutorial_update() {
	switch (tutorial_state) {
	case 0:
		//////// ‰Šúİ’è ////////

		audio_init();
		sprTutorial = sprite_load(L"./Data/Images/Tutorial.png");
		sprTutorial2 = sprite_load(L"./Data/Images/Tutorial2.png");
		sprTutorial3 = sprite_load(L"./Data/Images/Tutorial3.png");
		sprTutorial4 = sprite_load(L"./Data/Images/Tutorial4.png");
		sprTutorial5 = sprite_load(L"./Data/Images/™‹“ß‚ÌŒ©Ø‚è.png");
	

		tutorial_state++;
		/*fallthrough*/

	case 1:
		//////// ƒpƒ‰ƒ[ƒ^‚Ìİ’è ////////
		GameLib::setBlendMode(Blender::BS_ALPHA);
		music::play(0,false);
		music::setVolume(2, 0.5f);
		tutorial_state++;
		/*fallthrough*/

	case 2:
		//////// ’Êí ////////
		

		break;
	}



	tutorial_timer++;
}
void tutorial_render()
{

	GameLib::clear(0, 0, 0);
	
	if (TRG(0) & PAD_START)
	{
		counter++;
	}
	switch (counter)
	{
	case 0:
		sprite_render(sprTutorial, 0, 0);
		break;
	case 1:
		sprite_render(sprTutorial2, 0, 0);
		break;
	case 2:
		sprite_render(sprTutorial3, 0, 0);
		break;
	case 3:
		sprite_render(sprTutorial4, 0, 0);
		break;
	case 4:
		sprite_render(sprTutorial5, 0, 0);
		music::play(4, false);
		nextScene = SCENE_GAME;
		music::fade(0, 1);
		break;
	}

	debug::setString("counter%d", counter);
}
