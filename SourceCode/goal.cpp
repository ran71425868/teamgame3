#include "all.h"

int goal_state;
int boalCount;
int rnd;

extern int player_state;
extern int boal_state;

extern float player_angle;
extern float player_angle2;
extern float player_angle3;
extern float player_angle4;

extern float right_footX;
extern float right_footY;

extern float scrollValue; 
extern float scroll_position_X;

extern OBJ2D boal;

struct GOAL_DATA {
    Sprite* spr;
    const wchar_t* filePath;
    VECTOR2          texPos;
    VECTOR2          texSize;
    VECTOR2          pivot;
    float            radius;
}
goalData[] = {
       {NULL,   L"./Data/Images/01.png", { 0,0 }, { 229, 239 }, { 114.5, 119.5 }, {60}},
       {NULL,   L"./Data/Images/02.png", { 0,0 }, { 227, 239 }, { 113.5, 119.5 }, {60}},
       {NULL,   L"./Data/Images/03.png", { 0,0 }, { 228, 239 }, { 114  , 119.5 }, {60}},
       {NULL,   L"./Data/Images/04.png", { 0,0 }, { 229, 240 }, { 114.5, 120   }, {60}},
       {NULL,   L"./Data/Images/05.png", { 0,0 }, { 229, 238 }, { 114.5, 119   }, {60}},
       {NULL,   L"./Data/Images/06.png", { 0,0 }, { 228, 238 }, { 114  , 119   }, {60}},
       {NULL,   L"./Data/Images/07.png", { 0,0 }, { 226, 239 }, { 113  , 119.5 }, {60}},
       {NULL,   L"./Data/Images/08.png", { 0,0 }, { 226, 239 }, { 113  , 119.5 }, {60}},
       {NULL,   L"./Data/Images/09.png", { 0,0 }, { 227, 238 }, { 113.5, 119   }, {60}},
       {NULL,   L"./Data/Images/naiki.png", { 0,0 }, { 64, 128 }, { 32, 64  }, {20}},
};
OBJ2D goal[GOAL_MAX];

struct GOAL_SET {
    int goalType;
    VECTOR2 pos;
}
goalSet[] = {
    {0,{  -1820, 400}}, 
    {1,{  -1620, 400}}, 
    {2,{  -1420, 400}}, 
    {3,{  -1820, 600}},
    {4,{  -1620, 600}},
    {5,{  -1420, 600}},
    {6,{  -1820, 800}},
    {7,{  -1620, 800}},
    {8,{  -1420, 800}},
    {9,{  950, 985}},
    {-1,{  -1, -1 }},
};
//--------------------------------------
//  ゴールの初期設定
//--------------------------------------
void goal_init()
{
    //goal_stateを0
    goal_state = 0;
    boalCount = 5;

    rnd = 0;
}

//--------------------------------------
//  ゴールの終了処理
//--------------------------------------
void goal_deinit()
{
    //Goalを破棄
    int dataNum = ARRAYSIZE(goalData);
    for (int i = 0; i < dataNum; i++) {
        safe_delete(goalData[i].spr);
    }
}

