#ifndef BOAL_H
#define BOAL_H

//******************************************************************************
//
//
//      player.h
//
//
//******************************************************************************



//プレイヤーの画像定義
#define BOAL_TEX_W                 225.0f
#define BOAL_TEX_H                 225.0f
#define BOAL_PIVOT_X               112.5f
#define BOAL_PIVOT_Y               112.5f

#define GRAVITY                     1.0f


#define GROUND_Y                    1000.0f


//------< 変数 >----------------------------------------------------------------

extern OBJ2D boal;

//------< 関数 >----------------------------------------------------------------
void boal_init();
void boal_deinit();
void boal_update();
void boal_render();

void boal_moveX();
void boal_moveY();


#endif//PLAYER_H