//必要なファイルをインクルード
#include "all.h"


int curScene = SCENE_NONE;
int nextScene = SCENE_TITLE;

void setFullScreenMode()
{
	HWND hwnd = GetForegroundWindow();  // 現在のウィンドウを取得

	// ウィンドウのスタイルを取得
	LONG style = GetWindowLong(hwnd, GWL_STYLE);

	// フルスクリーン設定
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

// WinMain 関数を記述する
int APIENTRY wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int) {
	//ゲームライブラリの初期設定
	GameLib::init(L"Skiing in Escape", SCREEN_W, SCREEN_H);
	setFullScreenMode();

	audio_init();
	//ゲームループ
	while (GameLib::gameLoop())
	{
		// シーン切り替え処理
		if (curScene != nextScene) {

			// 現在のシーンに応じた終了処理
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

			// 次のシーンに応じた初期設定処理
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

			// nextScene が curScene になる
			curScene = nextScene;
		}

		//入力を更新
		input::update();

		// 現在のシーンに応じた更新・描画処理
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

		//画面を描画する
		GameLib::present(1, 0);

	}

	// 現在のシーンに応じた終了処理を行う
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

	//ゲームライブラリの終了処理
	GameLib::uninit();

	return 0;
}