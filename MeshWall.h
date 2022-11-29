//===========================================================
//
//ポリゴンの処理操作
//Author:堀川萩大
//
//===========================================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_
#include "main.h"

//プロトタイプ宣言
void InitMeshWall(void);
void UninitMeshWall(void);
void UpdataMeshWall(void);
void DrawMeshWall(void);
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
bool ColissionWall(D3DXVECTOR3 pos);
#endif