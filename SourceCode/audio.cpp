#include "all.h"

//--------------------------------------
//  �I�[�f�B�I�̏����ݒ�
//--------------------------------------
void audio_init()
{
    // ���y�̓ǂݍ���
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
//  �I�[�f�B�I�̏I������
//--------------------------------------
void audio_deinit()
{
    // ���y��S�ĉ��
    music::clear();
}
