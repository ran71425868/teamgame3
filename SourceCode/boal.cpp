#include "all.h"


int boal_state;
float speed;
bool boalground;

int boalflug;
int boalCount;

extern OBJ2D goal[GOAL_MAX];

extern float scrollValue;
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
    speed = 0;
    boalflug = 0;
    boalCount = 3;
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
        boal.pos = {0, GROUND_Y - 30};
        boal.scale = { 0.5f,0.5f };
        boal.texPos = { 0,0 };
        boal.texSize = { BOAL_TEX_W ,BOAL_TEX_H };
        boal.pivot = { BOAL_PIVOT_X,BOAL_PIVOT_Y };
        boal.color = { 1.0f,1.0f,1.0f,1.0f };
        boal.radius = 34.0f;
        boal.offset = { 0,0 };

       

        ++boal_state;
        /*fallthrough*/

    case 2:
        //////// �ʏ펞 ////////

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
    
    primitive::circle(boal.pos,
        boal.radius, { 1, 1 }, ToRadian(0), { 1, 0, 0, 0.2f }
    );
    debug::setString("boalflug%d", boalflug);
    debug::setString("boalCount%d", boalCount);
   
}
void boal_moveX()
{
    boalflug = 1;
    /*if (boal.pos.y >= 970)
    {
        if (boalCount > 0)
            boalCount -= 1;
    }*/
    if (boalflug > 0 && boal.pos.y >= 970)
    {
        boal.speed.x = 0.0f;
    }
}

void boal_moveY()
{
    boal.speed.y += GRAVITY;
    

}


