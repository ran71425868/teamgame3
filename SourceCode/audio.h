#ifndef AUDIO_H
#define AUDIO_H

//******************************************************************************
//
//
//      audio.h
//
//
//******************************************************************************

//------< �萔 >----------------------------------------------------------------

// XWB�̎��
#define XWB_SYSTEM          0
#define XWB_SE			1

// SYSTEM�̌��ʉ�
#define XWB_SYSTEM_DONPATU    0

#define XWB_SE_BU   0
#define XWB_SE_HIT    1
#define XWB_SE_KANSEI    2
#define XWB_SE_KETTEI    3


//------< �֐� >----------------------------------------------------------------
void audio_init();
void audio_deinit();

#endif//AUDIO_H