#include "all.h"

//--------------------------------------
//  オーディオの初期設定
//--------------------------------------
void audio_init()
{
    // 音楽の読み込み
    music::load(0, L"./Data/Musics/maou_bgm_cyber29.wav");
    music::load(1, L"./Data/Musics/maou_bgm_cyber41.wav");


    sound::load(XWB_SYSTEM, L"./Data/Sounds/system.xwb");
    sound::load(XWB_SE, L"./Data/Sounds/se.xwb");
   

}

//--------------------------------------
//  オーディオの終了処理
//--------------------------------------
void audio_deinit()
{
    // 音楽を全て解放
    music::clear();
}
