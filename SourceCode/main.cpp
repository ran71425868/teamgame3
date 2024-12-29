//�K�v�ȃt�@�C�����C���N���[�h
#include "all.h"


int curScene = SCENE_NONE;
int nextScene = SCENE_TITLE;

void setFullScreenMode()
{
	HWND hwnd = GetForegroundWindow();  // ���݂̃E�B���h�E���擾

	// �E�B���h�E�̃X�^�C�����擾
	LONG style = GetWindowLong(hwnd, GWL_STYLE);

	// �t���X�N���[���ݒ�
	MONITORINFO mi = { sizeof(mi) };
	if (GetMonitorInfo(MonitorFromWindow(hwnd, MONITOR_DEFAULTTOPRIMARY), &mi)) {
		SetWindowLong(hwnd, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hwnd, HWND_TOP,
			mi.rcMonitor.left, mi.rcMonitor.top,
			mi.rcMonitor.right - mi.rcMonitor.left,
			mi.rcMonitor.bottom - mi.rcMonitor.top,
			SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
	}
}

// WinMain �֐����L�q����
int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int) {
	//�Q�[�����C�u�����̏����ݒ�
	GameLib::init(L"Skiing in Escape", SCREEN_W, SCREEN_H);
	setFullScreenMode();

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