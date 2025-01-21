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
    
    int ten = 10;
    int score = 0;

    //”»’è
    for (int i = 0; i < 9; ++i) {
        if (goal[i].moveAlg == -1) continue;
        

        if (hitCheck(&boal, &goal[i]))
        {
           /* boal.moveAlg = -1;*/
            goal[i].moveAlg = -1;
            score += ten;

            if (goal[0].moveAlg == -1 && goal[1].moveAlg == -1 &&goal[2].moveAlg == -1) {
                score += 50;
            }
            if (goal[3].moveAlg == -1 && goal[4].moveAlg == -1 && goal[5].moveAlg == -1) {
                score += 50;
            }
            if (goal[6].moveAlg == -1 && goal[7].moveAlg == -1 && goal[8].moveAlg == -1) {
                score += 50;
            }
            if (goal[0].moveAlg == -1 && goal[3].moveAlg == -1 && goal[6].moveAlg == -1) {
                score += 50;
            }
            if (goal[1].moveAlg == -1 && goal[4].moveAlg == -1 && goal[7].moveAlg == -1) {
                score += 50;
            }
            if (goal[2].moveAlg == -1 && goal[5].moveAlg == -1 && goal[8].moveAlg == -1) {
                score += 50;
            }
            if (goal[0].moveAlg == -1 && goal[4].moveAlg == -1 && goal[8].moveAlg == -1) {
                score += 50;
            }
            if (goal[2].moveAlg == -1 && goal[4].moveAlg == -1 && goal[6].moveAlg == -1) {
                score += 50;
            }
           
            //scene_reset();
           /* if (&goal[i] == 0) {
                nextScene = SCENE_CLEAR;
            }*/
        }
    }
    //ƒ{[ƒ‹‚Æ‘«
    for (int i = 9; i < 10; i++)
    {
        if (hitCheck(&boal,&goal[i]))
        {
            game_score();
            /*boal.pos.x += 1;
            boal.pos.y += 1;*/
        }
    }
   
}
//ƒS[ƒ‹
void goaljudge()
{
    
}