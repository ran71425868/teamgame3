#include "all.h"

//--------------------------------------
//  �I�[�f�B�I�̏����ݒ�
//--------------------------------------
void audio_init()
{
    // ���y�̓ǂݍ���
    music::load(0, L"./Data/Musics/maou_bgm_cyber29.wav");
    music::load(1, L"./Data/Musics/maou_bgm_cyber41.wav");


    sound::load(XWB_SYSTEM, L"./Data/Sounds/system.xwb");
    sound::load(XWB_SE, L"./Data/Sounds/se.xwb");
   

}

//--------------------------------------
//  �I�[�f�B�I�̏I������
//--------------------------------------
void audio_deinit()
{
    // ���y��S�ĉ��
    music::clear();
}
