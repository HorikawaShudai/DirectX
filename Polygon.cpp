//===========================================================
//
//playerの処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "Polygon.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;		//頂点バッファポイント
LPDIRECT3DTEXTURE9 g_pTexturePolygon = NULL;			//テクスチャポインタ
D3DXVECTOR3 g_posPolygon;
D3DXVECTOR3 g_rotPolygon;
D3DXMATRIX g_mtxWorldPolygon;

//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitPolygon(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	 g_posPolygon = D3DXVECTOR3(0.0f,0.0f,0.0f);
	 g_rotPolygon = D3DXVECTOR3(0.0f,0.0f,0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	VERTEX_3D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tuti001.jpg",
		&g_pTexturePolygon);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3( -200.0f, 0.0f,  + 200.0f);
	pVtx[1].pos = D3DXVECTOR3( +200.0f, 0.0f,  + 200.0f);
	pVtx[2].pos = D3DXVECTOR3( -200.0f, 0.0f,  - 200.0f);
	pVtx[3].pos = D3DXVECTOR3( +200.0f, 0.0f,  - 200.0f);

	//norの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

	//頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//頂点バッファをアンロックする
	g_pVtxBuffPolygon->Unlock();
}

//=========================================================================================================
//ポリゴンの終了処理
//=========================================================================================================
void UninitPolygon(void)
{
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon->Release();
		g_pTexturePolygon = NULL;
	}
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}

//=========================================================================================================
//ポリゴンの更新処理
//=========================================================================================================
void UpdataPolygon(void)
{

}

//=========================================================================================================
//ポリゴンの描画処理
//=========================================================================================================
void DrawPolygon(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldPolygon);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotPolygon.y,  g_rotPolygon.x,  g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolygon);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);


	pDevice->SetTexture(0, g_pTexturePolygon);

	//ポリゴン
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
