//===========================================================
//
//playerの処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "Player.h"
#include "Camera.h"
#include "Shadow.h"
#include "Bullet.h"
#include "MeshWall.h"

#define MODEL_NAME "data\\MODEL\\camera.x"

//グローバル変数宣言
LPD3DXMESH g_pMeshPlayer = NULL;
LPD3DXBUFFER g_pBuffMatPlayer = NULL;
DWORD g_dwNumMatPlayer = 0;
PLAYER g_Player;
LPDIRECT3DTEXTURE9 g_apTEXturePlayer[50] = {};

//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitPlayer(void)
{
	int nNumVtx;
	DWORD dwSizeFVF;
	BYTE *pVtxBuff;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_Player.pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.moveP = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.nIdxShadow = 0;

	//Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer);

	//頂点数の取得
	nNumVtx = g_pMeshPlayer->GetNumVertices();

	D3DXMATERIAL *pMat;

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTEXturePlayer[nCntMat]);
		}
	}
	g_Player.nIdxShadow = SetShadow();
}

//=========================================================================================================
//ポリゴンの終了処理
//=========================================================================================================
void UninitPlayer(void)
{
	for (int nCntMat = 0; nCntMat < 50; nCntMat++)
	{
		if (g_apTEXturePlayer[nCntMat] != NULL)
		{
			g_apTEXturePlayer[nCntMat]->Release();
			g_apTEXturePlayer[nCntMat] = NULL;
		}
	}
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}
}

