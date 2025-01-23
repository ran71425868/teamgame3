#include "all.h"

extern OBJ2D player;
extern OBJ2D goal[GOAL_MAX];
extern OBJ2D boal;

int shoot=0;

extern int player_state;
extern int boal_state;
extern int boalflug;
extern int boalCount;
extern int boal_timer;
extern float power;


extern float scrollValue;
extern float scroll_position_X;
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
        shoot = 1;
        player.pos.x = 1920;
        scrollValue = 1920;
        boal.pos.x =1720 ;

        goal[0].pos.x = scrollValue - scrollValue + 100;
        goal[3].pos.x = scrollValue - scrollValue + 100;
        goal[6].pos.x = scrollValue - scrollValue + 100;

        goal[1].pos.x = scrollValue - scrollValue + 300;
        goal[4].pos.x = scrollValue - scrollValue + 300;
        goal[7].pos.x = scrollValue - scrollValue + 300;

        goal[2].pos.x = scrollValue - scrollValue + 500;
        goal[5].pos.x = scrollValue - scrollValue + 500;
        goal[8].pos.x = scrollValue - scrollValue + 500;

        if (player_angle2 < 40)
        {

            boal.speed.x = -25.0f;
            boal.speed.y = -30.0f*power;
            sound::play(XWB_SE, XWB_SE_HIT);

        }
        if (player_angle2 < 20)
        {

            boal.speed.x = -25.0f;
            boal.speed.y = -20.0f * power;
            sound::play(XWB_SE, XWB_SE_HIT);

        }

    }
   
}