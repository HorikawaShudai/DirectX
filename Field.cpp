//===========================================================
//
//player�̏�������
//Author:�x�씋��
//
//===========================================================
#include "input.h"
#include "Field.h"

#define MAX_FIELD  (50)
#define FIELF_SIZE (500.0f)


typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX  mtxWorld;
	bool bUse;
}FIELD;

//�O���[�o���ϐ��錾
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;		//���_�o�b�t�@�|�C���g
LPDIRECT3DTEXTURE9 g_pTextureField = NULL;			//�e�N�X�`���|�C���^
FIELD g_aField[MAX_FIELD];

//=========================================================================================================
//����������
//=========================================================================================================
void InitField(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		g_aField[nCntField].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aField[nCntField].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aField[nCntField].bUse = false;
	}
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_FIELD,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffField,
		NULL);


	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\tuti001.jpg",
		&g_pTextureField);


	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-FIELF_SIZE, 0.0f, +FIELF_SIZE);
		pVtx[1].pos = D3DXVECTOR3(+FIELF_SIZE, 0.0f, +FIELF_SIZE);
		pVtx[2].pos = D3DXVECTOR3(-FIELF_SIZE, 0.0f, -FIELF_SIZE);
		pVtx[3].pos = D3DXVECTOR3(+FIELF_SIZE, 0.0f, -FIELF_SIZE);

		//nor�̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffField->Unlock();
	//�n�ʂ�ݒu
	//SetField(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

//=========================================================================================================
//�n�ʂ̏I������
//=========================================================================================================
void UninitField(void)
{
	if (g_pTextureField != NULL)
	{
		g_pTextureField->Release();
		g_pTextureField = NULL;
	}
	if (g_pVtxBuffField != NULL)
	{
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}
}

//=========================================================================================================
//�n�ʂ̍X�V����
//=========================================================================================================
void UpdataField(void)
{

}

//=========================================================================================================
//�n�ʂ̕`�揈��
//=========================================================================================================
void DrawField(void)
{
	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if (g_aField[nCntField].bUse == true)
		{
			//�f�o�C�X�̎擾
			LPDIRECT3DDEVICE9 pDevice = GetDevice();

			D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

											//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aField[nCntField].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aField[nCntField].rot.y, g_aField[nCntField].rot.x, g_aField[nCntField].rot.z);
			D3DXMatrixMultiply(&g_aField[nCntField].mtxWorld, &g_aField[nCntField].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aField[nCntField].pos.x, g_aField[nCntField].pos.y, g_aField[nCntField].pos.z);
			D3DXMatrixMultiply(&g_aField[nCntField].mtxWorld, &g_aField[nCntField].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aField[nCntField].mtxWorld);

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

			pDevice->SetFVF(FVF_VERTEX_3D);


			pDevice->SetTexture(0, g_pTextureField);

			//�n��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
	}
}

void SetField(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{
		if (g_aField[nCntField].bUse == false)
		{
			g_aField[nCntField].pos = pos;
			g_aField[nCntField].rot = rot;
			g_aField[nCntField].bUse = true;
			break;
		}
	}
}