//===========================================================
//
//playerの処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "MeshWall.h"

#define MAX_WALL  (50)
#define FIELD_HEIGHT (2)
#define FIELD_HEIGHT_SIZE (2000.0f)
#define FIELD_WIDTH  (2)
#define FIELD_WIDTH_SIZE  (1000.0f)
#define DIVISION	 ((FIELD_WIDTH+1)*(FIELD_HEIGHT+1))
#define FIELF_SIZE (500.0f)


typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX  mtxWorld;
	float Length;
	bool bUse;
}WALL;

//グローバル変数宣言
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;		//頂点バッファポイント
LPDIRECT3DTEXTURE9 g_pTextureMeshWall = NULL;			//テクスチャポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;
WALL g_WallMesh[MAX_WALL];
D3DXMATRIX g_MeshWallmtxWorld;

//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitMeshWall(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		g_WallMesh[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_WallMesh[nCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_WallMesh[nCnt].bUse = false;
	}


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * DIVISION*MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);



	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall001.jpg",
		&g_pTextureMeshWall);


	VERTEX_3D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標の設定
	for (int nWall = 0; nWall < MAX_WALL; nWall++)
	{
		for (int nCnt = 0; nCnt < DIVISION; nCnt++)
		{
			pVtx[nCnt].pos = D3DXVECTOR3((-FIELD_HEIGHT_SIZE + (FIELD_HEIGHT_SIZE*(nCnt % 3))), (FIELD_WIDTH_SIZE - (FIELD_WIDTH_SIZE*(nCnt / 3))), 0.0f);
			//norの設定
			pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			//頂点カラー
			pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			//テクスチャ座標の設定
			pVtx[nCnt].tex = D3DXVECTOR2(0.0f + (0.5f*(nCnt % (FIELD_WIDTH + 1))), 0.0f+(0.5f*(nCnt / (FIELD_HEIGHT + 1))));

		}
		pVtx += DIVISION;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffMeshWall->Unlock();

	pDevice->CreateIndexBuffer(sizeof(WORD) * 14* MAX_WALL,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall,
		NULL);

	WORD *pIdx;
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);
	for (int nWall = 0; nWall < MAX_WALL; nWall++)
	{
		pIdx[0] = 3;
		pIdx[1] = 0;
		pIdx[2] = 4;
		pIdx[3] = 1;
		pIdx[4] = 5;
		pIdx[5] = 2;
		pIdx[6] = 2;
		pIdx[7] = 6;
		pIdx[8] = 6;
		pIdx[9] = 3;
		pIdx[10] = 7;
		pIdx[11] = 4;
		pIdx[12] = 8;
		pIdx[13] = 5;

		pIdx += 14;
	}

	g_pIdxBuffMeshWall->Unlock();
	//壁を設置
	SetMeshWall(D3DXVECTOR3(0.0f, 0.0f, 2000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMeshWall(D3DXVECTOR3(-2000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f));
	SetMeshWall(D3DXVECTOR3(2000.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	SetMeshWall(D3DXVECTOR3(0.0f, 0.0f, -2000.0f), D3DXVECTOR3(0.0f, 3.14f, 0.0f));
}

//=========================================================================================================
//地面の終了処理
//=========================================================================================================
void UninitMeshWall(void)
{
	if (g_pTextureMeshWall != NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}
}

//=========================================================================================================
//地面の更新処理
//=========================================================================================================
void UpdataMeshWall(void)
{

}

//=========================================================================================================
//地面の描画処理
//=========================================================================================================
void DrawMeshWall(void)
{
	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		if (g_WallMesh[nCnt].bUse == true)
		{
			//デバイスの取得
			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

											//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_MeshWallmtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_WallMesh[nCnt].rot.y, g_WallMesh[nCnt].rot.x, g_WallMesh[nCnt].rot.z);
			D3DXMatrixMultiply(&g_MeshWallmtxWorld, &g_MeshWallmtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_WallMesh[nCnt].pos.x, g_WallMesh[nCnt].pos.y, g_WallMesh[nCnt].pos.z);
			D3DXMatrixMultiply(&g_MeshWallmtxWorld, &g_MeshWallmtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_MeshWallmtxWorld);

			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

			//頂点バッファをデータストリームに設定
			pDevice->SetIndices(g_pIdxBuffMeshWall);

			pDevice->SetFVF(FVF_VERTEX_3D);


			pDevice->SetTexture(0, g_pTextureMeshWall);

			//地面
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 9, 0, 12);
		}
	}
}

void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_WallMesh[nCntWall].bUse == false)
		{
			g_WallMesh[nCntWall].pos = pos;
			g_WallMesh[nCntWall].rot = rot;
			g_WallMesh[nCntWall].bUse = true;
			break;
		}
	}
}
//====================================================
//壁の当たり判定
//====================================================
bool ColissionWall(D3DXVECTOR3 pos)
{
	bool bHit = false;
	D3DXVECTOR3 Wallpos[2];
	D3DXVECTOR3 vecLine;
	D3DXVECTOR3 vecTopos;


	VERTEX_3D *pVtx;
	//頂点バッファをロックし頂点情報へのポインタを取得
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_WallMesh[nCntWall].bUse == true)
		{
			{
				//Wallpos[0] = D3DXVECTOR3(-500.0f, 0.0f, 0.0f) + g_WallMesh[nCntWall].pos;
				//Wallpos[1] = D3DXVECTOR3(500.0f, 0.0f, 0.0f) + g_WallMesh[nCntWall].pos;
				//vecLine = (Wallpos[1] - Wallpos[0]);
				//vecTopos = (pos - Wallpos[0]);

				//if (((vecLine.z*vecTopos.x) - (vecLine.x*vecTopos.z)) < 0.0f)
				//{
				//	//bHit = true;
				//}
			}

			{

				if (g_WallMesh[nCntWall].pos.z == 0.0f&&g_WallMesh[nCntWall].pos.x > 0.0f)
				{
					if (g_WallMesh[nCntWall].pos.x < pos.x)
					{
						bHit = true;
					}
				}
				else if (g_WallMesh[nCntWall].pos.z == 0.0f&&g_WallMesh[nCntWall].pos.x < 0.0f)
				{
					if (g_WallMesh[nCntWall].pos.x > pos.x)
					{
						bHit = true;
					}
				}
				else if (g_WallMesh[nCntWall].pos.z > 0.0f&&g_WallMesh[nCntWall].pos.x == 0.0f)
				{
					if (g_WallMesh[nCntWall].pos.z < pos.z)
					{
						bHit = true;
					}
				}
				else if (g_WallMesh[nCntWall].pos.z < 0.0f&&g_WallMesh[nCntWall].pos.x == 0.0f)
				{
					if (g_WallMesh[nCntWall].pos.z > pos.z)
					{
						bHit = true;
					}
				}
			}
		}
		pVtx += DIVISION;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffMeshWall->Unlock();
	return bHit;
}