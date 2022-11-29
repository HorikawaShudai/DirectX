//===========================================================
//
//ポリゴンの処理操作
//Author:堀川萩大
//
//===========================================================
#ifndef _FIELD_H_
#define _FIELD_H_
#include "main.h"

//プロトタイプ宣言
void InitField(void);
void UninitField(void);
void UpdataField(void);
void DrawField(void);
void SetField(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
#endif