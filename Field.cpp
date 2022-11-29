//===========================================================
//
//playerの処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "Field.h"

#define MAX_FIELD  (50)
#define FIELF_SIZE (500.0f)


typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX  mtxWorld;
	bool bUse;
}FIELD;

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;		//頂点バッファポイント
LPDIRECT3DTEXTURE9 g_pTextureField = NULL;			//テクスチャポインタ
FIELD g_aField[MAX_FIELD];

//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitField(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		g_aField[nCntField].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aField[nCntField].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aField[nCntField].bUse = false;
	}
	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_FIELD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffField,
		NULL);


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tuti001.jpg",
		&g_pTextureField);


	VERTEX_3D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-FIELF_SIZE, 0.0f, +FIELF_SIZE);
		pVtx[1].pos = D3DXVECTOR3(+FIELF_SIZE, 0.0f, +FIELF_SIZE);
		pVtx[2].pos = D3DXVECTOR3(-FIELF_SIZE, 0.0f, -FIELF_SIZE);
		pVtx[3].pos = D3DXVECTOR3(+FIELF_SIZE, 0.0f, -FIELF_SIZE);

		//norの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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
	g_pVtxBuffField->Unlock();
	//地面を設置
	//SetField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//=========================================================================================================
//地面の終了処理
//=========================================================================================================
void UninitField(void)
{
	if (g_pTextureField != NULL)
	{
		g_pTextureField->Release();
		g_pTextureField = NULL;
	}
	if (g_pVtxBuffField != NULL)
	{
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}
}

//=========================================================================================================
//地面の更新処理
//=========================================================================================================
void UpdataField(void)
{

}

//=========================================================================================================
//地面の描画処理
//=========================================================================================================
void DrawField(void)
{
	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if (g_aField[nCntField].bUse == true)
		{
			//デバイスの取得
			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

											//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_aField[nCntField].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aField[nCntField].rot.y, g_aField[nCntField].rot.x, g_aField[nCntField].rot.z);
			D3DXMatrixMultiply(&g_aField[nCntField].mtxWorld, &g_aField[nCntField].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_aField[nCntField].pos.x, g_aField[nCntField].pos.y, g_aField[nCntField].pos.z);
			D3DXMatrixMultiply(&g_aField[nCntField].mtxWorld, &g_aField[nCntField].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aField[nCntField].mtxWorld);

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);


			pDevice->SetTexture(0, g_pTextureField);

			//地面
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
}

void SetField(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if (g_aField[nCntField].bUse == false)
		{
			g_aField[nCntField].pos = pos;
			g_aField[nCntField].rot = rot;
			g_aField[nCntField].bUse = true;
			break;
		}
	}
}