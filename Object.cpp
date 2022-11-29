//===========================================================
//
//playerの処理操作
//Author:堀川萩大
//
//===========================================================
#include "input.h"
#include "Object.h"
#include "Camera.h"
#include "Shadow.h"
#include "Bullet.h"
#include "MeshWall.h"

#define OBJECT_NAME "data\\OBJECT\\camera.x"

//グローバル変数宣言
LPD3DXMESH g_pMeshObject = NULL;
LPD3DXBUFFER g_pBuffMatObject = NULL;
DWORD g_dwNumMatObject = 0;
OBJECT g_Object;
LPDIRECT3DTEXTURE9 g_apTEXtureObject[50] = {};

//=========================================================================================================
//初期化処理
//=========================================================================================================
void InitObject(void)
{
	int nNumVtx;
	DWORD dwSizeFVF;
	BYTE *pVtxBuff;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_Object.pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
	g_Object.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Object.Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Object.moveP = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Object.nIdxShadow = 0;

	//Xファイルの読み込み
	D3DXLoadMeshFromX(OBJECT_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatObject,
		NULL,
		&g_dwNumMatObject,
		&g_pMeshObject);

	//頂点数の取得
	nNumVtx = g_pMeshObject->GetNumVertices();

	D3DXMATERIAL *pMat;

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatObject->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObject; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTEXtureObject[nCntMat]);
		}
	}
	g_Object.nIdxShadow = SetShadow();
}

//=========================================================================================================
//ポリゴンの終了処理
//=========================================================================================================
void UninitObject(void)
{
	for (int nCntMat = 0; nCntMat < 50; nCntMat++)
	{
		if (g_apTEXtureObject[nCntMat] != NULL)
		{
			g_apTEXtureObject[nCntMat]->Release();
			g_apTEXtureObject[nCntMat] = NULL;
		}
	}
	if (g_pMeshObject != NULL)
	{
		g_pMeshObject->Release();
		g_pMeshObject = NULL;
	}
	if (g_pBuffMatObject != NULL)
	{
		g_pBuffMatObject->Release();
		g_pBuffMatObject = NULL;
	}
}

