//============================
//
// ��[wall.cpp]
// Author:YOSHIDA YUUTO
//
//============================

//****************************
//�C���N���[�h�t�@�C��
//****************************
#include "wall.h"
#include "player.h"

//****************************
//�}�N����`
//****************************
#define MAX_WALL (4) //�ǂ̍ő吔

//****************************
//�O���[�o���ϐ��錾
//****************************
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL; //���_�o�b�t�@�ւ̃|�C���^
//D3DXVECTOR3 g_posWall; //�ʒu
//D3DXVECTOR3 g_rotWall; //����
//D3DXMATRIX g_mtxWorldWall;//���[���h�}�g���b�N�X
WALL g_Wall[MAX_WALL];//�ǂ̍\����

//=============================
//�ǂ̏���������
//=============================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&g_pTextureWall);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	VERTEX_3D* pVtx = NULL;

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_Wall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCntWall].vecLine = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCntWall].vecPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCntWall].fA = 1.0f;
		g_Wall[nCntWall].fWidth = 0.0f;
		g_Wall[nCntWall].fHeight = 0.0f;
		g_Wall[nCntWall].bUse = false;
		g_Wall[nCntWall].fScal = D3DXVECTOR3(0.0f,0.0f,0.0f);//������߂�
	}

	//���_�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//���_���W�̐ݒ�
		pVtx[0].Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		pVtx[1].Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		pVtx[2].Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		pVtx[3].Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);

		//�e���_�̖@���̐ݒ�(�x�N�g���̑傫���͂P�ɂ���K�v������)
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

	g_pVtxBuffWall->Unlock();
}
//=============================
//�ǂ̏I������
//=============================
void UninitWall(void)
{
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}
//=============================
//�ǂ̍X�V����
//=============================
void UpdateWall(void)
{
	
}
//=============================
//�ǂ̕`�揈��
//=============================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//�v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans,mtxScal;

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Wall[nCntWall].mtxWorld);

			////�傫���𔽉f
			//D3DXMatrixScaling(&mtxScal, g_Wall[nCntWall].fScal.x, g_Wall[nCntWall].fScal.y, g_Wall[nCntWall].fScal.z);
			//D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorld, &g_Wall[nCntWall].mtxWorld, &mtxScal);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[nCntWall].rot.y, g_Wall[nCntWall].rot.x, g_Wall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorld, &g_Wall[nCntWall].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Wall[nCntWall].pos.x, g_Wall[nCntWall].pos.y, g_Wall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorld, &g_Wall[nCntWall].mtxWorld, &mtxTrans);
			
			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Wall[nCntWall].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//�e�N�X�`���t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureWall);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall * 4, 2);
		}
	}
}
//=============================
//�ǂ̐ݒ菈��
//=============================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float fA,float fWidth,float fHeight)
{
	VERTEX_3D* pVtx;

	int nCntWall;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == false)
		{
			g_Wall[nCntWall].pos = pos;
			g_Wall[nCntWall].fWidth = fWidth;
			g_Wall[nCntWall].fHeight = fHeight;
			g_Wall[nCntWall].fA = fA;
			g_Wall[nCntWall].rot = rot;

			g_Wall[nCntWall].bUse = true;

			//���_���W�̐ݒ�
			pVtx[0].Pos = D3DXVECTOR3(0.0f, fHeight, 0.0f);
			pVtx[1].Pos = D3DXVECTOR3(fWidth * 2.0f, fHeight, 0.0f);
			pVtx[2].Pos = D3DXVECTOR3(0.0f, -fHeight, 0.0f);
			pVtx[3].Pos = D3DXVECTOR3(fWidth * 2.0f, -fHeight, 0.0f);

			//�e���_�̖@���̐ݒ�(�x�N�g���̑傫���͂P�ɂ���K�v������)
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fA);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fA);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fA);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fA);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}

	g_pVtxBuffWall->Unlock();
}
//==========================
//�ǂƂ̏Փ˔���
//==========================
void CollisionWall(void)
{
	VERTEX_3D* pVtx;

	PLAYER* pPlayer = GetPlayer();

	//���_�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		int nCntNext = (nCnt + 1) % MAX_WALL;

		if (g_Wall[nCnt].bUse == true && g_Wall[nCntNext].bUse == true)
		{
			D3DXVECTOR3 pos = g_Wall[nCnt].pos;

			//�v�Z�p
			D3DXVECTOR3 vecA, vecB;

			D3DXVECTOR3 PlayerVecPos(pPlayer->pos.x,0.0f,pPlayer->pos.z);

			vecA = g_Wall[nCntNext].pos - pos;

			D3DXVec3Normalize(&vecA,&vecA);

			vecB = PlayerVecPos - pos;

			D3DXVec3Normalize(&vecB, &vecB);

			D3DXVECTOR3 Cross = {};

			D3DXVec3Cross(&Cross, &vecA, &vecB);

			if (Cross.y < 0.0f)
			{
				pPlayer->pos = pPlayer->posOld;
				pPlayer->move.z = 0.0f;
			}
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffWall->Unlock();
}
