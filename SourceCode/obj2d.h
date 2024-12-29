#ifndef OBJ2D_H
#define OBJ2D_H

//******************************************************************************
//
//
//      obj2d.h
//
//
//******************************************************************************

//------< 構造体 >--------------------------------------------------------------
struct OBJ2D
{

    int timer;
    VECTOR2 pos;
    VECTOR2 scale;
    VECTOR2 texPos;
    VECTOR2 texSize;
    VECTOR2 pivot;
    VECTOR4 color;

    VECTOR2 speed;
    int moveAlg;
    float HitBack;
    GameLib::Sprite* spr;
    int state;

    float radius;
    VECTOR2 offset;

    float angle;

    int type;       // タイプ
    int sort;
};

//------< 関数 >----------------------------------------------------------------
OBJ2D* searchSet0(OBJ2D arr[], int dataNum, int moveAlg, VECTOR2 pos);
#endif//OBJ2D_H