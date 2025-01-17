#include "all.h"

int player_state;

int scroll_position_X;
int scroll_position_Y;

//各足パーツの角度
float player_angle;
float player_angle2;
float player_angle3;
float player_angle4;

//右膝
float right_knee_PosX;
float right_knee_PosY;
//左膝
float left_knee_PosX;
float left_knee_PosY;

float footPosX;
float footPosY;

float hizaX;
float hizaY;

extern float scrollValue;

//OBJ2D型の変数playerを宣言
OBJ2D player;

Sprite* sprBody;
Sprite* sprLeftArm;
Sprite* sprRightArm;
Sprite* sprThighs;
Sprite* sprLeftLeg;
Sprite* sprRightLeg;
Sprite* sprPlayer;

//--------------------------------------
//  プレイヤーの初期設定
//--------------------------------------
void player_init()
{
    //player_stateを0
    player_state = 0;
    player_angle = 0.0f;
    player_angle2 = 0;
    player_angle3 = 0;
    player_angle4 = 0;
}
//--------------------------------------
//  プレイヤーの終了処理
//--------------------------------------
void player_deinit()
{
    //sprPlayerを破棄
    safe_delete(sprPlayer);
}

//--------------------------------------
//  プレイヤーの更新処理
//--------------------------------------

bool ground = false;
void player_update()
{
    switch (player_state)
    {
    case 0:
        //////// 初期設定 ////////

        //プレイヤーの画像を読み込み
        sprPlayer = sprite_load(L"./Data/Images/3.png");
        sprRightLeg = sprite_load(L"./Data/Images/right_leg.png");
        sprThighs = sprite_load(L"./Data/Images/thighs.png");

        ++player_state;
        /*fallthrough*/

    case 1:
        //////// パラメータの設定 ////////

        //playerのパラメータ設定
        player = {};
        player.timer = 0;
        player.pos = { SCREEN_W * 0.5f,SCREEN_H * 0.5f };
        player.scale = { 0.25f,0.25f };
        player.texPos = { 0,0 };
        player.texSize = { PLAYER_TEX_W ,PLAYER_TEX_H };
        player.pivot = { PLAYER_PIVOT_X,PLAYER_PIVOT_Y };
        player.color = { 1.0f,1.0f,1.0f,1.0f };
        player.radius = 20.0f;
        player.offset = { 0,0 };


        ++player_state;
        /*fallthrough*/

    case 2:
        //////// 通常時 ////////

        //player_moveX・Yを呼ぶ
        player_moveY();
        player_moveX();

        //位置に速度を足す
        player.pos += player.speed;

       //膝・膝下の付け根座標
       //右足
       right_knee_PosX = player.pos.x + cosf(ToRadian(player_angle + 90.0)) * 128.0f;
       right_knee_PosY = player.pos.y + sinf(ToRadian(player_angle + 90.0)) * 128.0f;
       //左足
       
       // 足先
       float footX = right_knee_PosX + cosf(ToRadian(player_angle2 + 90.0)) * 128.0f;
       float footY = right_knee_PosY + sinf(ToRadian(player_angle2 + 90.0)) * 128.0f;

       footPosX = footX + cosf(ToRadian(player_angle2 - 90.0)) * 128.0f;
       footPosY = footY + sinf(ToRadian(player_angle2 - 90.0)) * 128.0f;

       /*hizaX = footPosX + cosf(ToRadian(player_angle - 90.0)) * 128.0f;
       hizaY = footPosY + sinf(ToRadian(player_angle - 90.0)) * 128.0f;*/

       if (footY > GROUND_Y)
       {
           ground = true;
           player.speed.y = 0.0f;
           footY = GROUND_Y;
       }
       else
       {
           ground = false;
       }

       //膝固定
       //右膝
       right_knee_PosX = footX + cosf(ToRadian(player_angle2 - 90.0)) * 128.0f;
       right_knee_PosY = footY + sinf(ToRadian(player_angle2 - 90.0)) * 128.0f;

       footPosY = right_knee_PosY;

       player.pos.x = footPosX + cosf(ToRadian(player_angle - 90.0)) * 128.0f;
       player.pos.y = footPosY + sinf(ToRadian(player_angle - 90.0)) * 128.0f;
       

        break;
       
    }
}