//=========================================================================================================
//ポリゴンの更新処理
//=========================================================================================================
void UpdateObject(void)
{
	Camera aCamera = GetCamera();
	g_Object.Oldpos = g_Object.pos;

	if (GetKeyboardPress(DIK_W) == true)
	{//Uのみ押された場合
		if (GetKeyboardPress(DIK_A) == true)
		{//Hのみ押された場合
			g_Object.moveP.x += cosf(D3DX_PI * 0.25f + aCamera.rot.y) * 0.5f;
			g_Object.moveP.z += sinf(D3DX_PI * 0.25f + aCamera.rot.y) * 0.5f;
			g_Object.Destrot.y = -D3DX_PI * 0.25f - aCamera.rot.y;
			if (g_Object.rot.y < -D3DX_PI)
			{
				g_Object.rot.y = D3DX_PI;
			}
			else if (g_Object.rot.y > D3DX_PI)
			{
				g_Object.rot.y = -D3DX_PI;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//Kのみ押された場合
			g_Object.moveP.x += cosf(-D3DX_PI * 0.25f + aCamera.rot.y) * 0.5f;
			g_Object.moveP.z += sinf(-D3DX_PI * 0.25f + aCamera.rot.y) * 0.5f;
			g_Object.Destrot.y = D3DX_PI * 0.25f - aCamera.rot.y;
			if (g_Object.rot.y < -D3DX_PI)
			{
				g_Object.rot.y = D3DX_PI;
			}
			else if (g_Object.rot.y > D3DX_PI)
			{
				g_Object.rot.y = -D3DX_PI;
			}
		}
		else
		{
			g_Object.moveP.x += cosf(D3DX_PI * 0.0f + aCamera.rot.y) * 0.5f;
			g_Object.moveP.z += sinf(D3DX_PI * 0.0f + aCamera.rot.y) * 0.5f;
			g_Object.Destrot.y = +D3DX_PI * 0.0f - aCamera.rot.y;
			if (g_Object.rot.y < -D3DX_PI)
			{
				g_Object.rot.y = D3DX_PI;
			}
			else if (g_Object.rot.y > D3DX_PI)
			{
				g_Object.rot.y = -D3DX_PI;
			}
		}
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{//Jのみ押された場合
		if (GetKeyboardPress(DIK_A) == true)
		{//Hのみ押された場合
			g_Object.moveP.x += cosf(D3DX_PI * 0.75f + aCamera.rot.y) * 0.5f;
			g_Object.moveP.z += sinf(D3DX_PI * 0.75f + aCamera.rot.y) * 0.5f;
			g_Object.Destrot.y = -D3DX_PI * 0.75f - aCamera.rot.y;
			if (g_Object.rot.y < -D3DX_PI)
			{
				g_Object.rot.y = D3DX_PI;
			}
			else if (g_Object.rot.y > D3DX_PI)
			{
				g_Object.rot.y = -D3DX_PI;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//Kのみ押された場合
			g_Object.moveP.x += cosf(-D3DX_PI * 0.75f + aCamera.rot.y) * 0.5f;
			g_Object.moveP.z += sinf(-D3DX_PI * 0.75f + aCamera.rot.y) * 0.5f;
			g_Object.Destrot.y = D3DX_PI * 0.75f - aCamera.rot.y;
			if (g_Object.rot.y < -D3DX_PI)
			{
				g_Object.rot.y = D3DX_PI;
			}
			else if (g_Object.rot.y > D3DX_PI)
			{
				g_Object.rot.y = -D3DX_PI;
			}
		}
		else
		{
			g_Object.moveP.x += cosf(+D3DX_PI * 1.0f + aCamera.rot.y) * 0.5f;
			g_Object.moveP.z += sinf(+D3DX_PI * 1.0f + aCamera.rot.y) * 0.5f;
			g_Object.Destrot.y = -D3DX_PI * 1.0f - aCamera.rot.y;
			if (g_Object.rot.y < -D3DX_PI)
			{
				g_Object.rot.y = D3DX_PI;
			}
			else if (g_Object.rot.y > D3DX_PI)
			{
				g_Object.rot.y = -D3DX_PI;
			}
		}
	}
	else if (GetKeyboardPress(DIK_A) == true)
	{//Hのみ押された場
		g_Object.moveP.x += cosf(D3DX_PI *0.5f + aCamera.rot.y) * 0.5f;
		g_Object.moveP.z += sinf(D3DX_PI *0.5f + aCamera.rot.y) * 0.5f;
		g_Object.Destrot.y = -D3DX_PI * 0.5f - aCamera.rot.y;
		if (g_Object.rot.y < -D3DX_PI)
		{
			g_Object.rot.y = D3DX_PI;
		}
		else if (g_Object.rot.y > D3DX_PI)
		{
			g_Object.rot.y = -D3DX_PI;
		}
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//Kのみ押された場合
		g_Object.moveP.x += cosf(-D3DX_PI *0.5f + aCamera.rot.y) * 0.5f;
		g_Object.moveP.z += sinf(-D3DX_PI *0.5f + aCamera.rot.y) * 0.5f;
		g_Object.Destrot.y = D3DX_PI * 0.5f - aCamera.rot.y;
		if (g_Object.rot.y < -D3DX_PI)
		{
			g_Object.rot.y = D3DX_PI;
		}
		else if (g_Object.rot.y > D3DX_PI)
		{
			g_Object.rot.y = -D3DX_PI;
		}
	}

	//if (GetKeyboardPress(DIK_E) == true)
	//{
	//	g_Object.Destrot.y += 0.05f;
	//}
	//else if (GetKeyboardPress(DIK_Q) == true)
	//{
	//	g_Object.Destrot.y -= 0.05f;
	//}
	if (GetKeyboardPress(DIK_SPACE) == true)
	{
		SetBullet(g_Object.pos, D3DXVECTOR3(0.0f, 0.0f, 0.5f), g_Object.rot, BULLETTYPE_PLAYER, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	//モデルの向き
	{
		g_Object.Diffrot.y = g_Object.Destrot.y - g_Object.rot.y;

		if (g_Object.Diffrot.y > D3DX_PI)
		{
			g_Object.Diffrot.y -= D3DX_PI * 2;
		}
		else if (g_Object.Diffrot.y < -D3DX_PI)
		{
			g_Object.Diffrot.y += D3DX_PI * 2;

		}

		g_Object.rot.y += (g_Object.Diffrot.y)*0.1f;

		if (g_Object.rot.y > D3DX_PI)
		{
			g_Object.rot.y -= D3DX_PI * 2;
		}
		else if (g_Object.rot.y < -D3DX_PI)
		{
			g_Object.rot.y += D3DX_PI * 2;
		}
	}
	g_Object.moveP *= 0.9f;
	g_Object.pos += g_Object.moveP;
	if (ColissionWall(g_Object.pos) == true)
	{
		g_Object.pos = g_Object.Oldpos;
	}

	SetPositionShadow(g_Object.nIdxShadow, D3DXVECTOR3(g_Object.pos.x, 0.0f, g_Object.pos.z));
}

//=========================================================================================================
//ポリゴンの描画処理
//=========================================================================================================
void DrawObject(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Object.mtxWorldObject);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Object.rot.y, g_Object.rot.x, g_Object.rot.z);
	D3DXMatrixMultiply(&g_Object.mtxWorldObject, &g_Object.mtxWorldObject, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Object.pos.x, g_Object.pos.y, g_Object.pos.z);
	D3DXMatrixMultiply(&g_Object.mtxWorldObject, &g_Object.mtxWorldObject, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Object.mtxWorldObject);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);
	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatObject->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObject; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTEXtureObject[nCntMat]);

		//モデル（パーツ）の描画
		g_pMeshObject->DrawSubset(nCntMat);
	}
	pDevice->SetMaterial(&matDef);

}

OBJECT GetObject(void)
{
	return g_Object;
}
