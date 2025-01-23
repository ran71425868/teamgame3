#ifndef AUDIO_H
#define AUDIO_H

//******************************************************************************
//
//
//      audio.h
//
//
//******************************************************************************

//------< ’è” >----------------------------------------------------------------

// XWB‚ÌŽí—Þ
#define XWB_SYSTEM          0
#define XWB_SE			1

// SYSTEM‚ÌŒø‰Ê‰¹
#define XWB_SYSTEM_DONPATU    0

#define XWB_SE_BU   0
#define XWB_SE_HIT    1
#define XWB_SE_KANSEI    2
#define XWB_SE_KETTEI    3


//------< ŠÖ” >----------------------------------------------------------------
void audio_init();
void audio_deinit();

#endif//AUDIO_H