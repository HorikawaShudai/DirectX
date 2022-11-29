//===========================================================
//
//player�̏�������
//Author:�x�씋��
//
//===========================================================
#include "input.h"
#include "MeshDome.h"

#define MAX_DOME  (8)			//������
#define MAX_HEIGHT  (4)			//������
#define DOME_SIZE (1000.0f)		//����
#define DOME_HEIGHT (300.0f)	//����


//typedef struct
//{
//	D3DXVECTOR3 pos;
//	D3DXVECTOR3 rot;
//	D3DXMATRIX  mtxWorld;
//	bool bUse;
//}FIELD;

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshDome = NULL;		//���_�o�b�t�@�|�C���g
LPDIRECT3DTEXTURE9 g_pTextureMeshDome = NULL;			//�e�N�X�`���|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshDome = NULL;
D3DXVECTOR3 g_MeshDomepos;
D3DXVECTOR3 g_MeshDomerot;
D3DXVECTOR3 g_MeshDomeLength;
D3DXMATRIX g_MeshDomemtxWorld;

//=========================================================================================================
//����������
//=========================================================================================================
void InitMeshDome(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	g_MeshDomepos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshDomerot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * ((MAX_DOME + 1) * 2),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshDome,
		NULL);



	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\mesh000.jpg",
		&g_pTextureMeshDome);


	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffMeshDome->Lock(0, 0, (void**)&pVtx, 0);
	//���_���W�̐ݒ�

	for (int nCnt = 0; nCnt <(MAX_DOME + 1) * 2; nCnt++)
	{
		pVtx[nCnt].pos.z = sinf((D3DX_PI*(1.0f - ((1.0f / (MAX_DOME / 2))*(nCnt % (MAX_DOME + 1)))) + g_MeshDomerot.y))* DOME_SIZE;
		pVtx[nCnt].pos.x = cosf((D3DX_PI*(1.0f - ((1.0f / (MAX_DOME / 2))*(nCnt % (MAX_DOME + 1)))) + g_MeshDomerot.y))* DOME_SIZE;
		pVtx[nCnt].pos.y = DOME_HEIGHT - (DOME_HEIGHT*(nCnt / (MAX_DOME + 1)));
		//nor�̐ݒ�
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		//���_�J���[
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[nCnt].tex = D3DXVECTOR2((0.0f + (0.125f*(nCnt % (MAX_DOME + 1)))), (0.0f + (1.0f*(nCnt / (MAX_DOME + 1)))));
	}
	//���_�o�b�t�@���A�����b�N����
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
	//�n�ʂ�ݒu
	//SetMeshDome(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//=========================================================================================================
//�n�ʂ̏I������
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
//�n�ʂ̍X�V����
//=========================================================================================================
void UpdataMeshDome(void)
{

}

//=========================================================================================================
//�n�ʂ̕`�揈��
//=========================================================================================================
void DrawMeshDome(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

									//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_MeshDomemtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshDomerot.y, g_MeshDomerot.x, g_MeshDomerot.z);
	D3DXMatrixMultiply(&g_MeshDomemtxWorld, &g_MeshDomemtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_MeshDomepos.x, g_MeshDomepos.y, g_MeshDomepos.z);
	D3DXMatrixMultiply(&g_MeshDomemtxWorld, &g_MeshDomemtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshDomemtxWorld);

	pDevice->SetStreamSource(0, g_pVtxBuffMeshDome, 0, sizeof(VERTEX_3D));

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshDome);

	pDevice->SetFVF(FVF_VERTEX_3D);


	//pDevice->SetTexture(0, NULL);
	pDevice->SetTexture(0, g_pTextureMeshDome);

	//�n��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (MAX_DOME + 1) * 2, 0, MAX_DOME * 2);
}