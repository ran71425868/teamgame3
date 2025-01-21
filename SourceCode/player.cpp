#include "all.h"

int player_state;

int scroll_position_X;
int scroll_position_Y;

//腰
float right_waistX;
float right_waistY;
float left_waistX;
float left_waistY;

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

//右足
float right_foot_PosX;
float right_foot_PosY;
//左足
float left_foot_PosX;
float left_foot_PosY;

float right_footX;
float right_footY;

float left_footX;
float left_footY;

extern float scrollValue;

//OBJ2D型の変数playerを宣言
OBJ2D player;

Sprite* sprBody;
Sprite* sprLeftArm;
Sprite* sprRightArm;
Sprite* sprThighs;
Sprite* sprLeftLeg;
Sprite* sprRightLeg;
Sprite* sprNaiki;

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
    safe_delete(sprBody);
    safe_delete(sprLeftArm);
    safe_delete(sprRightArm);
    safe_delete(sprThighs);
    safe_delete(sprLeftLeg);
    safe_delete(sprRightLeg);
    safe_delete(sprNaiki);
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
        sprBody = sprite_load(L"./Data/Images/upper_body.png");
        sprLeftArm = sprite_load(L"./Data/Images/left_arm.png");
        sprRightArm = sprite_load(L"./Data/Images/right_arm.png");
        sprThighs = sprite_load(L"./Data/Images/thighs.png");
        sprLeftLeg = sprite_load(L"./Data/Images/left_leg.png");
        sprRightLeg = sprite_load(L"./Data/Images/right_leg.png");

        sprNaiki = sprite_load(L"./Data/Images/naiki.png");

        ++player_state;
        /*fallthrough*/

    case 1:
        //////// パラメータの設定 ////////

        //playerのパラメータ設定
        player = {};
        player.timer = 0;
        player.pos = { SCREEN_W * 0.5f,SCREEN_H * 0.5f };
        player.scale = { 1.0f,1.0f };
        player.texPos = { 0,0 };
        player.texSize = { PLAYER_TEX_W ,PLAYER_TEX_H };
        player.pivot = { PLAYER_PIVOT_X,PLAYER_PIVOT_Y };
        player.color = { 1.0f,1.0f,1.0f,1.0f };
        player.radius = 20.0f;
        player.offset = { 0,-64 };


        ++player_state;
        /*fallthrough*/

    case 2:
        //////// 通常時 ////////

        //腰にプレイヤーの位置を入れる
        right_waistX = player.pos.x;
        right_waistY = player.pos.y;

        left_waistX = player.pos.x + 60;
        left_waistY = player.pos.y;

        //player_moveX・Yを呼ぶ
        player_moveY();
        player_moveX();

        //位置に速度を足す
        player.pos += player.speed;

       //膝・膝下の付け根座標
       //右足
       right_knee_PosX = right_waistX + cosf(ToRadian(player_angle + 90.0)) * 128.0f;
       right_knee_PosY = right_waistY + sinf(ToRadian(player_angle + 90.0)) * 128.0f;

       //左足
       left_knee_PosX = left_waistX+ cosf(ToRadian(player_angle3 + 90.0)) * 128.0f;
       left_knee_PosY = left_waistY+ sinf(ToRadian(player_angle3 + 90.0)) * 128.0f;

       //足先
       //右足
       right_footX = right_knee_PosX + cosf(ToRadian(player_angle2 + 90.0)) * 128.0f;
       right_footY = right_knee_PosY + sinf(ToRadian(player_angle2 + 90.0)) * 128.0f;

       //左足
       left_footX = left_knee_PosX + cosf(ToRadian(player_angle4 + 90.0)) * 128.0f;
       left_footY = left_knee_PosY + sinf(ToRadian(player_angle4 + 90.0)) * 128.0f;

       //足先から見た膝の座標
       //右足
       right_foot_PosX =right_footX + cosf(ToRadian(player_angle2 - 90.0)) * 128.0f;
       right_foot_PosY =right_footY + sinf(ToRadian(player_angle2 - 90.0)) * 128.0f;

       //左足
       left_foot_PosX = left_footX + cosf(ToRadian(player_angle4 - 90.0)) * 128.0f;
       left_foot_PosY = left_footY + sinf(ToRadian(player_angle4 - 90.0)) * 128.0f;

       
       if (right_footY > GROUND_Y)
       {
           ground = true;
           player.speed.y = 0.0f;
           right_footY = GROUND_Y;
       }
       if (left_footY > GROUND_Y)
       {
           ground = true;
           player.speed.y = 0.0f;
           left_footY = GROUND_Y;
       }
       
       else
       {
           ground = false;
       }

       //膝固定
       //右膝
       right_knee_PosX = right_footX + cosf(ToRadian(player_angle2 - 90.0)) * 128.0f;
       right_knee_PosY = right_footY + sinf(ToRadian(player_angle2 - 90.0)) * 128.0f;

       //左膝
       left_knee_PosX = left_footX + cosf(ToRadian(player_angle4 - 90.0)) * 128.0f;
       left_knee_PosY = left_footY + sinf(ToRadian(player_angle4 - 90.0)) * 128.0f;

       right_foot_PosY = right_knee_PosY;
       left_foot_PosY = left_knee_PosY;

       //太もも固定
       //右足
       right_waistX = right_foot_PosX + cosf(ToRadian(player_angle - 90.0)) * 128.0f;
       right_waistY = right_foot_PosY + sinf(ToRadian(player_angle - 90.0)) * 128.0f;
       
       //左足
       left_waistX = left_foot_PosX + cosf(ToRadian(player_angle3 - 90.0)) * 128.0f;
       left_waistY = left_foot_PosY + sinf(ToRadian(player_angle3 - 90.0)) * 128.0f;

        break;
       
    }
}

