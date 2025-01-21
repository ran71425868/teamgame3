#include "all.h"


int boal_state;
float speed;
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
        boal.pos = { SCREEN_W * 0.3f, GROUND_Y - 30};
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
        boal_moveX();

        // 位置に速度を足す
        //player.pos += player.speed;

        // プレイヤーの上下左右のエリアチェック
        /*if (player.pos.x < 100 + WALL_RIGHT) {
            player.pos.x = 100 + WALL_RIGHT;
        }
        if (player.pos.x > WALL_LEFT - 100) {
            player.pos.x = WALL_LEFT - 100;
        }*/

        /*if (player.pos.y + sinf(ToRadian(player_angle+90.0))*128.0f > WALL_DOWN) {
            player.pos.y = WALL_DOWN;
        }*/

        /*if (player.pos.y + 640.0f > GROUND_Y) {
            player.pos.y = GROUND_Y - 640.0f;
            if (player_angle > 20.0f) {

            }
        }*/
        
            boal.pos.x -= boal.speed.x;
            boal.pos.y -= boal.speed.y;
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
}
void boal_moveX()
{
    if (STATE(0) & PAD_LEFT)
    {
        //boal.pos.x += 0.05;
        //boal.pos.x += 0.2;
        boal.pos.x += 1.0;

    }

    if (hitCheck(&boal, &goal[9]))
    {

        if (player_angle2 < -60)
        {

            boal.speed.x += 3.5f;
            boal.speed.y += 3.5f;

        }
        if (player_angle2 < -30)
        {
            /* for (int i = 0; i < SCREEN_W; i++)
             {
             }*/

            boal.speed.x += 6.0f;
            boal.speed.y += 6.0f;

        }
        if (player_angle2 < -1)
        {
            boal.speed.x += 12.5f;
            boal.speed.y += 12.5f;

           
        }
        else
        {
            boal.pos.x += 0;
            boal.pos.y += 0;

         
        }
    }
}
void boal_moveY()
{
    //if (STATE(0) & PAD_UP && !(STATE(0) & PAD_DOWN))
    //{
    //    boal.pos.y -= 1;
    //}

}


