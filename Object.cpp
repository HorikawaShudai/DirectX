//===========================================================
//
//player�̏�������
//Author:�x�씋��
//
//===========================================================
#include "input.h"
#include "Object.h"
#include "Camera.h"
#include "Shadow.h"
#include "Bullet.h"
#include "MeshWall.h"

#define OBJECT_NAME "data\\OBJECT\\camera.x"

//�O���[�o���ϐ��錾
LPD3DXMESH g_pMeshObject = NULL;
LPD3DXBUFFER g_pBuffMatObject = NULL;
DWORD g_dwNumMatObject = 0;
OBJECT g_Object;
LPDIRECT3DTEXTURE9 g_apTEXtureObject[50] = {};

//=========================================================================================================
//����������
//=========================================================================================================
void InitObject(void)
{
	int nNumVtx;
	DWORD dwSizeFVF;
	BYTE *pVtxBuff;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	g_Object.pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
	g_Object.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Object.Diffrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Object.moveP = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Object.nIdxShadow = 0;

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(OBJECT_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatObject,
		NULL,
		&g_dwNumMatObject,
		&g_pMeshObject);

	//���_���̎擾
	nNumVtx = g_pMeshObject->GetNumVertices();

	D3DXMATERIAL *pMat;

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatObject->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObject; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTEXtureObject[nCntMat]);
		}
	}
	g_Object.nIdxShadow = SetShadow();
}

//=========================================================================================================
//�|���S���̏I������
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
//�|���S���̍X�V����
//=========================================================================================================
void UpdateObject(void)
{
	Camera aCamera = GetCamera();
	g_Object.Oldpos = g_Object.pos;

	if (GetKeyboardPress(DIK_W) == true)
	{//U�̂݉����ꂽ�ꍇ
		if (GetKeyboardPress(DIK_A) == true)
		{//H�̂݉����ꂽ�ꍇ
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
		{//K�̂݉����ꂽ�ꍇ
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
	{//J�̂݉����ꂽ�ꍇ
		if (GetKeyboardPress(DIK_A) == true)
		{//H�̂݉����ꂽ�ꍇ
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
		{//K�̂݉����ꂽ�ꍇ
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
	{//H�̂݉����ꂽ��
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
	{//K�̂݉����ꂽ�ꍇ
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

	//���f���̌���
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
//�|���S���̕`�揈��
//=========================================================================================================
void DrawObject(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Object.mtxWorldObject);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Object.rot.y, g_Object.rot.x, g_Object.rot.z);
	D3DXMatrixMultiply(&g_Object.mtxWorldObject, &g_Object.mtxWorldObject, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Object.pos.x, g_Object.pos.y, g_Object.pos.z);
	D3DXMatrixMultiply(&g_Object.mtxWorldObject, &g_Object.mtxWorldObject, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Object.mtxWorldObject);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);
	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatObject->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatObject; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTEXtureObject[nCntMat]);

		//���f���i�p�[�c�j�̕`��
		g_pMeshObject->DrawSubset(nCntMat);
	}
	pDevice->SetMaterial(&matDef);

}

OBJECT GetObject(void)
{
	return g_Object;
}