void player_render()
{
    //プレイヤーの描画
    //体
     
    //左腕
    //sprite_render(sprLeftArm, player.pos.x, player.pos.y, player.scale.x, player.scale.y, player.texPos.x, player.texPos.y, player.texSize.x, player.texSize.y, player.pivot.x, player.pivot.y,
        //ToRadian(0), player.color.x, player.color.y);
     
    //右腕
    //sprite_render(sprRightArm, player.pos.x, player.pos.y, player.scale.x, player.scale.y, player.texPos.x, player.texPos.y, player.texSize.x, player.texSize.y, player.pivot.x, player.pivot.y,
        //ToRadian(0), player.color.x, player.color.y);
     
    // 右太もも
    sprite_render(sprThighs, right_waistX, right_waistY, player.scale.x, player.scale.y, player.texPos.x, player.texPos.y, player.texSize.x, player.texSize.y, player.pivot.x, player.pivot.y,
        ToRadian(player_angle), player.color.x, player.color.y); 
    // 右膝下
    sprite_render(sprRightLeg, right_knee_PosX, right_knee_PosY, player.scale.x, player.scale.y, player.texPos.x, player.texPos.y, player.texSize.x, player.texSize.y, player.pivot.x, player.pivot.y,
        ToRadian(player_angle2), player.color.x, player.color.y);

    //左太もも
    sprite_render(sprThighs, left_waistX, left_waistY, player.scale.x, player.scale.y, player.texPos.x, player.texPos.y, player.texSize.x, player.texSize.y, player.pivot.x, player.pivot.y,
        ToRadian(player_angle3), player.color.x, player.color.y);
   //左膝下
    sprite_render(sprLeftLeg, left_knee_PosX, left_knee_PosY, player.scale.x, player.scale.y, player.texPos.x, player.texPos.y, player.texSize.x, player.texSize.y, player.pivot.x, player.pivot.y,
        ToRadian(player_angle4), player.color.x, player.color.y);

    sprite_render(sprNaiki, right_footX, right_footY, player.scale.x*0.5f, player.scale.y*0.5f, player.texPos.x, player.texPos.y, player.texSize.x, player.texSize.y, player.pivot.x, player.pivot.y+90,
        ToRadian(player_angle4), player.color.x, player.color.y);





    sprite_render(sprBody, player.pos.x+40, player.pos.y-350, player.scale.x*2.8, player.scale.y*2.8, player.texPos.x, player.texPos.y, player.texSize.x, player.texSize.y, player.pivot.x, player.pivot.y, 
        ToRadian(0), player.color.x, player.color.y);

    primitive::rect(0,GROUND_Y, 1920, 80,0,0, ToRadian(0), 0, 1, 0);

    primitive::circle({ right_knee_PosX ,right_knee_PosY }, player.radius, { 1, 1 }, ToRadian(0), { 1, 0, 0, 0.2f });
    primitive::circle({ right_footX ,right_footY-20 }, player.radius, { 1, 1 }, ToRadian(0), { 1, 0, 0, 0.2f });
}

