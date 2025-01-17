#include "all.h"

int player_state;

int scroll_position_X;
int scroll_position_Y;

//��
float right_waistX;
float right_waistY;
float left_waistX;
float left_waistY;

//�e���p�[�c�̊p�x
float player_angle;
float player_angle2;
float player_angle3;
float player_angle4;

//�E�G
float right_knee_PosX;
float right_knee_PosY;
//���G
float left_knee_PosX;
float left_knee_PosY;

//�E��
float right_foot_PosX;
float right_foot_PosY;
//����
float left_foot_PosX;
float left_foot_PosY;

extern float scrollValue;

//OBJ2D�^�̕ϐ�player��錾
OBJ2D player;

Sprite* sprBody;
Sprite* sprLeftArm;
Sprite* sprRightArm;
Sprite* sprThighs;
Sprite* sprLeftLeg;
Sprite* sprRightLeg;
Sprite* sprPlayer;

//--------------------------------------
//  �v���C���[�̏����ݒ�
//--------------------------------------
void player_init()
{
    //player_state��0
    player_state = 0;
    player_angle = 0.0f;
    player_angle2 = 0;
    player_angle3 = 0;
    player_angle4 = 0;
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

bool ground = false;
void player_update()
{
    switch (player_state)
    {
    case 0:
        //////// �����ݒ� ////////

        //�v���C���[�̉摜��ǂݍ���
        sprPlayer = sprite_load(L"./Data/Images/3.png");
        sprLeftLeg = sprite_load(L"./Data/Images/left_leg.png");
        sprRightLeg = sprite_load(L"./Data/Images/right_leg.png");
        sprThighs = sprite_load(L"./Data/Images/thighs.png");

        ++player_state;
        /*fallthrough*/

    case 1:
        //////// �p�����[�^�̐ݒ� ////////

        //player�̃p�����[�^�ݒ�
        player = {};
        player.timer = 0;
        player.pos = { SCREEN_W * 0.5f,SCREEN_H * 0.5f };
        player.scale = { 1.0f,1.0f };
        player.texPos = { 0,0 };
        player.texSize = { PLAYER_TEX_W ,PLAYER_TEX_H };
        player.pivot = { PLAYER_PIVOT_X,PLAYER_PIVOT_Y };
        player.color = { 1.0f,1.0f,1.0f,1.0f };
        player.radius = 20.0f;
        player.offset = { 0,0 };


        ++player_state;
        /*fallthrough*/

    case 2:
        //////// �ʏ펞 ////////

        //���Ƀv���C���[�̈ʒu������
        right_waistX = player.pos.x;
        right_waistY = player.pos.y;

        left_waistX = player.pos.x + 100;
        left_waistY = player.pos.y;

        //player_moveX�EY���Ă�
        player_moveY();
        player_moveX();

        //�ʒu�ɑ��x�𑫂�
        player.pos += player.speed;

        

       //�G�E�G���̕t�������W
       //�E��
       right_knee_PosX = right_waistX + cosf(ToRadian(player_angle + 90.0)) * 128.0f;
       right_knee_PosY = right_waistY + sinf(ToRadian(player_angle + 90.0)) * 128.0f;

       //����
       left_knee_PosX = left_waistX+ cosf(ToRadian(player_angle3 + 90.0)) * 128.0f;
       left_knee_PosY = left_waistY+ sinf(ToRadian(player_angle3 + 90.0)) * 128.0f;

       //����
       //�E��
       float right_footX = right_knee_PosX + cosf(ToRadian(player_angle2 + 90.0)) * 128.0f;
       float right_footY = right_knee_PosY + sinf(ToRadian(player_angle2 + 90.0)) * 128.0f;

       //����
       float left_footX = left_knee_PosX + cosf(ToRadian(player_angle4 + 90.0)) * 128.0f;
       float left_footY = left_knee_PosY + sinf(ToRadian(player_angle4 + 90.0)) * 128.0f;

       right_foot_PosX =right_footX + cosf(ToRadian(player_angle2 - 90.0)) * 128.0f;
       right_foot_PosY =right_footY + sinf(ToRadian(player_angle2 - 90.0)) * 128.0f;

       left_foot_PosX = left_footX + cosf(ToRadian(player_angle4 - 90.0)) * 128.0f;
       left_foot_PosY = left_footY + sinf(ToRadian(player_angle4 - 90.0)) * 128.0f;

       
       if (right_footY > GROUND_Y || left_footY > GROUND_Y)
       {
           ground = true;
           player.speed.y = 0.0f;
           right_footY = GROUND_Y;
           left_footY = GROUND_Y;
       }
       else
       {
           ground = false;
       }

       //�G�Œ�
       //�E�G
       right_knee_PosX = right_footX + cosf(ToRadian(player_angle2 - 90.0)) * 128.0f;
       right_knee_PosY = right_footY + sinf(ToRadian(player_angle2 - 90.0)) * 128.0f;

       //���G
       left_knee_PosX = left_footX + cosf(ToRadian(player_angle4 - 90.0)) * 128.0f;
       left_knee_PosY = left_footY + sinf(ToRadian(player_angle4 - 90.0)) * 128.0f;

       right_foot_PosY = right_knee_PosY;
       left_foot_PosY = left_knee_PosY;

       //�������Œ�
       //�E��
       right_waistX = right_foot_PosX + cosf(ToRadian(player_angle - 90.0)) * 128.0f;
       right_waistY = right_foot_PosY + sinf(ToRadian(player_angle - 90.0)) * 128.0f;
       
       //����
       left_waistX = left_foot_PosX + cosf(ToRadian(player_angle3 - 90.0)) * 128.0f;
       left_waistY = left_foot_PosY + sinf(ToRadian(player_angle3 - 90.0)) * 128.0f;
        break;
       
    }
}

void player_render()
{
    //�v���C���[�̕`��
    // �E������
    sprite_render(sprThighs, right_waistX, right_waistY, player.scale.x, player.scale.y, player.texPos.x, player.texPos.y, player.texSize.x, player.texSize.y, player.pivot.x, player.pivot.y,
        ToRadian(player_angle), player.color.x, player.color.y); 
    // �E�G��
    sprite_render(sprRightLeg, right_knee_PosX, right_knee_PosY, player.scale.x, player.scale.y, player.texPos.x, player.texPos.y, player.texSize.x, player.texSize.y, player.pivot.x, player.pivot.y,
        ToRadian(player_angle2), player.color.x, player.color.y);

    //��������
    sprite_render(sprThighs, left_waistX, left_waistY, player.scale.x, player.scale.y, player.texPos.x, player.texPos.y, player.texSize.x, player.texSize.y, player.pivot.x, player.pivot.y,
        ToRadian(player_angle3), player.color.x, player.color.y);
   //���G��
    sprite_render(sprLeftLeg, left_knee_PosX, left_knee_PosY, player.scale.x, player.scale.y, player.texPos.x, player.texPos.y, player.texSize.x, player.texSize.y, player.pivot.x, player.pivot.y,
        ToRadian(player_angle4), player.color.x, player.color.y);

    primitive::rect(0,GROUND_Y, 1920, 80,0,0, ToRadian(0), 0, 1, 0);

    //primitive::circle({ player.pos.x + cosf(ToRadian(player_angle + 90.0)) * 128.0f,player.pos.y + sinf(ToRadian(player_angle + 90.0)) * 256.0f }, player.radius, { 1, 1 }, ToRadian(0), { 1, 0, 0, 0.2f });
}

void player_moveY()
{
    
    //�d��
    if(!ground)
        player.speed.y += GRAVITY;

    //�C�ӂ̑���ɂ��ړ�
    //�E����������ɓ���������
    if (STATE(0) & PAD_UP && !(STATE(0) & PAD_DOWN))
    {
       
        player_angle += PLAYER_ACCEL_Y;
        if (player_angle > 90.0f)
            player_angle = 90.0f;
    }

    //�E�����������ɓ���������
    if (STATE(0) & PAD_DOWN && !(STATE(0) & PAD_UP))
    {
        player_angle -= PLAYER_ACCEL_Y;
        if (player_angle < 0.0f)
            player_angle = 0.0f;

    }

    //������������ɓ���������
    if (STATE(0) & PAD_L1 && !(STATE(0) & PAD_R1))
    {
        
        player_angle3 += PLAYER_ACCEL_Y;
        if (player_angle3 > 90.0f)
            player_angle3 = 90.0f;
    }

    //�������������ɓ���������
    if (STATE(0) & PAD_R1 && !(STATE(0) & PAD_L1))
    {
        player_angle3 -= PLAYER_ACCEL_Y;
        if (player_angle3 < 0.0f)
            player_angle3 = 0.0f;
    }
}



void player_moveX()
{

    //�C�ӂ̑���ɂ��ړ�
    //�E����O�ɓ���������
    if (STATE(0) & PAD_LEFT && !(STATE(0) & PAD_RIGHT)) 
    {
        scrollValue += 2;
        player_angle2 += 1.0f;
        if (player_angle2 > 40.0f) 
        {
            player_angle2 = 40.0f;
            scrollValue -= 2;
        }
        if (player_angle <= 40.0f && player_angle2 > 0)
        {
            player_angle2 -= 1.0f;
            scrollValue -= 2;
        }
           
    }

    //�E�������ɓ���������
    if (STATE(0) & PAD_RIGHT && !(STATE(0) & PAD_LEFT)) 
    {
        //player.speed.x += PLAYER_ACCEL_X;
        player_angle2 -= 1.0f;
        if (player_angle2 < -90.0f)
            player_angle2 = -90.0f;
        

    }

    //������O�ɓ���������
    if (STATE(0) & PAD_L3 && !(STATE(0) & PAD_R3))
    {
        player_angle4 += PLAYER_ACCEL_X;
        if (player_angle4 > 60.0f)
            player_angle4 = 60.0f;

    }

    //���������ɓ���������
    if (STATE(0) & PAD_R3 && !(STATE(0) & PAD_L3))
    {
        player_angle4 -= PLAYER_ACCEL_X;
        if (player_angle4 < -60.0f)
            player_angle4 = -60.0f;

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
    if (player.speed.x >= PLAYER_SPEED_X_MAX)
        player.speed.x = PLAYER_SPEED_X_MAX;

    if (player.speed.x <= -PLAYER_SPEED_X_MAX)
        player.speed.x = -PLAYER_SPEED_X_MAX;

}
