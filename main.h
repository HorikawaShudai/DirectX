//===========================================================
//
//ポリゴンの処理操作
//Author:堀川萩大
//
//===========================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#include <windows.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800) //ビルド時の警告対処用ビルド
#include "dinput.h"

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")	//システム時刻の取得
#pragma comment(lib,"dinput8.lib")

#define SCREEN_WIDTH			(1280)	 //ウィンドウサイズ（幅）
#define SCREEN_HEIGHT			(720)	 //ウィンドウサイズ（高さ）
#define FVF_VERTEX_2D (D3DFVF_XYZRHW |D3DFVF_DIFFUSE |D3DFVF_TEX1) //頂点フォーマット(2D)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)


typedef struct
{
	D3DXVECTOR3 pos; //頂点座標	
	float rhw;		 //座標変換用係数(1.0fで固定)
	D3DCOLOR col;	 //頂点カラー
	D3DXVECTOR2 tex; //テクスチャ座標
}VERTEX_2D;


typedef struct
{
	D3DXVECTOR3 pos;		//頂点座標
	D3DXVECTOR3 nor;		//法線ベクトル
	D3DCOLOR col;			//頂点カラー
	D3DXVECTOR2 tex;		//テクスチャ座標
}VERTEX_3D;

//プロタイプ宣言
LPDIRECT3DDEVICE9 GetDevice(void);
LPD3DXFONT GetFont(void);

#endif

