//===========================================================
//
//player�̏�������
//Author:�x�씋��
//
//===========================================================
#include "input.h"
#include "Polygon.h"

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;		//���_�o�b�t�@�|�C���g
LPDIRECT3DTEXTURE9 g_pTexturePolygon = NULL;			//�e�N�X�`���|�C���^
D3DXVECTOR3 g_posPolygon;
D3DXVECTOR3 g_rotPolygon;
D3DXMATRIX g_mtxWorldPolygon;

//=========================================================================================================
//����������
//=========================================================================================================
void InitPolygon(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	 g_posPolygon = D3DXVECTOR3(0.0f,0.0f,0.0f);
	 g_rotPolygon = D3DXVECTOR3(0.0f,0.0f,0.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tuti001.jpg",
		&g_pTexturePolygon);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3( -200.0f, 0.0f,  + 200.0f);
	pVtx[1].pos = D3DXVECTOR3( +200.0f, 0.0f,  + 200.0f);
	pVtx[2].pos = D3DXVECTOR3( -200.0f, 0.0f,  - 200.0f);
	pVtx[3].pos = D3DXVECTOR3( +200.0f, 0.0f,  - 200.0f);

	//nor�̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPolygon->Unlock();
}

//=========================================================================================================
//�|���S���̏I������
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
//�|���S���̍X�V����
//=========================================================================================================
void UpdataPolygon(void)
{

}

//=========================================================================================================
//�|���S���̕`�揈��
//=========================================================================================================
void DrawPolygon(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldPolygon);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotPolygon.y,  g_rotPolygon.x,  g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolygon);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);


	pDevice->SetTexture(0, g_pTexturePolygon);

	//�|���S��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
