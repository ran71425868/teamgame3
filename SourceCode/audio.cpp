#include "all.h"

//--------------------------------------
//  オーディオの初期設定
//--------------------------------------
void audio_init()
{
    // 音楽の読み込み
    music::load(0, L"./Data/Musics/F.wav");
    music::load(1, L"./Data/Musics/SuperGazer.wav");
    music::load(2, L"./Data/Musics/TVVC3577.wav");
}

//--------------------------------------
//  オーディオの終了処理
//--------------------------------------
void audio_deinit()
{
    // 音楽を全て解放
    music::clear();
}
