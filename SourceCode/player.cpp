#include "all.h"

int player_state;

int scroll_position_X;
int scroll_position_Y;


extern float scrollValue;

//OBJ2D�^�̕ϐ�player��錾
OBJ2D player;

Sprite* sprPlayer;

//--------------------------------------
//  �v���C���[�̏����ݒ�
//--------------------------------------
void player_init()
{
    //player_state��0
    player_state = 0;
    
}
//--------------------------------------
//  �v���C���[�̏I������
//--------------------------------------
void player_deinit()
{
    //sprPlayer��j��
    safe_delete(sprPlayer);
}

//--------------------------------------
//  �v���C���[�̍X�V����
//--------------------------------------
void player_update()
{
    switch (player_state)
    {
    case 0:
        //////// �����ݒ� ////////

        //�v���C���[�̉摜��ǂݍ���
        sprPlayer = sprite_load(L"./Data/Images/player_02.png");

        ++player_state;
        /*fallthrough*/

    case 1:
        //////// �p�����[�^�̐ݒ� ////////

        //player�̃p�����[�^�ݒ�
        player = {};
        player.timer = 0;
        player.pos = { SCREEN_W * 0.5f,SCREEN_H * 0.5f };
        player.scale = { 0.5f,0.5f };
        player.texPos = { 0,0 };
        player.texSize = { PLAYER_TEX_W ,PLAYER_TEX_H };
        player.pivot = { PLAYER_PIVOT_X,PLAYER_PIVOT_Y };
        player.color = { 1.0f,1.0f,1.0f,1.0f };
        player.radius = 20.0f;
        player.offset = { 0,0 };
        player.HitBack = 0;


        ++player_state;
        /*fallthrough*/

    case 2:
        //////// �ʏ펞 ////////

        //player_moveX�EY���Ă�
        player_moveY();
        player_moveX();

        // �ʒu�ɑ��x�𑫂�
        player.pos += player.speed;
        player.pos.y += player.HitBack;

        // �v���C���[�̏㉺���E�̃G���A�`�F�b�N
        if (player.pos.x < 100 + WALL_RIGHT) {
            player.pos.x = 100 + WALL_RIGHT;
        }
        if (player.pos.x > WALL_LEFT - 100) {
            player.pos.x = WALL_LEFT - 100;
        }

        if (player.pos.y > WALL_DOWN) {
            player.pos.y = WALL_DOWN;
        }

        break;
    }
}

void player_render()
{
    //�v���C���[�̕`��
    sprite_render(sprPlayer, player.pos.x + scroll_position_X, player.pos.y + scroll_position_Y, player.scale.x, player.scale.y, player.texPos.x, player.texPos.y, player.texSize.x, player.texSize.y, player.pivot.x, player.pivot.y,
        ToRadian(0), player.color.x, player.color.y);
    //primitive::rect(player.pos.x - 100, player.pos.y - 100, 200 * hp / 100, 15, 0, 0, ToRadian(0), 0, 1, 0);


}

void player_moveY()
{
    if (STATE(0) & PAD_UP && !(STATE(0) & PAD_DOWN))
    {
        player.HitBack -= PLAYER_ACCEL_Y / 2;
    }
    if (STATE(0) & PAD_DOWN && !(STATE(0) & PAD_UP))
    {
        player.speed.y += PLAYER_ACCEL_Y * 2;
        player.scale.y = 0.5f;

    }
    else {
        if (player.speed.y > 0) {
            player.speed.y -= PLAYER_DECEL_Y;
            if (player.speed.y < 0)
                player.speed.y = 0.0f;

        }

        if (player.speed.y < 0) {
            player.speed.y += PLAYER_DECEL_Y;
            if (player.speed.y > 0)
                player.speed.y = 0.0f;

        }
    }
    if (player.speed.y >= PLAYER_SPEED_Y_MAX) {
        player.speed.y = PLAYER_SPEED_Y_MAX;
    }

}



void player_moveX()
{

    //�C�ӂ̑���ɂ��ړ�
    if (STATE(0) & PAD_LEFT && !(STATE(0) & PAD_RIGHT)) {
        player.speed.x -= PLAYER_ACCEL_X;
        player.scale.x = 0.5f;

    }
    else if (STATE(0) & PAD_RIGHT && !(STATE(0) & PAD_LEFT)) {
        player.speed.x += PLAYER_ACCEL_X;
        player.scale.x = 0.5f;

    }
    else {
        if (player.speed.x > 0) {
            player.speed.x -= PLAYER_DECEL_X;
            if (player.speed.x < 0) {
                player.speed.x = 0.0f;
            }
        }

        if (player.speed.x < 0) {
            player.speed.x += PLAYER_DECEL_X;
            if (player.speed.x > 0) {
                player.speed.x = 0.0f;
            }
        }

    }
    if (player.speed.x >= PLAYER_SPEED_X_MAX) {
        player.speed.x = PLAYER_SPEED_X_MAX;
    }


    if (player.speed.x <= -PLAYER_SPEED_X_MAX) {
        player.speed.x = -PLAYER_SPEED_X_MAX;
    }
}
