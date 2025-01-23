#include "all.h"


int boal_state;
int boal_timer;
float speed;
bool boalground;

int boalflug;
int boalCount;

extern OBJ2D goal[GOAL_MAX];

extern int player_state;
extern float scrollValue;
extern float scroll_position_X;
extern float player_angle2;

//OBJ2D型の変数boalを宣言
OBJ2D boal;

Sprite* sprBoal;

//--------------------------------------
//  プレイヤーの初期設定
//--------------------------------------
void boal_init()
{
    //boal_stateを0
    boal_state = 0;
    boal_timer = 0;

    speed = 0;
    boalflug = 3;
    boalCount = 3;
}
//--------------------------------------
//  プレイヤーの終了処理
//--------------------------------------
void boal_deinit()
{
    //sprPlayerを破棄
    safe_delete(sprBoal);
}

//--------------------------------------
//  更新処理
//--------------------------------------
void boal_update()
{
    switch (boal_state)
    {
    case 0:
        //////// 初期設定 ////////

        //画像を読み込み
        sprBoal = sprite_load(L"./Data/Images/boal.png");

        ++boal_state;
        /*fallthrough*/

    case 1:
        //////// パラメータの設定 ////////

        //playerのパラメータ設定
        boal = {};
        boal.timer = 0;
        boal.pos = {scroll_position_X, GROUND_Y - 30};
        boal.scale = { 0.5f,0.5f };
        boal.texPos = { 0,0 };
        boal.texSize = { BOAL_TEX_W ,BOAL_TEX_H };
        boal.pivot = { BOAL_PIVOT_X,BOAL_PIVOT_Y };
        boal.color = { 1.0f,1.0f,1.0f,1.0f };
        boal.radius = 34.0f;
        boal.offset = { 0,0 };

       

        ++boal_state;
        /*fallthrough*/

    case 2:
        //////// 通常時 ////////

        //player_moveX・Yを呼ぶ
        boal_moveY();

        // 位置に速度を足す
        boal.pos += boal.speed;
        
        boalground = false;
        if (boal.pos.y > 970)
        {
            boal.speed.y = 0.0f;
            boal.pos.y = 970;
            boalground = true;
        }

        boal_timer++;
        
        
        break;
    }
}

void boal_render()
{
    //描画
    sprite_render(sprBoal,
        boal.pos.x, boal.pos.y,
        boal.scale.x, boal.scale.y,
        boal.texPos.x, boal.texPos.y,
        boal.texSize.x, boal.texSize.y,
        boal.pivot.x, boal.pivot.y,
        ToRadian(0), boal.color.x, boal.color.y);
    
   /* primitive::circle(boal.pos,
        boal.radius, { 1, 1 }, ToRadian(0), { 1, 0, 0, 0.2f }
    );*/
    debug::setString("boaltimer%d", boal_timer);

    debug::setString("boalflug%d", boalflug);
    debug::setString("boalCount%d", boalCount);
   
}
void boal_moveX()
{
    if (boal_timer % 100 == 0)
    {
        if (boalflug > 0)
        {
            boalflug--;

        }

        if (boalflug <= 0)
        {
            player_state = 0;
            boal_state = 0;

            if (boalCount > 0)
                boalCount--;
        }
        else
        {
            boalflug = 3;
        }
        
    }

    if (boalCount == 0)
    {
        game_clear();
    }
}

void boal_moveY()
{
    boal.speed.y += GRAVITY;
}


