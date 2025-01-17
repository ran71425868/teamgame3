#include "all.h"

int     goal_state;
OBJ2D   goal[GOAL_MAX];

struct GOAL_DATA {
    Sprite* spr;
    const wchar_t* filePath;
    VECTOR2         texPos;
    VECTOR2         texSize;
    VECTOR2         pivot;
    float           radius;
}
goalData[] = {
{ NULL,   L"./Data/Images/01.png", { 0, 0 }, { 229, 239 }, { 114.5, 119.5 }, 70},
{ NULL,   L"./Data/Images/02.png", { 0, 0 }, { 227, 239 }, { 113.5, 119.5 }, 70},
{ NULL,   L"./Data/Images/03.png", { 0, 0 }, { 228, 239 }, { 114,   119.5 }, 70},
{ NULL,   L"./Data/Images/04.png", { 0, 0 }, { 229, 240 }, { 114.5, 120 },   70},
{ NULL,   L"./Data/Images/05.png", { 0, 0 }, { 229, 238 }, { 114.5, 119 },   70},
{ NULL,   L"./Data/Images/06.png", { 0, 0 }, { 228, 238 }, { 114,   119 },   70},
{ NULL,   L"./Data/Images/07.png", { 0, 0 }, { 226, 239 }, { 113,   119.5 }, 70},
{ NULL,   L"./Data/Images/08.png", { 0, 0 }, { 226, 239 }, { 113,   119.5 }, 70},
{ NULL,   L"./Data/Images/09.png", { 0, 0 }, { 227, 238 }, { 113.5, 119 },   70},
};


struct GOAL_SET {
    int             goalType;
    VECTOR2         pos;
}goalSet[] = {
    { 0, { 100, 400 }},
    { 0, { 300, 400 }},
    { 0, { 500, 400 }},
    { 0, { 100, 600 }},
    { 0, { 300, 600 }},
    { 0, { 500, 600 }},
    { 0, { 100, 800 }},
    { 0, { 300, 800 }},
    { 0, { 500, 800 }},
    {-1,{-1,-1}},
};

Sprite* sprGoal;



void goal_init()
{
    goal_state = 0;
   
}

void goal_deinit()
{
    int dataNum = ARRAYSIZE(goalData);
    for (int i = 0; i < dataNum; ++i) {
        safe_delete(goalData[i].spr);
    }
}

void goal_update()
{
    switch (goal_state)
    {
    case 0:
    {
        int dataNum = sizeof(goalData) / sizeof(GOAL_DATA);


        for (int i = 0; i < dataNum; ++i) {
            goalData[i].spr = sprite_load(goalData[i].filePath);

        }



    }

    ++goal_state;

    case 1:

        for (int i = 0; i < GOAL_MAX; ++i) {
            goal[i] = {};
            goal[i].moveAlg = -1;

            goal[i].spr = goalData[i].spr;
            goal[i].texPos = goalData[i].texPos;
            goal[i].texSize = goalData[i].texSize;
            goal[i].pivot = goalData[i].pivot;
        }

        for (int i = 0; goalSet[i].goalType >= 0; i++) {
            OBJ2D* p = searchSet0(goal, GOAL_MAX, goalSet[i].goalType, goalSet[i].pos);
            if (!p)break;
        }
        ++goal_state;

    case 2:
 

        break;

    }
}
void goal_render() {
    for (int i = 0; i < GOAL_MAX; ++i)
    {
        if (goal[i].moveAlg == -1)continue;

        sprite_render(
            goal[i].spr,
            goal[i].pos.x, goal[i].pos.y,
            0.6f, 0.6f,
            goal[i].texPos.x, goal[i].texPos.y,
            goal[i].texSize.x, goal[i].texSize.y,
            goal[i].pivot.x, goal[i].pivot.y,
            ToRadian(0),
            1,1,1,1
        );
        primitive::circle(goal[i].pos,
        goalData[i].radius, {1, 1}, ToRadian(0), {1, 0, 0, 0.2f}
    );
    }
}
void moveGoal0(OBJ2D* obj)
{

    switch (obj->state) {

    case 0:

        obj->scale = { 0.6f,0.6f };
        obj->color = { 1,1,1,1 };
        obj->spr = goalData[0].spr;
        obj->texPos = goalData[0].texPos;
        obj->texSize = goalData[0].texSize;
        obj->pivot = goalData[0].pivot;
        obj->radius = goalData[0].radius;

        //++obj->state;

    //case 1:
        break;

    }
}

