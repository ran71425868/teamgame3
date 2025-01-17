#include "all.h"

extern OBJ2D player;
extern OBJ2D goal[GOAL_MAX];
extern OBJ2D boal;

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
    for (int i = 0; i < GOAL_MAX; ++i) {
        if (goal[i].moveAlg == -1) continue;
        

        if (hitCheck(&boal, &goal[i]))
        {
            boal.moveAlg = -1;
            goal[i].moveAlg = -1;
           

            //scene_reset();
           /* if (&goal[i] == 0) {
                nextScene = SCENE_CLEAR;
            }*/
        }
    }
}
//ƒS[ƒ‹
void goaljudge()
{
    
}