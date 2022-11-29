//===========================================================
//
//ポリゴンの処理操作
//Author:堀川萩大
//
//===========================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_
#include "main.h"

//プロトタイプ宣言
void InitShadow(void);
void UninitShadow(void);
void UpdataShadow(void);
void DrawShadow(void);
int SetShadow(void);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);
void FinishShadow(int nIdxShadow);
#endif