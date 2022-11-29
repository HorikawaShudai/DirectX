//===========================================================
//
//playerの処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "Wall.h"

#define MAX_WALL (50)


typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX  mtxWorld;
	bool bUse;
}WALL;

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;		//頂点バッファポイント
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;			//テクスチャポインタ
WALL g_aWall[MAX_WALL];

//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitWall(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_aWall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aWall[nCntWall].bUse = false;
	}
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) *( 4 * MAX_WALL),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall001.jpg",
		&g_pTextureWall);


	VERTEX_3D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-500.0f, 200.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(+500.0f, 200.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-500.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(+500.0f, 0.0f, 0.0f);

		//norの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;

	}
	//頂点バッファをアンロックする
	g_pVtxBuffWall->Unlock();
	//壁を設置
	SetWall(D3DXVECTOR3(   0.0f, 0.0f, 500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetWall(D3DXVECTOR3(-500.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f,-1.57f, 0.0f));
	SetWall(D3DXVECTOR3( 500.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetWall(D3DXVECTOR3(   0.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
}

//=========================================================================================================
//壁の終了処理
//=========================================================================================================
void UninitWall(void)
{
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}

//=========================================================================================================
//壁の更新処理
//=========================================================================================================
void UpdataWall(void)
{

}

//=========================================================================================================
//壁の描画処理
//=========================================================================================================
void DrawWall(void)
{
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == true)
		{
			//デバイスの取得
			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

											//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aWall[nCntWall].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aWall[nCntWall].rot.y, g_aWall[nCntWall].rot.x, g_aWall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aWall[nCntWall].pos.x, g_aWall[nCntWall].pos.y, g_aWall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_aWall[nCntWall].mtxWorld, &g_aWall[nCntWall].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aWall[nCntWall].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);


			pDevice->SetTexture(0, g_pTextureWall);

			//壁
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4* nCntWall, 2);
		}
	}
}

void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_aWall[nCntWall].bUse == false)
		{
			g_aWall[nCntWall].pos = pos;
			g_aWall[nCntWall].rot = rot;
			g_aWall[nCntWall].bUse = true;
			break;
		}
	}
}
