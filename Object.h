//===========================================================
//
//playerの処理操作
//Author:堀川萩大
//
//===========================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 Oldpos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 Destrot;
	D3DXVECTOR3 Diffrot;
	D3DXVECTOR3 moveP;
	D3DXVECTOR3 moveR;
	D3DXVECTOR3 VtxMinObject;
	D3DXVECTOR3 VtxMaxObject;
	D3DXMATRIX  mtxWorldObject;
	int nIdxShadow;
}OBJECT;

//プロトタイプ宣言
void InitObject(void);
void UninitObject(void);
void UpdateObject(void);
void DrawObject(void);
OBJECT GetObject(void);

#endif
