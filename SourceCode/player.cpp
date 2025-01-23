#include "all.h"

int player_state;

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


float right_footX;
float right_footY;

float left_footX;
float left_footY;

float scroll_position_X;

extern float scrollValue;

//OBJ2D�^�̕ϐ�player��錾
OBJ2D player;
extern OBJ2D goal[GOAL_MAX];

Sprite* sprBody;
Sprite* sprLeftArm;
Sprite* sprRightArm;
Sprite* sprThighs;
Sprite* sprLeftLeg;
Sprite* sprRightLeg;
Sprite* sprNaiki;

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
    safe_delete(sprBody);
    safe_delete(sprLeftArm);
    safe_delete(sprRightArm);
    safe_delete(sprThighs);
    safe_delete(sprLeftLeg);
    safe_delete(sprRightLeg);
}

//--------------------------------------
//  �v���C���[�̍X�V����
//--------------------------------------

bool right_ground = false;
bool left_ground = false;

VECTOR2 body;
void player_update()
{
    switch (player_state)
    {
    case 0:
        //////// �����ݒ� ////////

        //�v���C���[�̉摜��ǂݍ���
        sprBody = sprite_load(L"./Data/Images/upper_body.png");
        sprLeftArm = sprite_load(L"./Data/Images/left_arm.png");
        sprRightArm = sprite_load(L"./Data/Images/right_arm.png");
        sprThighs = sprite_load(L"./Data/Images/thighs.png");
        sprLeftLeg = sprite_load(L"./Data/Images/left_leg.png");
        sprRightLeg = sprite_load(L"./Data/Images/right_leg.png");

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
        body = { 0 , 0 };

        ++player_state;
        /*fallthrough*/

    case 2:
        //////// �ʏ펞 ////////

        //���Ƀv���C���[�̈ʒu������
        right_waistX = player.pos.x;
        right_waistY = player.pos.y;

        left_waistX = player.pos.x + 60;
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
       right_footX = right_knee_PosX + cosf(ToRadian(player_angle2 + 90.0)) * 128.0f;
       right_footY = right_knee_PosY + sinf(ToRadian(player_angle2 + 90.0)) * 128.0f;

       //����
       left_footX = left_knee_PosX + cosf(ToRadian(player_angle4 + 90.0)) * 128.0f;
       left_footY = left_knee_PosY + sinf(ToRadian(player_angle4 + 90.0)) * 128.0f;
       
       if (right_footY > GROUND_Y)
       {
           right_footY = GROUND_Y;
          
           right_ground = true;
           player.speed.y = 0.0f;

           
           
           if (!left_ground && right_ground)
           {
               player_angle = 0;
               player_angle2 = 0;
           }

           
       }

       else
       {
            right_ground = false;
       }

       if (left_footY > GROUND_Y)
       {
           left_footY = GROUND_Y;
         
           left_ground = true;
           player.speed.y = 0.0f;

           
           if (!right_ground && left_ground)
           {
               player_angle3 = 0;
               player_angle4 = 0;
           }

       }

       else
       {
           
           left_ground = false;
       }

       //�G�Œ�
       //�E�G
       right_knee_PosX = right_footX + cosf(ToRadian(player_angle2 - 90.0)) * 128.0f;
       right_knee_PosY = right_footY + sinf(ToRadian(player_angle2 - 90.0)) * 128.0f;

       //���G
       left_knee_PosX = left_footX + cosf(ToRadian(player_angle4 - 90.0)) * 128.0f;
       left_knee_PosY = left_footY + sinf(ToRadian(player_angle4 - 90.0)) * 128.0f;

       //�������Œ�
       //�E��
       right_waistX = right_knee_PosX + cosf(ToRadian(player_angle - 90.0)) * 128.0f;
       right_waistY = right_knee_PosY + sinf(ToRadian(player_angle - 90.0)) * 128.0f;
       
       //����
       left_waistX = left_knee_PosX + cosf(ToRadian(player_angle3 - 90.0)) * 128.0f;
       left_waistY = left_knee_PosY + sinf(ToRadian(player_angle3 - 90.0)) * 128.0f;


       // �E���������̃x�N�g��
       VECTOR2 footVec(left_waistX - right_waistX, left_waistY - right_waistY);
       // ����
       float dist = sqrtf(footVec.x * footVec.x + footVec.y * footVec.y);
       footVec.x /= dist;
       footVec.y /= dist;

       dist /= 2;

       body.x = right_waistX + footVec.x * dist;
       body.y = right_waistY + footVec.y * dist;

       // �O�̃t���[���Œn�ʂɐڒn������
        break;
       
    }
}

