#include "all.h"


int boal_state;
float speed;
bool boalground;

int boalflug;
int boalCount;

extern OBJ2D goal[GOAL_MAX];

extern float scrollValue;
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
    speed = 0;
    boalflug = 0;
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
        boal.pos = {0, GROUND_Y - 30};
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
    
    primitive::circle(boal.pos,
        boal.radius, { 1, 1 }, ToRadian(0), { 1, 0, 0, 0.2f }
    );
    debug::setString("boalflug%d", boalflug);
    debug::setString("boalCount%d", boalCount);
   
}
void boal_moveX()
{
    boalflug = 1;
    /*if (boal.pos.y >= 970)
    {
        if (boalCount > 0)
            boalCount -= 1;
    }*/
    if (boalflug > 0 && boal.pos.y >= 970)
    {
        boal.speed.x = 0.0f;
    }
}

void boal_moveY()
{
    boal.speed.y += GRAVITY;
    

}


