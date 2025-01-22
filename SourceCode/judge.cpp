#include "all.h"

extern OBJ2D player;
extern OBJ2D goal[GOAL_MAX];
extern OBJ2D boal;

extern float player_angle2;

//“–‚½‚è”»’è
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

    //”»’è
    for (int i = 0; i < 9; ++i) {
        if (goal[i].moveAlg == -1) continue;
        

        if (hitCheck(&boal, &goal[i]))
        {
            goal[i].moveAlg = -1;
            game_score();
            if (goal[i].moveAlg == -1) {
                nextScene = SCENE_RESULT;
            }
        }
    }

    //ƒ{[ƒ‹‚Æ‘«
    if (hitCheck(&boal, &goal[9]))
    {
        if (player_angle2 < 60)
        {

            boal.speed.x = -25.0f;
            boal.speed.y = -30.0f;
            boal_moveX();
        }

        if (player_angle2 < 30)
        {

            boal.speed.x = -20.0f;
            boal.speed.y = -50.0f;
            boal_moveX();

        }
        if (player_angle2 < 1)
        {

            boal.speed.x = -30.0f;
            boal.speed.y = -70.0f;
            boal_moveX();
       
        }
    }
   
}