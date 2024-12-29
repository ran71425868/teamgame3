#ifndef PLAYER_H
#define PLAYER_H

//******************************************************************************
//
//
//      player.h
//
//
//******************************************************************************



//プレイヤーの画像定義
#define PLAYER_TEX_W                 180.0f
#define PLAYER_TEX_H                 350.0f
#define PLAYER_PIVOT_X               90.0f
#define PLAYER_PIVOT_Y               175.0f

#define COOL_DOWN_MAX				3	

//プレイヤーの加減速の定数
#define PLAYER_ACCEL_X      0.6f
#define PLAYER_ACCEL_Y      1.0f
#define PLAYER_DECEL_X      0.4f
#define PLAYER_DECEL_Y      0.4f
#define PLAYER_SPEED_X_MAX      5.0f
#define PLAYER_SPEED_Y_MAX      5.0f

//壁の判定
#define WALL_LEFT          SCREEN_W - PLAYER_TEX_W * 0.5f
#define WALL_RIGHT          PLAYER_TEX_W * 0.5f
#define WALL_DOWN          SCREEN_H - PLAYER_TEX_H * 0.5f
#define WALL_UP             PLAYER_TEX_H * 0.5f

//------< 変数 >----------------------------------------------------------------

extern OBJ2D player;

//------< 関数 >----------------------------------------------------------------
void player_init();
void player_deinit();
void player_update();
void player_render();

void player_moveX();
void player_moveY();

void player_hp();


#endif//PLAYER_H