void player_render()
{
    //�v���C���[�̕`��
    
     
    //���r
    sprite_render(sprLeftArm, body.x + 90, body.y - 150, player.scale.x * 1.5, player.scale.y * 1.5, player.texPos.x, player.texPos.y, player.texSize.x, player.texSize.y, player.pivot.x, player.pivot.y,
        ToRadian(0), player.color.x, player.color.y);
     
    //�E�r
    sprite_render(sprRightArm, body.x-100, body.y-160, player.scale.x * 2, player.scale.y*2, player.texPos.x, player.texPos.y, player.texSize.x, player.texSize.y, player.pivot.x, player.pivot.y,
        ToRadian(0), player.color.x, player.color.y);
     
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

    //��
    sprite_render(sprBody, body.x, body.y, player.scale.x * 2.8, player.scale.y * 2.8, player.texPos.x, player.texPos.y, player.texSize.x, player.texSize.y, player.pivot.x, player.pivot.y + player.texSize.y - 20.0f,
        ToRadian(0), player.color.x, player.color.y);

    debug::setString("right_ground%d", right_ground);
    debug::setString("left_ground%d", left_ground);

}

void player_moveY()
{
    
    //�d��
    if (!right_ground && !left_ground)
    {
        player.speed.y += GRAVITY;
    }

  //--------------------------------------------------------------
  // �E������
  //--------------------------------------------------------------

    //�E����������ɓ���������
    if (STATE(0) & PAD_UP && !(STATE(0) & PAD_DOWN))
    {
        //��]���x
        player_angle += 1.0f;

        //�E����������ɓ��������E�l
        if (player_angle > 90.0f)
            player_angle = 90.0f;

        //�����������ɐH�����܂Ȃ�����
        if (player_angle2 < 0)
            player_angle = 0;
        
    }

    //�E�����������ɓ���������
    if (STATE(0) & PAD_DOWN && !(STATE(0) & PAD_UP))
    {
        //��]���x
        player_angle -= 1.0f;

        //�E�����������ɓ��������E�l
        if (player_angle < 0.0f)
            player_angle = 0.0f;

        //���������~�낷�Ƒ����~��鏈��
        if (player_angle2 <= 40)
        {
            player_angle2 -= 1.0f;

            //�����������ɐH�����܂Ȃ�����
            if (player_angle2 < 0) {
                player_angle2 += 1.0f;
            }
        }

    }

   //--------------------------------------------------------------
   // ��������
   //--------------------------------------------------------------

    //������������ɓ���������
    if (STATE(0) & PAD_L1 && !(STATE(0) & PAD_R1))
    {
        //��]���x
        player_angle3 += 1.0f;

        //������������ɓ��������E�l
        if (player_angle3 > 90.0f)
            player_angle3 = 90.0f;

        //�����������ɐH�����܂Ȃ�����
        if (player_angle4 < 0)
            player_angle3 = 0;
    }

    //�������������ɓ���������
    if (STATE(0) & PAD_R1 && !(STATE(0) & PAD_L1))
    {
        //��]���x
        player_angle3 -= 1.0f;

        //�������������ɓ��������E�l
        if (player_angle3 < 0.0f)
            player_angle3 = 0.0f;

        //���������~�낷�Ƒ����~��鏈��
        if (player_angle4 <= 40)
        {
            player_angle4 -= 1.0f;

            //�����������ɐH�����܂Ȃ�����
            if (player_angle4 < 0) {
                player_angle4 += 1.0f;
            }
        }
    }
}

