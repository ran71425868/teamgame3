#include "all.h"

OBJ2D* searchSet0(OBJ2D arr[], int dataNum, int moveAlg, VECTOR2 pos)
{
    //searchSetŠÖ”‚Ìì¬
    for (int i = 0; i < dataNum; i++) {
        if (arr[i].moveAlg != -1)continue;

        arr[i].moveAlg = moveAlg;
        arr[i].pos = pos;
        return &arr[i];
    }



    return NULL;                        // ¶¬‚Å‚«‚È‚©‚Á‚½
}