//=========================================================================================================
//ポリゴンの更新処理
//=========================================================================================================
void UpdatePlayer(void)
{
	Camera aCamera = GetCamera();
	g_Player.Oldpos = g_Player.pos;

	if (GetKeyboardPress(DIK_W) == true)
	{//Uのみ押された場合
		if (GetKeyboardPress(DIK_A) == true)
		{//Hのみ押された場合
			g_Player.moveP.x += cosf(D3DX_PI * 0.25f + aCamera.rot.y) * 0.5f;
			g_Player.moveP.z += sinf(D3DX_PI * 0.25f + aCamera.rot.y) * 0.5f;
			g_Player.Destrot.y = -D3DX_PI * 0.25f - aCamera.rot.y;
			if (g_Player.rot.y < -D3DX_PI)
			{
				g_Player.rot.y = D3DX_PI;
			}
			else if (g_Player.rot.y > D3DX_PI)
			{
				g_Player.rot.y = -D3DX_PI;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//Kのみ押された場合
			g_Player.moveP.x += cosf(-D3DX_PI * 0.25f + aCamera.rot.y) * 0.5f;
			g_Player.moveP.z += sinf(-D3DX_PI * 0.25f + aCamera.rot.y) * 0.5f;
			g_Player.Destrot.y = D3DX_PI * 0.25f - aCamera.rot.y;
			if (g_Player.rot.y < -D3DX_PI)
			{
				g_Player.rot.y = D3DX_PI;
			}
			else if (g_Player.rot.y > D3DX_PI)
			{
				g_Player.rot.y = -D3DX_PI;
			}
		}
		else
		{
			g_Player.moveP.x += cosf(D3DX_PI * 0.0f + aCamera.rot.y) * 0.5f;
			g_Player.moveP.z += sinf(D3DX_PI * 0.0f + aCamera.rot.y) * 0.5f;
			g_Player.Destrot.y = +D3DX_PI * 0.0f - aCamera.rot.y;
			if (g_Player.rot.y < -D3DX_PI)
			{
				g_Player.rot.y = D3DX_PI;
			}
			else if (g_Player.rot.y > D3DX_PI)
			{
				g_Player.rot.y = -D3DX_PI;
			}
		}
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{//Jのみ押された場合
		if (GetKeyboardPress(DIK_A) == true)
		{//Hのみ押された場合
			g_Player.moveP.x += cosf(D3DX_PI * 0.75f + aCamera.rot.y) * 0.5f;
			g_Player.moveP.z += sinf(D3DX_PI * 0.75f + aCamera.rot.y) * 0.5f;
			g_Player.Destrot.y = -D3DX_PI * 0.75f - aCamera.rot.y;
			if (g_Player.rot.y < -D3DX_PI)
			{
				g_Player.rot.y = D3DX_PI;
			}
			else if (g_Player.rot.y > D3DX_PI)
			{
				g_Player.rot.y = -D3DX_PI;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//Kのみ押された場合
			g_Player.moveP.x += cosf(-D3DX_PI * 0.75f + aCamera.rot.y) * 0.5f;
			g_Player.moveP.z += sinf(-D3DX_PI * 0.75f + aCamera.rot.y) * 0.5f;
			g_Player.Destrot.y = D3DX_PI * 0.75f - aCamera.rot.y;
			if (g_Player.rot.y < -D3DX_PI)
			{
				g_Player.rot.y = D3DX_PI;
			}
			else if (g_Player.rot.y > D3DX_PI)
			{
				g_Player.rot.y = -D3DX_PI;
			}
		}
		else
		{
			g_Player.moveP.x += cosf(+D3DX_PI * 1.0f + aCamera.rot.y) * 0.5f;
			g_Player.moveP.z += sinf(+D3DX_PI * 1.0f + aCamera.rot.y) * 0.5f;
			g_Player.Destrot.y = -D3DX_PI * 1.0f - aCamera.rot.y;
			if (g_Player.rot.y < -D3DX_PI)
			{
				g_Player.rot.y = D3DX_PI;
			}
			else if (g_Player.rot.y > D3DX_PI)
			{
				g_Player.rot.y = -D3DX_PI;
			}
		}
	}
	else if (GetKeyboardPress(DIK_A) == true)
	{//Hのみ押された場
		g_Player.moveP.x += cosf(D3DX_PI *0.5f + aCamera.rot.y) * 0.5f;
		g_Player.moveP.z += sinf(D3DX_PI *0.5f + aCamera.rot.y) * 0.5f;
		g_Player.Destrot.y = -D3DX_PI * 0.5f - aCamera.rot.y;
		if (g_Player.rot.y < -D3DX_PI)
		{
			g_Player.rot.y = D3DX_PI;
		}
		else if (g_Player.rot.y > D3DX_PI)
		{
			g_Player.rot.y = -D3DX_PI;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//Kのみ押された場合
		g_Player.moveP.x += cosf(-D3DX_PI *0.5f + aCamera.rot.y) * 0.5f;
		g_Player.moveP.z += sinf(-D3DX_PI *0.5f + aCamera.rot.y) * 0.5f;
		g_Player.Destrot.y = D3DX_PI * 0.5f - aCamera.rot.y;
		if (g_Player.rot.y < -D3DX_PI)
		{
			g_Player.rot.y = D3DX_PI;
		}
		else if (g_Player.rot.y > D3DX_PI)
		{
			g_Player.rot.y = -D3DX_PI;
		}
	}

	//if (GetKeyboardPress(DIK_E) == true)
	//{
	//	g_Player.Destrot.y += 0.05f;
	//}
	//else if (GetKeyboardPress(DIK_Q) == true)
	//{
	//	g_Player.Destrot.y -= 0.05f;
	//}
	if (GetKeyboardPress(DIK_SPACE) == true)
	{
		SetBullet(g_Player.pos, D3DXVECTOR3(0.0f, 0.0f, 0.5f), g_Player.rot, BULLETTYPE_PLAYER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	//モデルの向き
	{
		g_Player.Diffrot.y = g_Player.Destrot.y - g_Player.rot.y;

		if (g_Player.Diffrot.y > D3DX_PI)
		{
			g_Player.Diffrot.y -= D3DX_PI * 2;
		}
		else if (g_Player.Diffrot.y < -D3DX_PI)
		{
			g_Player.Diffrot.y += D3DX_PI * 2;

		}

		g_Player.rot.y += (g_Player.Diffrot.y)*0.1f;

		if (g_Player.rot.y > D3DX_PI)
		{
			g_Player.rot.y -= D3DX_PI * 2;
		}
		else if (g_Player.rot.y < -D3DX_PI)
		{
			g_Player.rot.y += D3DX_PI * 2;
		}
	}
	g_Player.moveP *= 0.9f;
	g_Player.pos += g_Player.moveP;
	if (ColissionWall(g_Player.pos) == true)
	{
		g_Player.pos = g_Player.Oldpos;
	}

	SetPositionShadow(g_Player.nIdxShadow, D3DXVECTOR3(g_Player.pos.x, 0.0f, g_Player.pos.z));
}

//=========================================================================================================
//ポリゴンの描画処理
//=========================================================================================================
void DrawPlayer(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player.mtxWorldPlayer);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorldPlayer, &g_Player.mtxWorldPlayer, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorldPlayer, &g_Player.mtxWorldPlayer, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorldPlayer);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);
	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTEXturePlayer[nCntMat]);

		//モデル（パーツ）の描画
		g_pMeshPlayer->DrawSubset(nCntMat);
	}
	pDevice->SetMaterial(&matDef);

}

PLAYER GetPlayer(void)
{
	return g_Player;
}
