#include "all.h"

int player_state;

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


float right_footX;
float right_footY;

float left_footX;
float left_footY;

float scroll_position_X;

extern float scrollValue;

//OBJ2D型の変数playerを宣言
OBJ2D player;
extern OBJ2D goal[GOAL_MAX];

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
}

//--------------------------------------
//  プレイヤーの更新処理
//--------------------------------------

bool right_ground = false;
bool left_ground = false;

VECTOR2 body;
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
        player.offset = { 0,0 };
        body = { 0 , 0 };

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
       
       if (right_footY > GROUND_Y)
       {
           right_footY = GROUND_Y;
          
           right_ground = true;
           player.speed.y = 0.0f;

           
           
           if (!left_ground && right_ground)
           {
               player_angle = 0;
               player_angle2 = 0;
           }

           
       }

       else
       {
            right_ground = false;
       }

       if (left_footY > GROUND_Y)
       {
           left_footY = GROUND_Y;
         
           left_ground = true;
           player.speed.y = 0.0f;

           
           if (!right_ground && left_ground)
           {
               player_angle3 = 0;
               player_angle4 = 0;
           }

       }

       else
       {
           
           left_ground = false;
       }

       //膝固定
       //右膝
       right_knee_PosX = right_footX + cosf(ToRadian(player_angle2 - 90.0)) * 128.0f;
       right_knee_PosY = right_footY + sinf(ToRadian(player_angle2 - 90.0)) * 128.0f;

       //左膝
       left_knee_PosX = left_footX + cosf(ToRadian(player_angle4 - 90.0)) * 128.0f;
       left_knee_PosY = left_footY + sinf(ToRadian(player_angle4 - 90.0)) * 128.0f;

       //太もも固定
       //右足
       right_waistX = right_knee_PosX + cosf(ToRadian(player_angle - 90.0)) * 128.0f;
       right_waistY = right_knee_PosY + sinf(ToRadian(player_angle - 90.0)) * 128.0f;
       
       //左足
       left_waistX = left_knee_PosX + cosf(ToRadian(player_angle3 - 90.0)) * 128.0f;
       left_waistY = left_knee_PosY + sinf(ToRadian(player_angle3 - 90.0)) * 128.0f;


       // 右足→左足のベクトル
       VECTOR2 footVec(left_waistX - right_waistX, left_waistY - right_waistY);
       // 距離
       float dist = sqrtf(footVec.x * footVec.x + footVec.y * footVec.y);
       footVec.x /= dist;
       footVec.y /= dist;

       dist /= 2;

       body.x = right_waistX + footVec.x * dist;
       body.y = right_waistY + footVec.y * dist;

       // 前のフレームで地面に接地したか
        break;
       
    }
}

void player_render()
{
    //プレイヤーの描画
    
     
    //左腕
    sprite_render(sprLeftArm, body.x + 90, body.y - 150, player.scale.x * 1.5, player.scale.y * 1.5, player.texPos.x, player.texPos.y, player.texSize.x, player.texSize.y, player.pivot.x, player.pivot.y,
        ToRadian(0), player.color.x, player.color.y);
     
    //右腕
    sprite_render(sprRightArm, body.x-100, body.y-160, player.scale.x * 2, player.scale.y*2, player.texPos.x, player.texPos.y, player.texSize.x, player.texSize.y, player.pivot.x, player.pivot.y,
        ToRadian(0), player.color.x, player.color.y);
     
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

    //体
    sprite_render(sprBody, body.x, body.y, player.scale.x * 2.8, player.scale.y * 2.8, player.texPos.x, player.texPos.y, player.texSize.x, player.texSize.y, player.pivot.x, player.pivot.y + player.texSize.y - 20.0f,
        ToRadian(0), player.color.x, player.color.y);

    debug::setString("right_ground%d", right_ground);
    debug::setString("left_ground%d", left_ground);

}

void player_moveY()
{
    
    //重力
    if (!right_ground && !left_ground)
    {
        player.speed.y += GRAVITY;
    }

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
        scroll_position_X += 2;
        boal.pos.x += 2;

        for (int i = 0; i < 9; i++)
        {
            goal[i].pos.x += 2;
        }
        
        //回転速度
        player_angle2 += 1.0f;

        if (scrollValue > 750)
        {
            scrollValue -= 2;
            scroll_position_X -= 2;
            boal.pos.x -= 2;
            for (int i = 0; i < 9; i++)
            {
                goal[i].pos.x -= 2;
            }
        }

        //右足を前にする限界値
        if (player_angle2 > 40.0f) 
        {
            player_angle2 = 40.0f;
            //移動停止
            scrollValue -= 2;
            scroll_position_X -= 2;
            boal.pos.x -= 2;

            for (int i = 0; i < 9; i++)
            {
                goal[i].pos.x -= 2;
            }
        }

        //膝の可動域を超えない処理
        if (player_angle <= 40.0f && player_angle2 > 0)
        {
            player_angle2 -= 1.0f;
            //移動停止
            scrollValue -= 2;
            scroll_position_X -= 2;
            boal.pos.x -= 2;

            for (int i = 0; i < 9; i++)
            {
                goal[i].pos.x -= 2;
            }
        }
           
        if (scrollValue > 1920)
        {
            scrollValue = 1920;
            
            goal[0].pos.x = scrollValue - scrollValue + 100;
            goal[3].pos.x = scrollValue - scrollValue + 100;
            goal[6].pos.x = scrollValue - scrollValue + 100;

            goal[1].pos.x = scrollValue - scrollValue + 300;
            goal[4].pos.x = scrollValue - scrollValue + 300;
            goal[7].pos.x = scrollValue - scrollValue + 300;

            goal[2].pos.x = scrollValue - scrollValue + 500;
            goal[5].pos.x = scrollValue - scrollValue + 500;
            goal[8].pos.x = scrollValue - scrollValue + 500;
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
        scroll_position_X += 2;
        boal.pos.x += 2;

        for (int i = 0; i < 9; i++)
        {
            goal[i].pos.x += 2;
        }
        //回転速度
        player_angle4 += 1.0f;

        //左足を前にする限界値
        if (player_angle4 > 60.0f) 
        {
            player_angle4 = 60.0f;
            //移動停止
            scrollValue -= 2;
            scroll_position_X -= 2;
            boal.pos.x -= 2;

            for (int i = 0; i < 9; i++)
            {
                goal[i].pos.x -= 2;
            }
        }

        //膝の可動域を超えない処理
        if (player_angle3 <= 40.0f && player_angle4 > 0)
        {
            player_angle4 -= 1.0f;
            //移動停止
            scrollValue -= 2;
            scroll_position_X -= 2;
            boal.pos.x -= 2;

            for (int i = 0; i < 9; i++)
            {
                goal[i].pos.x -= 2;
            }
        }

        if (scrollValue > 1920)
        {
            scrollValue = 1920;
            
            goal[0].pos.x = scrollValue - scrollValue + 100;
            goal[3].pos.x = scrollValue - scrollValue + 100;
            goal[6].pos.x = scrollValue - scrollValue + 100;

            goal[1].pos.x = scrollValue - scrollValue + 300;
            goal[4].pos.x = scrollValue - scrollValue + 300;
            goal[7].pos.x = scrollValue - scrollValue + 300;

            goal[2].pos.x = scrollValue - scrollValue + 500;
            goal[5].pos.x = scrollValue - scrollValue + 500;
            goal[8].pos.x = scrollValue - scrollValue + 500;
        }
    }

    //左足を後ろに動かす処理
    if (STATE(0) & PAD_R3 && !(STATE(0) & PAD_L3))
    {
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
