#include "all.h"


int boal_state;


extern float scrollValue;

//OBJ2D�^�̕ϐ�player��錾
OBJ2D boal;

Sprite* sprBoal;

//--------------------------------------
//  �v���C���[�̏����ݒ�
//--------------------------------------
void boal_init()
{
    //boal_state��0
    boal_state = 0;

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
        boal.pos = { SCREEN_W * 0.3f, GROUND_Y - 30};
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
        boal_moveX();

        // �ʒu�ɑ��x�𑫂�
        //player.pos += player.speed;

        // �v���C���[�̏㉺���E�̃G���A�`�F�b�N
        /*if (player.pos.x < 100 + WALL_RIGHT) {
            player.pos.x = 100 + WALL_RIGHT;
        }
        if (player.pos.x > WALL_LEFT - 100) {
            player.pos.x = WALL_LEFT - 100;
        }*/

        /*if (player.pos.y + sinf(ToRadian(player_angle+90.0))*128.0f > WALL_DOWN) {
            player.pos.y = WALL_DOWN;
        }*/

        /*if (player.pos.y + 640.0f > GROUND_Y) {
            player.pos.y = GROUND_Y - 640.0f;
            if (player_angle > 20.0f) {

            }
        }*/
        
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
    
    //primitive::rect(player.pos.x - 100, player.pos.y - 100, 200 * hp / 100, 15, 0, 0, ToRadian(0), 0, 1, 0);

    primitive::circle(boal.pos,
        boal.radius, { 1, 1 }, ToRadian(0), { 1, 0, 0, 0.2f }
    );
}
void boal_moveX()
{
    if (STATE(0) & PAD_LEFT && !(STATE(0) & PAD_RIGHT))
    {
        boal.pos.x += 0.05;

    }
    if (STATE(0) & PAD_RIGHT && !(STATE(0) & PAD_LEFT))
    {
        boal.pos.x == 0;
    }
}
void boal_moveY()
{


}