void player_render()
{
    //プレイヤーの描画
    // 太もも
    sprite_render(sprThighs, player.pos.x , player.pos.y , player.scale.x, player.scale.y, player.texPos.x, player.texPos.y, player.texSize.x, player.texSize.y, player.pivot.x, player.pivot.y,
        ToRadian(player_angle), player.color.x, player.color.y); 
    // 膝下
    sprite_render(sprRightLeg, right_knee_PosX, right_knee_PosY, player.scale.x, player.scale.y, player.texPos.x, player.texPos.y, player.texSize.x, player.texSize.y, player.pivot.x, player.pivot.y,
        ToRadian(player_angle2), player.color.x, player.color.y);

    /*sprite_render(sprPlayer, player.pos.x+100, player.pos.y, player.scale.x, player.scale.y, player.texPos.x, player.texPos.y, player.texSize.x, player.texSize.y, player.pivot.x, player.pivot.y,
        ToRadian(player_angle3), player.color.x, player.color.y);
    sprite_render(sprPlayer, player.pos.x+100 + cosf(ToRadian(player_angle3 + 90.0)) * 128.0f, player.pos.y + sinf(ToRadian(player_angle3 + 90.0)) * 128.0f, player.scale.x, player.scale.y, player.texPos.x, player.texPos.y, player.texSize.x, player.texSize.y, player.pivot.x, player.pivot.y,
        ToRadian(player_angle4), player.color.x, player.color.y);*/

    primitive::rect(0,GROUND_Y, 1920, 80,0,0, ToRadian(0), 0, 1, 0);

    //primitive::circle({ player.pos.x + cosf(ToRadian(player_angle + 90.0)) * 128.0f,player.pos.y + sinf(ToRadian(player_angle + 90.0)) * 256.0f }, player.radius, { 1, 1 }, ToRadian(0), { 1, 0, 0, 0.2f });
}

void player_moveY()
{
    
    //重力
    if(!ground)
        player.speed.y += GRAVITY;

    //任意の操作による移動
    //右太ももを上に動かす処理
    if (STATE(0) & PAD_UP && !(STATE(0) & PAD_DOWN))
    {
       
        player_angle += PLAYER_ACCEL_Y;
        if (player_angle > 90.0f)
            player_angle = 90.0f;
    }

    //右太ももを下に動かす処理
    if (STATE(0) & PAD_DOWN && !(STATE(0) & PAD_UP))
    {
        player_angle -= PLAYER_ACCEL_Y;
        if (player_angle < 0.0f)
            player_angle = 0.0f;

    }

    //左太ももを上に動かす処理
    if (STATE(0) & PAD_L1 && !(STATE(0) & PAD_R1))
    {
        
        player_angle3 += PLAYER_ACCEL_Y;
        if (player_angle3 > 90.0f)
            player_angle3 = 90.0f;
    }

    //左太ももを下に動かす処理
    if (STATE(0) & PAD_R1 && !(STATE(0) & PAD_L1))
    {
        player_angle3 -= PLAYER_ACCEL_Y;
        if (player_angle3 < 0.0f)
            player_angle3 = 0.0f;
    }
}



void player_moveX()
{

    //任意の操作による移動
    //右足を前に動かす処理
    if (STATE(0) & PAD_LEFT && !(STATE(0) & PAD_RIGHT)) 
    {
        scrollValue += 2;
        player_angle2 += 1.0f;
        if (player_angle2 > 40.0f) 
        {
            player_angle2 = 40.0f;
            scrollValue -= 2;
        }
        if (player_angle <= 40.0f && player_angle2 > 0)
        {
            player_angle2 -= 1.0f;
            scrollValue -= 2;
        }
           
    }

    //右足を後ろに動かす処理
    if (STATE(0) & PAD_RIGHT && !(STATE(0) & PAD_LEFT)) 
    {
        //player.speed.x += PLAYER_ACCEL_X;
        player_angle2 -= 1.0f;
        if (player_angle2 < -90.0f)
            player_angle2 = -90.0f;
        

    }

    //左足を前に動かす処理
    if (STATE(0) & PAD_L3 && !(STATE(0) & PAD_R3))
    {
        player_angle4 += PLAYER_ACCEL_X;
        if (player_angle4 > 60.0f)
            player_angle4 = 60.0f;

    }

    //左足を後ろに動かす処理
    if (STATE(0) & PAD_R3 && !(STATE(0) & PAD_L3))
    {
        player_angle4 -= PLAYER_ACCEL_X;
        if (player_angle4 < -60.0f)
            player_angle4 = -60.0f;

    }
    else {
        if (player.speed.x > 0) {
            player.speed.x -= PLAYER_DECEL_X;
            if (player.speed.x < 0) {
                player.speed.x = 0.0f;
            }
        }

        if (player.speed.x < 0) {
            player.speed.x += PLAYER_DECEL_X;
            if (player.speed.x > 0) {
                player.speed.x = 0.0f;
            }
        }

    }
    if (player.speed.x >= PLAYER_SPEED_X_MAX)
        player.speed.x = PLAYER_SPEED_X_MAX;

    if (player.speed.x <= -PLAYER_SPEED_X_MAX)
        player.speed.x = -PLAYER_SPEED_X_MAX;

    debug::setString("hizaX:%f", hizaX);
    debug::setString("hizaY:%f", hizaY);

    debug::setString("playerPosX:%f", player.pos.x);
    debug::setString("playerPosY:%f", player.pos.y);
}
