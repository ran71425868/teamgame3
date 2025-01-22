#include "all.h"

//--------------------------------------
//  オーディオの初期設定
//--------------------------------------
void audio_init()
{
    // 音楽の読み込み
    music::load(0, L"./Data/Musics/maou_bgm_cyber29.wav");
    music::load(1, L"./Data/Musics/maou_bgm_cyber41.wav");
    music::load(2, L"./Data/Sounds/kettei.wav");
    music::load(3, L"./Data/Sounds/kansei.wav");
    music::load(4, L"./Data/Sounds/hit.wav");
    music::load(5, L"./Data/Sounds/bu.wav");
 
  /*  music::load(2, L"./Data/Musics/F.wav");
    music::load(3, L"./Data/Musics/SuperGazer.wav");
    music::load(4, L"./Data/Musics/TVVC3577.wav");*/ 

}

//--------------------------------------
//  オーディオの終了処理
//--------------------------------------
void audio_deinit()
{
    // 音楽を全て解放
    music::clear();
}