//--------------------------------------
//  ゴールの更新処理
//--------------------------------------
void goal_update()
{
    switch (goal_state)
    {
    case 0:
    {

        //////// 初期設定 ////////

        //エネミーの画像を読み込み
        int dataNum = sizeof(goalData) / sizeof(GOAL_DATA);
        for (int i = 0; i < dataNum; i++)
        {
            goalData[i].spr = sprite_load(goalData[i].filePath);
        }

        ++goal_state;
        /*fallthrough*/
    }

    case 1:
        //////// パラメータの設定 ////////

        for (int i = 0; i < GOAL_MAX; i++)
        {
            goal[i] = {};
            goal[i].moveAlg = -1;
        }

        for (int i = 0; goalSet[i].goalType >= 0; i++) {
            OBJ2D* p = searchSet0(goal, GOAL_MAX, goalSet[i].goalType, goalSet[i].pos);
            if (!p) break;
        }

        rnd = rand() % 5;

        ++goal_state;
        /*fallthrough*/

    case 2:

        if (STATE(0) & PAD_TRG1)
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

            player_deinit();
            goal[9].moveAlg = -1;
            boal_deinit();
        }

        if (STATE(0) & PAD_SELECT)
        {
            scrollValue = scroll_position_X;

            goal[0].pos.x = -1820 + scroll_position_X;
            goal[3].pos.x = -1820 + scroll_position_X;
            goal[6].pos.x = -1820 + scroll_position_X;

            goal[1].pos.x = -1620 + scroll_position_X;
            goal[4].pos.x = -1620 + scroll_position_X;
            goal[7].pos.x = -1620 + scroll_position_X;

            goal[2].pos.x = -1420 + scroll_position_X;
            goal[5].pos.x = -1420 + scroll_position_X;
            goal[8].pos.x = -1420 + scroll_position_X;

            player_state = 0;
            goal[9].moveAlg = 9;
            boal_state=0;
        }


        for (int i = 0; i < GOAL_MAX; i++) {
            if (goal[i].moveAlg == -1)continue;

            switch (goal[i].moveAlg)
            {
            case 0:
                setGoal0(&goal[i]);
                break;

            case 1:
                setGoal1(&goal[i]);
                break;

            case 2:
                setGoal2(&goal[i]);
                break;

            case 3:
                setGoal3(&goal[i]);
                break;

            case 4:
                setGoal4(&goal[i]);
                break;
            case 5:
                setGoal5(&goal[i]);
                break;

            case 6:
                setGoal6(&goal[i]);
                break;

            case 7:
                setGoal7(&goal[i]);
                break;
            case 8:
                setGoal8(&goal[i]);
                break;
            case 9:
                naiki(&goal[i]);
                break;
            }

        }
        break;
    }
}

void goal_render()
{

    for (int i = 0; i < 9; ++i)
    {
        if (goal[i].moveAlg == -1)continue;

        // ゴールの描画
        sprite_render(
            goal[i].spr,
            goal[i].pos.x, goal[i].pos.y,
            goal[i].scale.x, goal[i].scale.y,
            goal[i].texPos.x, goal[i].texPos.y,
            goal[i].texSize.x, goal[i].texSize.y,
            goal[i].pivot.x, goal[i].pivot.y,
            ToRadian(0),
            goal[i].color.x, goal[i].color.y,
            goal[i].color.z, goal[i].color.w);

    }
    for (int i = 9; i < 10; i++) 
    {
        if (goal[i].moveAlg == -1)continue;
        sprite_render(
            goal[i].spr,
            goal[i].pos.x, goal[i].pos.y,
            goal[i].scale.x, goal[i].scale.y,
            goal[i].texPos.x, goal[i].texPos.y,
            goal[i].texSize.x, goal[i].texSize.y,
            goal[i].pivot.x, goal[i].pivot.y,
            ToRadian(player_angle2),
            goal[i].color.x, goal[i].color.y,
            goal[i].color.z, goal[i].color.w);
    }
    
}

void setGoal0(OBJ2D* obj)
{

    switch (obj->state) {

    case 0:

        //1枚目
        obj->scale = { 0.6f,0.6f };
        obj->color = { 1,1,1,1 };
        obj->spr = goalData[0].spr;
        obj->texPos = goalData[0].texPos;
        obj->texSize = goalData[0].texSize;
        obj->pivot = goalData[0].pivot;
        obj->radius = goalData[0].radius;

        ++obj->state;
        /*fallthrough*/

    case 1:
        ////////通常時////////
        break;

    }

}

void setGoal1(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:

        //2枚目
        obj->scale = { 0.6f,0.6f };
        obj->color = { 1,1,1,1 };
        obj->spr = goalData[1].spr;
        obj->texPos = goalData[1].texPos;
        obj->texSize = goalData[1].texSize;
        obj->pivot = goalData[1].pivot;
        obj->radius = goalData[1].radius;

        ++obj->state;
        /*fallthrough*/

    case 1:
        ////////通常時////////
        break;
    }
}

