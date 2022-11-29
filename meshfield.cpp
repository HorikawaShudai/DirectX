//===========================================================
//
//playerの処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "MeshField.h"

#define MAX_FIELD  (50)
#define FIELF_SIZE (1000.0f)


//typedef struct
//{
//	D3DXVECTOR3 pos;
//	D3DXVECTOR3 rot;
//	D3DXMATRIX  mtxWorld;
//	bool bUse;
//}FIELD;

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL;		//頂点バッファポイント
LPDIRECT3DTEXTURE9 g_pTextureMeshField = NULL;			//テクスチャポインタ
D3DXVECTOR3 g_MeshFieldpos;
D3DXVECTOR3 g_MeshFieldrot;
D3DXMATRIX g_MeshFieldmtxWorld;

//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitMeshField(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	g_MeshFieldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshFieldrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 14 * MAX_FIELD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL);


	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tuti001.jpg",
		&g_pTextureMeshField);


	VERTEX_3D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	pVtx[0].pos =  D3DXVECTOR3(-FIELF_SIZE, 0.0f, 0.0f);
	pVtx[1].pos =  D3DXVECTOR3(-FIELF_SIZE, 0.0f, +FIELF_SIZE);
	pVtx[2].pos =  D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos =  D3DXVECTOR3(0.0f, 0.0f, FIELF_SIZE);
	pVtx[4].pos =  D3DXVECTOR3(FIELF_SIZE, 0.0f, 0.0f);
	pVtx[5].pos =  D3DXVECTOR3(FIELF_SIZE, 0.0f, FIELF_SIZE);
	pVtx[6].pos =  D3DXVECTOR3(FIELF_SIZE, 0.0f, FIELF_SIZE);
	pVtx[7].pos =  D3DXVECTOR3(-FIELF_SIZE, 0.0f, -FIELF_SIZE);
	pVtx[8].pos =  D3DXVECTOR3(-FIELF_SIZE, 0.0f, -FIELF_SIZE);
	pVtx[9].pos =  D3DXVECTOR3(-FIELF_SIZE, 0.0f, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(0.0f, 0.0f, -FIELF_SIZE);
	pVtx[11].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[12].pos = D3DXVECTOR3(+FIELF_SIZE, 0.0f, -FIELF_SIZE);
	pVtx[13].pos = D3DXVECTOR3(+FIELF_SIZE, 0.0f, 0.0f);

	//norの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[9].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[10].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[11].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[12].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[13].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
	//頂点バッファをアンロックする
	g_pVtxBuffMeshField->Unlock();
	//地面を設置
	//SetMeshField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//=========================================================================================================
//地面の終了処理
//=========================================================================================================
void UninitMeshField(void)
{
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}
}

//=========================================================================================================
//地面の更新処理
//=========================================================================================================
void UpdataMeshField(void)
{

}

//=========================================================================================================
//地面の描画処理
//=========================================================================================================
void DrawMeshField(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

									//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_MeshFieldmtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshFieldrot.y, g_MeshFieldrot.x, g_MeshFieldrot.z);
	D3DXMatrixMultiply(&g_MeshFieldmtxWorld, &g_MeshFieldmtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_MeshFieldpos.x, g_MeshFieldpos.y, g_MeshFieldpos.z);
	D3DXMatrixMultiply(&g_MeshFieldmtxWorld, &g_MeshFieldmtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshFieldmtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);


	pDevice->SetTexture(0, g_pTextureMeshField);

	//地面
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 12);


}