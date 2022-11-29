//===========================================================
//
//playerの処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "Billboard.h"

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;		//頂点バッファポイント
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;			//テクスチャポインタ
D3DXVECTOR3 g_posBillboard;
D3DXMATRIX g_mtxWorldBillboard;

//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitBillboard(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_posBillboard = D3DXVECTOR3(-200.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	VERTEX_3D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tree000.png",
		&g_pTextureBillboard);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-20.0f, 100.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+20.0f, 100.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-20.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+20.0f, 0.0f, 0.0f);

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


	//頂点バッファをアンロックする
	g_pVtxBuffBillboard->Unlock();
}

//=========================================================================================================
//ビルボードの終了処理
//=========================================================================================================
void UninitBillboard(void)
{
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//=========================================================================================================
//ビルボードの更新処理
//=========================================================================================================
void UpdataBillboard(void)
{
}

//=========================================================================================================
//ビルボードの描画処理
//=========================================================================================================
void DrawBillboard(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxTrans;	//計算用マトリックス
	D3DXMATRIX mtxView;		//ビューマトリックスの取得用

	//Zテストを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
	
	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldBillboard);

	//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&g_mtxWorldBillboard, NULL, &mtxView);
	g_mtxWorldBillboard._41 = 0.0f;
	g_mtxWorldBillboard._42 = 0.0f;
	g_mtxWorldBillboard._43 = 0.0f;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posBillboard.x, g_posBillboard.y, g_posBillboard.z);
	D3DXMatrixMultiply(&g_mtxWorldBillboard, &g_mtxWorldBillboard, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBillboard);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);


	pDevice->SetTexture(0, g_pTextureBillboard);

	//ビルボード
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//Zテストを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
