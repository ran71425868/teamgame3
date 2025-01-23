#include "all.h"

extern OBJ2D player;
extern OBJ2D goal[GOAL_MAX];
extern OBJ2D boal;

extern float scrollValue;
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
            sound::play(XWB_SE, XWB_SE_BU);
            music::setVolume(5, 0.5f);
            music::setVolume(1, 0.2f);
            music::setVolume(3, 0.1f);

            if (   goal[0].moveAlg == -1 && goal[1].moveAlg == -1 && goal[2].moveAlg == -1
                && goal[3].moveAlg == -1 && goal[4].moveAlg == -1 && goal[5].moveAlg == -1
                && goal[6].moveAlg == -1 && goal[7].moveAlg == -1 && goal[8].moveAlg == -1)
            {
                game_clear();
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
            sound::play(XWB_SE, XWB_SE_HIT);

        }

        if (player_angle2 < 30)
        {

            boal.speed.x = -20.0f;
            boal.speed.y = -50.0f;
            boal_moveX();
            sound::play(XWB_SE, XWB_SE_HIT);

        }
        if (player_angle2 < 1)
        {

            boal.speed.x = -30.0f;
            boal.speed.y = -70.0f;
            boal_moveX();
            sound::play(XWB_SE, XWB_SE_HIT);
       
        }
    }
   
}