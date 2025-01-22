#include "all.h"

extern OBJ2D player;
extern OBJ2D goal[GOAL_MAX];
extern OBJ2D boal;

extern float player_angle2;

//当たり判定
bool hitCheckCircle(VECTOR2 pos1, float r1, VECTOR2 pos2, float r2) {
    float dx = pos2.x - pos1.x;
    float dy = pos2.y - pos1.y;
    float r = r1 + r2;

    if (dx * dx + dy * dy <= r * r)
        return true;

    return false;
}

bool hitCheck(OBJ2D* obj1, OBJ2D* obj2) {
    return hitCheckCircle(
        obj1->pos + obj1->offset, obj1->radius,
        obj2->pos + obj2->offset, obj2->radius
    );
}

void judge()
{

    //判定
    for (int i = 0; i < 9; ++i) {
        if (goal[i].moveAlg == -1) continue;
        

        if (hitCheck(&boal, &goal[i]))
        {
            goal[i].moveAlg = -1;
            game_score();
            music::play(5, false);
            music::setVolume(5, 0.5f);
            music::setVolume(1, 0.2f);
            music::setVolume(3, 0.1f);

            if (goal[i].moveAlg == -1) {
                nextScene = SCENE_RESULT;
            }
        }
    }

    //ボールと足
    if (hitCheck(&boal, &goal[9]))
    {
        if (player_angle2 < 60)
        {

            boal.speed.x = -25.0f;
            boal.speed.y = -30.0f;
            boal_moveX();
            music::play(4, false);
            music::setVolume(4, 1.5f);

        }

        if (player_angle2 < 30)
        {

            boal.speed.x = -20.0f;
            boal.speed.y = -50.0f;
            boal_moveX();
            music::play(4, false);
            music::setVolume(4, 1.5f);

        }
        if (player_angle2 < 1)
        {

            boal.speed.x = -30.0f;
            boal.speed.y = -70.0f;
            boal_moveX();
            music::play(4, false);
            music::setVolume(4, 1.5f);
       
        }
    }
   
}