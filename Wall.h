//===========================================================
//
//ポリゴンの処理操作
//Author:堀川萩大
//
//===========================================================
#ifndef _WALL_H_
#define _WALL_H_
#include "main.h"

//プロトタイプ宣言
void InitWall(void);
void UninitWall(void);
void UpdataWall(void);
void DrawWall(void);

void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
#endif