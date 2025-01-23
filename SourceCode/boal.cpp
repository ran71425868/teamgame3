#include "all.h"
#include	<stdlib.h>
#include	<time.h>

int boal_state;
int boal_timer;

bool boalground;

int boalflug;
int boalCount;
int rnd;
float power;

extern OBJ2D goal[GOAL_MAX];

extern int player_state;
extern float scrollValue;
extern float scroll_position_X;
extern float player_angle2;

//OBJ2D�^�̕ϐ�boal��錾
OBJ2D boal;

Sprite* sprBoal;

//--------------------------------------
//  �v���C���[�̏����ݒ�
//--------------------------------------
void boal_init()
{
    //boal_state��0
    boal_state = 0;
    boal_timer = 0;

    boalflug = 2;
    boalCount = 5;
    rnd = 0;
    power = 0;

    
}
//--------------------------------------
//  �v���C���[�̏I������
//--------------------------------------
void boal_deinit()
{
    //sprPlayer��j��
    safe_delete(sprBoal);
}

//--------------------------------------
//  �X�V����
//--------------------------------------
void boal_update()
{
    switch (boal_state)
    {
    case 0:
        //////// �����ݒ� ////////

        //�摜��ǂݍ���
        sprBoal = sprite_load(L"./Data/Images/boal.png");

        ++boal_state;
        /*fallthrough*/

    case 1:
        //////// �p�����[�^�̐ݒ� ////////

        //player�̃p�����[�^�ݒ�
        boal = {};
        boal.timer = 0;
        boal.pos = {scroll_position_X, GROUND_Y - 30};
        boal.scale = { 0.5f,0.5f };
        boal.texPos = { 0,0 };
        boal.texSize = { BOAL_TEX_W ,BOAL_TEX_H };
        boal.pivot = { BOAL_PIVOT_X,BOAL_PIVOT_Y };
        boal.color = { 1.0f,1.0f,1.0f,1.0f };
        boal.radius = 34.0f;
        boal.offset = { 0,0 };

        rnd = rand() % 5;

        ++boal_state;
        /*fallthrough*/

    case 2:
        //////// �ʏ펞 ////////

        
        
        switch (rnd)
        {
        case 0:
            power = 1;
            break;
        case 1:
            power = 1.1;
            break;
        case 2:
            power = 1.2;
            break;
        case 3:
            power = 1.3;
            break;
        case 4:
            power = 1.35;
            break;
        }


        //player_moveX�EY���Ă�
        boal_moveY();

        // �ʒu�ɑ��x�𑫂�
        boal.pos += boal.speed;
        
        boalground = false;
        if (boal.pos.y > 970)
        {
            boal.speed.y = 0.0f;
            boal.pos.y = 970;
            boalground = true;
        }

        if (boal.speed.x < 0)
        {
            if (boal_timer % 100 == 0)
            {
                if (boalflug > 0)
                {
                    boalflug--;

                }
                else if (boalflug <= 0)
                {
                    scrollValue = 0;
                    scroll_position_X = 0;

                    goal[0].pos.x = -1820 + scroll_position_X;
                    goal[3].pos.x = -1820 + scroll_position_X;
                    goal[6].pos.x = -1820 + scroll_position_X;

                    goal[1].pos.x = -1620 + scroll_position_X;
                    goal[4].pos.x = -1620 + scroll_position_X;
                    goal[7].pos.x = -1620 + scroll_position_X;

                    goal[2].pos.x = -1420 + scroll_position_X;
                    goal[5].pos.x = -1420 + scroll_position_X;
                    goal[8].pos.x = -1420 + scroll_position_X;

                    //scrollValue = -scroll_position_X;
                    
                    player_state = 0;
                    boal_state = 0;

                    if (boalCount > 0)
                    {
                        boalCount--;
                    }
                        boalflug = 2;
                    
                }
               

            }
        }


        if (boalCount == 0)
        {
            game_clear();
        }

        boal_timer++;
        
        
        break;
    }
}

void boal_render()
{
    //�`��
    sprite_render(sprBoal,
        boal.pos.x, boal.pos.y,
        boal.scale.x, boal.scale.y,
        boal.texPos.x, boal.texPos.y,
        boal.texSize.x, boal.texSize.y,
        boal.pivot.x, boal.pivot.y,
        ToRadian(0), boal.color.x, boal.color.y);
    
   /* primitive::circle(boal.pos,
        boal.radius, { 1, 1 }, ToRadian(0), { 1, 0, 0, 0.2f }
    );*/
    
    text_out(0, "power *", 1400, 150, 2, 2);
    text_out(0, std::to_string(power), 1700, 150, 2, 2);
    text_out(0, "boll *", 1500, 50, 2, 2);
    text_out(0, std::to_string(boalCount), 1700, 50, 2, 2);
   
}

void boal_moveY()
{
    boal.speed.y += GRAVITY;
}