void setGoal2(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:

        //3枚目
        obj->scale = { 0.6f,0.6f };
        obj->color = { 1,1,1,1 };
        obj->spr = goalData[2].spr;
        obj->texPos = goalData[2].texPos;
        obj->texSize = goalData[2].texSize;
        obj->pivot = goalData[2].pivot;
        obj->radius = goalData[2].radius;

        ++obj->state;
        /*fallthrough*/

    case 1:
        ////////通常時////////
        break;
    }
}

void setGoal3(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:
        //4枚目
        obj->scale = { 0.6f,0.6f };
        obj->color = { 1,1,1,1 };
        obj->spr = goalData[3].spr;
        obj->texPos = goalData[3].texPos;
        obj->texSize = goalData[3].texSize;
        obj->pivot = goalData[3].pivot;
        obj->radius = goalData[3].radius;

        ++obj->state;
        /*fallthrough*/

    case 1:
        ////////通常時////////
        break;

    }
}

void setGoal4(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:

        //5枚目
        obj->scale = { 0.6f,0.6f };
        obj->color = { 1,1,1,1 };
        obj->spr = goalData[4].spr;
        obj->texPos = goalData[4].texPos;
        obj->texSize = goalData[4].texSize;
        obj->pivot = goalData[4].pivot;
        obj->radius = goalData[4].radius;

        ++obj->state;
        /*fallthrough*/

    case 1:
        ////////通常時////////
        break;
    }
}

void setGoal5(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:

        //6枚目
        obj->scale = { 0.6f,0.6f };
        obj->color = { 1,1,1,1 };
        obj->spr = goalData[5].spr;
        obj->texPos = goalData[5].texPos;
        obj->texSize = goalData[5].texSize;
        obj->pivot = goalData[5].pivot;
        obj->radius = goalData[5].radius;

        ++obj->state;
        /*fallthrough*/

    case 1:
        ////////通常時////////
        break;
    }
}

void setGoal6(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:

        //7枚目
        obj->scale = { 0.6f,0.6f };
        obj->color = { 1,1,1,1 };
        obj->spr = goalData[6].spr;
        obj->texPos = goalData[6].texPos;
        obj->texSize = goalData[6].texSize;
        obj->pivot = goalData[6].pivot;
        obj->radius = goalData[6].radius;

        ++obj->state;
        /*fallthrough*/

    case 1:
        ////////通常時////////
        break;
    }
}

void setGoal7(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:

        //8枚目
        obj->scale = { 0.6f,0.6f };
        obj->color = { 1,1,1,1 };
        obj->spr = goalData[7].spr;
        obj->texPos = goalData[7].texPos;
        obj->texSize = goalData[7].texSize;
        obj->pivot = goalData[7].pivot;
        obj->radius = goalData[7].radius;

        ++obj->state;
        /*fallthrough*/

    case 1:
        ////////通常時////////
        break;
    }
}

void setGoal8(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:

        //9枚目
        obj->scale = { 0.6f,0.6f };
        obj->color = { 1,1,1,1 };
        obj->spr = goalData[8].spr;
        obj->texPos = goalData[8].texPos;
        obj->texSize = goalData[8].texSize;
        obj->pivot = goalData[8].pivot;
        obj->radius = goalData[8].radius;

        ++obj->state;
        /*fallthrough*/

    case 1:
        ////////通常時////////

        break;
    }

}

void naiki(OBJ2D* obj)
{
    switch (obj->state)
    {
    case 0:

        //9枚目
        obj->scale = { 0.5f,0.5f };
        obj->color = { 1,1,1,1 };
        obj->spr = goalData[9].spr;
        obj->texPos = goalData[9].texPos;
        obj->texSize = goalData[9].texSize;
        obj->pivot = goalData[9].pivot;
        obj->radius = goalData[9].radius;

        ++obj->state;
        /*fallthrough*/

    case 1:
        ////////通常時////////
        goal[9].pos.x = right_footX-10;
        goal[9].pos.y = right_footY-15;

        break;
    }
}