void player_moveX()
{
   //--------------------------------------------------------------
   // �E��
   //--------------------------------------------------------------
    
    //�E����O�ɓ���������
    if (STATE(0) & PAD_LEFT && !(STATE(0) & PAD_RIGHT)) 
    {
        
        //�ړ�����
        scrollValue += 2;
        scroll_position_X += 2;
        boal.pos.x += 2;

        for (int i = 0; i < 9; i++)
        {
            goal[i].pos.x += 2;
        }
        
        //��]���x
        player_angle2 += 1.0f;

        if (scrollValue > 750)
        {
            scrollValue -= 2;
            scroll_position_X -= 2;
            boal.pos.x -= 2;
            for (int i = 0; i < 9; i++)
            {
                goal[i].pos.x -= 2;
            }
        }

        //�E����O�ɂ�����E�l
        if (player_angle2 > 40.0f) 
        {
            player_angle2 = 40.0f;
            //�ړ���~
            scrollValue -= 2;
            scroll_position_X -= 2;
            boal.pos.x -= 2;

            for (int i = 0; i < 9; i++)
            {
                goal[i].pos.x -= 2;
            }
        }

        //�G�̉���𒴂��Ȃ�����
        if (player_angle <= 40.0f && player_angle2 > 0)
        {
            player_angle2 -= 1.0f;
            //�ړ���~
            scrollValue -= 2;
            scroll_position_X -= 2;
            boal.pos.x -= 2;

            for (int i = 0; i < 9; i++)
            {
                goal[i].pos.x -= 2;
            }
        }
           
        if (scrollValue > 1920)
        {
            scrollValue = 1920;
            
            goal[0].pos.x = scrollValue - scrollValue + 100;
            goal[3].pos.x = scrollValue - scrollValue + 100;
            goal[6].pos.x = scrollValue - scrollValue + 100;

            goal[1].pos.x = scrollValue - scrollValue + 300;
            goal[4].pos.x = scrollValue - scrollValue + 300;
            goal[7].pos.x = scrollValue - scrollValue + 300;

            goal[2].pos.x = scrollValue - scrollValue + 500;
            goal[5].pos.x = scrollValue - scrollValue + 500;
            goal[8].pos.x = scrollValue - scrollValue + 500;
        }


    }

    //�E�������ɓ���������
    if (STATE(0) & PAD_RIGHT && !(STATE(0) & PAD_LEFT)) 
    {
        //��]���x
        player_angle2 -= 1.0f;

        //�E�������ɂ�����E�l
        if (player_angle2 < -90.0f)
            player_angle2 = -90.0f;

        //�G�ɑ����H�����܂Ȃ�����
        if (player_angle >= 90)
            player_angle2 += 1.0f;
       

    }

    //--------------------------------------------------------------
    // ����
    //--------------------------------------------------------------

    //������O�ɓ���������
    if (STATE(0) & PAD_L3 && !(STATE(0) & PAD_R3))
    {
        //�ړ�����
        scrollValue += 2;
        scroll_position_X += 2;
        boal.pos.x += 2;

        for (int i = 0; i < 9; i++)
        {
            goal[i].pos.x += 2;
        }
        //��]���x
        player_angle4 += 1.0f;

        //������O�ɂ�����E�l
        if (player_angle4 > 60.0f) 
        {
            player_angle4 = 60.0f;
            //�ړ���~
            scrollValue -= 2;
            scroll_position_X -= 2;
            boal.pos.x -= 2;

            for (int i = 0; i < 9; i++)
            {
                goal[i].pos.x -= 2;
            }
        }

        //�G�̉���𒴂��Ȃ�����
        if (player_angle3 <= 40.0f && player_angle4 > 0)
        {
            player_angle4 -= 1.0f;
            //�ړ���~
            scrollValue -= 2;
            scroll_position_X -= 2;
            boal.pos.x -= 2;

            for (int i = 0; i < 9; i++)
            {
                goal[i].pos.x -= 2;
            }
        }

        if (scrollValue > 1920)
        {
            scrollValue = 1920;
            
            goal[0].pos.x = scrollValue - scrollValue + 100;
            goal[3].pos.x = scrollValue - scrollValue + 100;
            goal[6].pos.x = scrollValue - scrollValue + 100;

            goal[1].pos.x = scrollValue - scrollValue + 300;
            goal[4].pos.x = scrollValue - scrollValue + 300;
            goal[7].pos.x = scrollValue - scrollValue + 300;

            goal[2].pos.x = scrollValue - scrollValue + 500;
            goal[5].pos.x = scrollValue - scrollValue + 500;
            goal[8].pos.x = scrollValue - scrollValue + 500;
        }
    }

    //���������ɓ���������
    if (STATE(0) & PAD_R3 && !(STATE(0) & PAD_L3))
    {
        //��]���x
        player_angle4 -= 1.0f;

        //���������ɂ�����E�l
        if (player_angle4 < -60.0f)
            player_angle4 = -60.0f;

        //�G�ɑ����H�����܂Ȃ�����
        if (player_angle3 >= 90)
            player_angle4 += 1.0f;
    }

    //����������
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
    //���x�����ɂ���
    if (player.speed.x >= PLAYER_SPEED_X_MAX)
        player.speed.x = PLAYER_SPEED_X_MAX;

    if (player.speed.x <= -PLAYER_SPEED_X_MAX)
        player.speed.x = -PLAYER_SPEED_X_MAX;

}
