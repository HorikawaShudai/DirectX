//===========================================================
//
//playerの処理操作
//Author:堀川萩大
//
//===========================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
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
	D3DXVECTOR3 VtxMinPlayer;
	D3DXVECTOR3 VtxMaxPlayer;
	D3DXMATRIX  mtxWorldPlayer;
	int nIdxShadow;
}PLAYER;

//プロトタイプ宣言
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER GetPlayer(void);

#endif
