#ifndef BOAL_H
#define BOAL_H

//******************************************************************************
//
//
//      player.h
//
//
//******************************************************************************



//�v���C���[�̉摜��`
#define BOAL_TEX_W                 225.0f
#define BOAL_TEX_H                 225.0f
#define BOAL_PIVOT_X               112.5f
#define BOAL_PIVOT_Y               112.5f

//�ǂ̔���
#define WALL_LEFT          SCREEN_W - BOAL_TEX_W * 0.5f
#define WALL_RIGHT         BOAL_TEX_W * 0.5f
#define WALL_DOWN          SCREEN_H - BOAL_TEX_H * 0.5f
#define WALL_UP             BOAL_TEX_H * 0.5f


#define GROUND_Y                    1000.0f
//------< �ϐ� >----------------------------------------------------------------

extern OBJ2D boal;

//------< �֐� >----------------------------------------------------------------
void boal_init();
void boal_deinit();
void boal_update();
void boal_render();

void boal_moveY();



#endif//PLAYER_H