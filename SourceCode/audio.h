#ifndef AUDIO_H
#define AUDIO_H

//******************************************************************************
//
//
//      audio.h
//
//
//******************************************************************************

//------< 定数 >----------------------------------------------------------------

// XWBの種類
#define XWB_SYSTEM          0
#define XWB_SE			1

// SYSTEMの効果音
#define XWB_SYSTEM_DONPATU    0

#define XWB_SE_BU   0
#define XWB_SE_HIT    1
#define XWB_SE_KANSEI    2
#define XWB_SE_KETTEI    3


//------< 関数 >----------------------------------------------------------------
void audio_init();
void audio_deinit();

#endif//AUDIO_H