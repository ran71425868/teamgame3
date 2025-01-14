#include "all.h"

int     goal_state;
int k;
int i;
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
{ NULL,   L"./Data/Images/01.png", { 0, 0 }, { 229, 239 }, { 40, 40 }, 45},
{ NULL,   L"./Data/Images/02.png", { 0, 0 }, { 227, 239 }, { 40, 40 }, 45},
{ NULL,   L"./Data/Images/03.png", { 0, 0 }, { 228, 239 }, { 40, 40 }, 45},
{ NULL,   L"./Data/Images/04.png", { 0, 0 }, { 229, 240 }, { 40, 40 }, 45},
{ NULL,   L"./Data/Images/05.png", { 0, 0 }, { 229, 238 }, { 40, 40 }, 45},
{ NULL,   L"./Data/Images/06.png", { 0, 0 }, { 228, 238 }, { 40, 40 }, 45},
{ NULL,   L"./Data/Images/07.png", { 0, 0 }, { 226, 239 }, { 40, 40 }, 45},
{ NULL,   L"./Data/Images/08.png", { 0, 0 }, { 226, 239 }, { 40, 40 }, 45},
{ NULL,   L"./Data/Images/09.png", { 0, 0 }, { 227, 238 }, { 40, 40 }, 45},
};


struct GOAL_SET {
    int             goalType;
    VECTOR2         pos;
}goalSet[] = {
    { 0, { 1000, 600 }},
    { 0, { 950, 600 }},
    { 0, { 1200, 600 }},
    { 0, { 1200, 600 }},
    { 0, { 950, 600 }},
    { 0, { 700, 600 }},
    { 0, { 1200, 600 }},
    { 0, { 950, 600 }},
    { 0, { 700, 600 }},
    { 1, { 1000, 600}},
    { 2, { 1200, 600}},
    { -1, { -1,  -1 }},
};

Sprite* sprGoal;



void goal_init()
{
    goal_state = 0;
    k = 0;

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
        }

        for (int i = 0; goalSet[i].goalType >= 0; i++) {
            OBJ2D* p = searchSet0(goal, GOAL_MAX, goalSet[i].goalType, goalSet[i].pos);
            if (!p)break;
        }
        ++goal_state;

    case 2:
       
        for (int i = 0; i < GOAL_MAX; ++i) {

        

            switch (goal[i].moveAlg) {
            case 0: moveGoal0(&goal[i]); break;
            }
          
        }

        break;

    }
}
void goal_render() {
    for (int i = 0; i < GOAL_MAX; ++i)
    {
        sprite_render(
            goal[i].spr,
            goal[i].pos.x, goal[i].pos.y,
            goal[i].scale.x, goal[i].scale.y,
            goal[i].texPos.x, goal[i].texPos.y,
            goal[i].texSize.x, goal[i].texSize.y,
            goal[i].pivot.x, goal[i].pivot.y,
            ToRadian(0),
            goal[i].color.x, goal[i].color.y,
            goal[i].color.z, goal[i].color.w
        );

    }
}
void moveGoal0(OBJ2D* obj)
{

    switch (obj->state) {

    case 0:

        obj->scale = { 1,1 };
        obj->color = { 1,1,1,1 };
        obj->spr = goalData[0].spr;
        obj->texPos = goalData[0].texPos;
        obj->texSize = goalData[0].texSize;
        obj->pivot = goalData[0].pivot;
        obj->radius = goalData[0].radius;

        obj->speed.x = -2.5f;

        ++obj->state;

    case 1:


        break;
    }
}

