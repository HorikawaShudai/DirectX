//===========================================================
//
//playerの処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "MeshDome.h"

#define MAX_DOME  (8)			//分割数
#define MAX_HEIGHT  (4)			//分割数
#define DOME_SIZE (1000.0f)		//距離
#define DOME_HEIGHT (300.0f)	//高さ


//typedef struct
//{
//	D3DXVECTOR3 pos;
//	D3DXVECTOR3 rot;
//	D3DXMATRIX  mtxWorld;
//	bool bUse;
//}FIELD;

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshDome = NULL;		//頂点バッファポイント
LPDIRECT3DTEXTURE9 g_pTextureMeshDome = NULL;			//テクスチャポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshDome = NULL;
D3DXVECTOR3 g_MeshDomepos;
D3DXVECTOR3 g_MeshDomerot;
D3DXVECTOR3 g_MeshDomeLength;
D3DXMATRIX g_MeshDomemtxWorld;

//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitMeshDome(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	g_MeshDomepos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshDomerot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ((MAX_DOME + 1) * 2),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshDome,
		NULL);



	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\mesh000.jpg",
		&g_pTextureMeshDome);


	VERTEX_3D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffMeshDome->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定

	for (int nCnt = 0; nCnt <(MAX_DOME + 1) * 2; nCnt++)
	{
		pVtx[nCnt].pos.z = sinf((D3DX_PI*(1.0f - ((1.0f / (MAX_DOME / 2))*(nCnt % (MAX_DOME + 1)))) + g_MeshDomerot.y))* DOME_SIZE;
		pVtx[nCnt].pos.x = cosf((D3DX_PI*(1.0f - ((1.0f / (MAX_DOME / 2))*(nCnt % (MAX_DOME + 1)))) + g_MeshDomerot.y))* DOME_SIZE;
		pVtx[nCnt].pos.y = DOME_HEIGHT - (DOME_HEIGHT*(nCnt / (MAX_DOME + 1)));
		//norの設定
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		//頂点カラー
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[nCnt].tex = D3DXVECTOR2((0.0f + (0.125f*(nCnt % (MAX_DOME + 1)))), (0.0f + (1.0f*(nCnt / (MAX_DOME + 1)))));
	}
	//頂点バッファをアンロックする
	g_pVtxBuffMeshDome->Unlock();

	pDevice->CreateIndexBuffer(sizeof(WORD) * ((MAX_DOME + 1) * 2),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshDome,
		NULL);

	WORD *pIdx;
	g_pIdxBuffMeshDome->Lock(0, 0, (void**)&pIdx, 0);
	for (int nCnt = 0, nIdx = 0; nCnt<(MAX_DOME + 1); nCnt++)
	{
		pIdx[nIdx] = nCnt + (MAX_DOME + 1);
		pIdx[nIdx + 1] = nCnt;
		nIdx += 2;
	}

	g_pIdxBuffMeshDome->Unlock();
	//地面を設置
	//SetMeshDome(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//=========================================================================================================
//地面の終了処理
//=========================================================================================================
void UninitMeshDome(void)
{
	if (g_pTextureMeshDome != NULL)
	{
		g_pTextureMeshDome->Release();
		g_pTextureMeshDome = NULL;
	}
	if (g_pVtxBuffMeshDome != NULL)
	{
		g_pVtxBuffMeshDome->Release();
		g_pVtxBuffMeshDome = NULL;
	}
}

//=========================================================================================================
//地面の更新処理
//=========================================================================================================
void UpdataMeshDome(void)
{

}

//=========================================================================================================
//地面の描画処理
//=========================================================================================================
void DrawMeshDome(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

									//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_MeshDomemtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshDomerot.y, g_MeshDomerot.x, g_MeshDomerot.z);
	D3DXMatrixMultiply(&g_MeshDomemtxWorld, &g_MeshDomemtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_MeshDomepos.x, g_MeshDomepos.y, g_MeshDomepos.z);
	D3DXMatrixMultiply(&g_MeshDomemtxWorld, &g_MeshDomemtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshDomemtxWorld);

	pDevice->SetStreamSource(0, g_pVtxBuffMeshDome, 0, sizeof(VERTEX_3D));

	//頂点バッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshDome);

	pDevice->SetFVF(FVF_VERTEX_3D);


	//pDevice->SetTexture(0, NULL);
	pDevice->SetTexture(0, g_pTextureMeshDome);

	//地面
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (MAX_DOME + 1) * 2, 0, MAX_DOME * 2);
}