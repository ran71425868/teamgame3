//�K�v�ȃt�@�C�����C���N���[�h
#include "all.h"


int curScene = SCENE_NONE;
int nextScene = SCENE_TITLE;

// WinMain �֐����L�q����
int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int) {
	//�Q�[�����C�u�����̏����ݒ�
	GameLib::init(L"Exciting Soccer", SCREEN_W, SCREEN_H);

	audio_init();
	//�Q�[�����[�v
	while (GameLib::gameLoop())
	{
		// �V�[���؂�ւ�����
		if (curScene != nextScene) {

			// ���݂̃V�[���ɉ������I������
			switch (curScene) {
			case SCENE_TITLE:
				title_deinit();
				break;

			case SCENE_TUTORIAL:
				tutorial_deinit();
				break;


			case SCENE_GAME:
				game_deinit();
				break;

			case SCENE_RESULT:
				result_deinit();
				break;

			}

			// ���̃V�[���ɉ����������ݒ菈��
			switch (nextScene) {
			case SCENE_TITLE:
				title_init();
				break;

			case SCENE_TUTORIAL:
				tutorial_init();
				break;

			case SCENE_GAME:
				game_init();
				break;

			case SCENE_RESULT:
				result_init();
				break;
			}

			// nextScene �� curScene �ɂȂ�
			curScene = nextScene;
		}

		//���͂��X�V
		input::update();

		// ���݂̃V�[���ɉ������X�V�E�`�揈��
		switch (curScene) {
		case SCENE_TITLE:
			title_update();
			title_render();
			break;

		case SCENE_TUTORIAL:
			tutorial_update();
			tutorial_render();
			break;

		case SCENE_GAME:
			game_update();
			game_render();
			break;

		case SCENE_RESULT:
			result_update();
			result_render();
			break;

		}

		debug::display(1, 1, 1, 1, 1);

		//��ʂ�`�悷��
		GameLib::present(1, 0);

	}

	// ���݂̃V�[���ɉ������I���������s��
	switch (curScene) {

	case SCENE_TITLE:
		title_deinit();
		break;

	case SCENE_TUTORIAL:
		tutorial_deinit();
		break;

	case SCENE_GAME:
		game_deinit();
		break;

	case SCENE_RESULT:
		result_deinit();
		break;

	}

	//�Q�[�����C�u�����̏I������
	GameLib::uninit();

	return 0;
}