void player_moveY()
{
    
    //重力
    if(!ground)
        player.speed.y += GRAVITY;

  //--------------------------------------------------------------
  // 右太もも
  //--------------------------------------------------------------

    //右太ももを上に動かす処理
    if (STATE(0) & PAD_UP && !(STATE(0) & PAD_DOWN))
    {
        //回転速度
        player_angle += 1.0f;

        //右太ももを上に動かす限界値
        if (player_angle > 90.0f)
            player_angle = 90.0f;

        //太ももが足に食い込まない処理
        if (player_angle2 < 0)
            player_angle = 0;
        
    }

    //右太ももを下に動かす処理
    if (STATE(0) & PAD_DOWN && !(STATE(0) & PAD_UP))
    {
        //回転速度
        player_angle -= 1.0f;

        //右太ももを下に動かす限界値
        if (player_angle < 0.0f)
            player_angle = 0.0f;

        //太ももを降ろすと足も降りる処理
        if (player_angle2 <= 40)
        {
            player_angle2 -= 1.0f;

            //太ももが足に食い込まない処理
            if (player_angle2 < 0) {
                player_angle2 += 1.0f;
            }
        }

    }

   //--------------------------------------------------------------
   // 左太もも
   //--------------------------------------------------------------

    //左太ももを上に動かす処理
    if (STATE(0) & PAD_L1 && !(STATE(0) & PAD_R1))
    {
        //回転速度
        player_angle3 += 1.0f;

        //左太ももを上に動かす限界値
        if (player_angle3 > 90.0f)
            player_angle3 = 90.0f;

        //太ももが足に食い込まない処理
        if (player_angle4 < 0)
            player_angle3 = 0;
    }

    //左太ももを下に動かす処理
    if (STATE(0) & PAD_R1 && !(STATE(0) & PAD_L1))
    {
        //回転速度
        player_angle3 -= 1.0f;

        //左太ももを下に動かす限界値
        if (player_angle3 < 0.0f)
            player_angle3 = 0.0f;

        //太ももを降ろすと足も降りる処理
        if (player_angle4 <= 40)
        {
            player_angle4 -= 1.0f;

            //太ももが足に食い込まない処理
            if (player_angle4 < 0) {
                player_angle4 += 1.0f;
            }
        }
    }
}



void player_moveX()
{
   //--------------------------------------------------------------
   // 右足
   //--------------------------------------------------------------
    
    //右足を前に動かす処理
    if (STATE(0) & PAD_LEFT && !(STATE(0) & PAD_RIGHT)) 
    {
        //移動処理
        scrollValue += 2;
        //回転速度
        player_angle2 += 1.0f;

        //右足を前にする限界値
        if (player_angle2 > 40.0f) 
        {
            player_angle2 = 40.0f;
            //移動停止
            scrollValue -= 2;
        }

        //膝の可動域を超えない処理
        if (player_angle <= 40.0f && player_angle2 > 0)
        {
            player_angle2 -= 1.0f;
            //移動停止
            scrollValue -= 2;
        }
           
    }

    //右足を後ろに動かす処理
    if (STATE(0) & PAD_RIGHT && !(STATE(0) & PAD_LEFT)) 
    {
        //回転速度
        player_angle2 -= 1.0f;

        //右足を後ろにする限界値
        if (player_angle2 < -90.0f)
            player_angle2 = -90.0f;

        //膝に足が食い込まない処理
        if (player_angle >= 90)
            player_angle2 += 1.0f;
       

    }

    //--------------------------------------------------------------
    // 左足
    //--------------------------------------------------------------

    //左足を前に動かす処理
    if (STATE(0) & PAD_L3 && !(STATE(0) & PAD_R3))
    {
        //移動処理
        scrollValue += 2;
        //回転速度
        player_angle4 += 1.0f;

        //左足を前にする限界値
        if (player_angle4 > 60.0f) 
        {
            player_angle4 = 60.0f;
            //移動停止
            scrollValue -= 2;
        }

        //膝の可動域を超えない処理
        if (player_angle3 <= 40.0f && player_angle4 > 0)
        {
            player_angle4 -= 1.0f;
            //移動停止
            scrollValue -= 2;
        }
    }

    //左足を後ろに動かす処理
    if (STATE(0) & PAD_R3 && !(STATE(0) & PAD_L3))
    {
        //移動処理
        scrollValue += 2;
        //回転速度
        player_angle4 -= 1.0f;

        //左足を後ろにする限界値
        if (player_angle4 < -60.0f)
            player_angle4 = -60.0f;

        //膝に足が食い込まない処理
        if (player_angle3 >= 90)
            player_angle4 += 1.0f;
    }

    //加減速処理
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
    //速度を一定にする
    if (player.speed.x >= PLAYER_SPEED_X_MAX)
        player.speed.x = PLAYER_SPEED_X_MAX;

    if (player.speed.x <= -PLAYER_SPEED_X_MAX)
        player.speed.x = -PLAYER_SPEED_X_MAX;

}
