//============================
//
// �v���C���[[player.cpp]
// Author:YOSHIDA YUUTO
//
//============================

//****************************
//�C���N���[�h�t�@�C��
//****************************
#include "player.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "billboard.h"
#include "bullet.h"
#include "particle.h"
#include "block.h"
#include "wall.h"

//****************************
//�O���[�o���ϐ��錾
//****************************
LPDIRECT3DTEXTURE9 g_apTexturePlayer[128] = {};//�v���C���[�̃e�N�X�`���ւ̃|�C���^
LPD3DXMESH g_pMeshPlayer = NULL;//���b�V��(���_���W)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatPlayer = NULL;//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatPlayer = 0;//�}�e���A���̐�
PLAYER g_player;//�v���C���[�\����

//============================
//�v���C���[�̏���������
//============================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	CAMERA* pCamera = GetCamera();

	g_player.nIdxShadow = SetShadow(D3DXVECTOR3(g_player.pos.x, g_player.pos.y, g_player.pos.z), D3DXVECTOR3(g_player.rot.x, g_player.rot.y, g_player.rot.z));
	g_player.pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);

	//g_player.vtxMinPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_player.vtxMaxPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDestPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.bJump = false;
	g_player.bDisp = true;

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\obj2.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer);

	D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

	//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//���̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���
				//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTexturePlayer[nCntMat]);
		}
	}

	//���_���W�̎擾
	int nNumVtx;//���_��
	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

	//���_���̎擾
	nNumVtx = g_pMeshPlayer->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y�擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshPlayer->GetFVF());

	//���_�o�b�t�@�̃��b�N
	g_pMeshPlayer->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//���_���W���r���ău���b�N�̍ŏ��l,�ő�l���擾
		if (vtx.x < g_player.vtxMinPlayer.x)
		{
			g_player.vtxMinPlayer.x = vtx.x;
		}
		else if (vtx.y < g_player.vtxMinPlayer.y)
		{
			g_player.vtxMinPlayer.y = vtx.y;
		}
		else if (vtx.z < g_player.vtxMinPlayer.z)
		{
			g_player.vtxMinPlayer.z = vtx.z;
		}

		else if (vtx.x > g_player.vtxMaxPlayer.x)
		{
			g_player.vtxMaxPlayer.x = vtx.x;
		}

		else if (vtx.y > g_player.vtxMaxPlayer.y)
		{
			g_player.vtxMaxPlayer.y = vtx.y;
		}

		else if (vtx.z > g_player.vtxMaxPlayer.z)
		{
			g_player.vtxMaxPlayer.z = vtx.z;
		}

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}

	g_player.Size.x = g_player.vtxMaxPlayer.x - g_player.vtxMinPlayer.x;
	g_player.Size.y = g_player.vtxMaxPlayer.y - g_player.vtxMinPlayer.y;
	g_player.Size.z = g_player.vtxMaxPlayer.z - g_player.vtxMinPlayer.z;

	//���_�o�b�t�@�̃A�����b�N
	g_pMeshPlayer->UnlockVertexBuffer();

}
//============================
//�v���C���[�̏I������
//============================
void UninitPlayer(void)
{
	for (int nCnt = 0; nCnt < (int)g_dwNumMatPlayer; nCnt++)
	{
		if (g_apTexturePlayer[nCnt] != NULL)
		{
			g_apTexturePlayer[nCnt]->Release();
			g_apTexturePlayer[nCnt] = NULL;
		}
	}

	//���b�V���̔j��
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}
}
//============================
//�v���C���[�̍X�V����
//============================
void UpdatePlayer(void)
{
	CAMERA* pCamera = GetCamera();

	if (g_player.bDisp == true)
	{
		SetPositionShadow(g_player.nIdxShadow, D3DXVECTOR3(g_player.pos.x, 1.0f, g_player.pos.z));
	}

	if (GetKeyboardPress(DIK_A) == true)
	{
		//�v���C���[�̈ړ�(��)
		if (GetKeyboardPress(DIK_W) == true)
		{
			g_player.move.x += sinf(pCamera->rot.y - D3DX_PI * 0.25f) * PLAYER_MOVE;
			g_player.move.z += cosf(pCamera->rot.y - D3DX_PI * 0.25f) * PLAYER_MOVE;

			g_player.rotDestPlayer.y = pCamera->rot.y + D3DX_PI * 0.75f;
		}
		//�v���C���[�̈ړ�(��)
		else if (GetKeyboardPress(DIK_S) == true)
		{
			g_player.move.x += sinf(pCamera->rot.y - D3DX_PI * 0.75f) * PLAYER_MOVE;
			g_player.move.z += cosf(pCamera->rot.y - D3DX_PI * 0.75f) * PLAYER_MOVE;

			g_player.rotDestPlayer.y = pCamera->rot.y + D3DX_PI * 0.25f;
		}
		//�v���C���[�̈ړ�(��)
		else
		{
			g_player.move.z += sinf(pCamera->rot.y) * PLAYER_MOVE;
			g_player.move.x -= cosf(pCamera->rot.y) * PLAYER_MOVE;

			g_player.rotDestPlayer.y = pCamera->rot.y + D3DX_PI * 0.5f;

			//if (g_player.rotDestPlayer.y < D3DX_PI * 2.0f)
			//{
			//	g_player.rotDestPlayer.y -= D3DX_PI;
			//}
		}

	}
	//�v���C���[�̈ړ�(�E)
	else if (GetKeyboardPress(DIK_D) == true)
	{
		//�v���C���[�̈ړ�(��)
		if (GetKeyboardPress(DIK_W) == true)
		{
			g_player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.25f) * PLAYER_MOVE;
			g_player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.25f) * PLAYER_MOVE;

			g_player.rotDestPlayer.y = pCamera->rot.y - D3DX_PI * 0.75f;
		}
		//�v���C���[�̈ړ�(��)
		else if (GetKeyboardPress(DIK_S) == true)
		{
			g_player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.75f) * PLAYER_MOVE;
			g_player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.75f) * PLAYER_MOVE;

			g_player.rotDestPlayer.y = pCamera->rot.y - D3DX_PI * 0.25f;
		}
		//�v���C���[�̈ړ�(�E)
		else
		{
			g_player.move.z -= sinf(pCamera->rot.y) * PLAYER_MOVE;
			g_player.move.x += cosf(pCamera->rot.y) * PLAYER_MOVE;

			g_player.rotDestPlayer.y = pCamera->rot.y - D3DX_PI * 0.5f;
		}

	}
	//�v���C���[�̈ړ�(��)
	else if (GetKeyboardPress(DIK_W) == true)
	{
		g_player.move.x += sinf(pCamera->rot.y) * PLAYER_MOVE;
		g_player.move.z += cosf(pCamera->rot.y) * PLAYER_MOVE;

		g_player.rotDestPlayer.y = pCamera->rot.y + D3DX_PI;

		//pCamera->posV.z += PLAYER_MOVE;
		//pCamera->posR.z += PLAYER_MOVE;
	}
	//�v���C���[�̈ړ�(��)
	else if (GetKeyboardPress(DIK_S) == true)
	{
		g_player.move.x -= sinf(pCamera->rot.y) * PLAYER_MOVE;
		g_player.move.z -= cosf(pCamera->rot.y) * PLAYER_MOVE;

		g_player.rotDestPlayer.y = pCamera->rot.y;

		//pCamera->posV.z -= PLAYER_MOVE;
		//pCamera->posR.z -= PLAYER_MOVE;
	}

	//�ړ��ʂ�����
	g_player.move.x += (0.0f - g_player.move.x) * 0.25f;
	//g_player.move.y += (0.0f - g_player.move.y) * 0.25f;
	g_player.move.z += (0.0f - g_player.move.z) * 0.25f;

	//�O��̈ʒu��ۑ�
	g_player.posOld = g_player.pos;

	//�v���C���[�̈ʒu�̍X�V
	g_player.pos += g_player.move;

	//�v���C���[�̏d��ddd
	g_player.move.y -= 1.0f;

	if (CollisionBlock() == true)
	{
		g_player.bJump = true;
	}
	else
	{
		g_player.bJump = false;
	}
	
	CollisionWall();

	//���n
	if (g_player.pos.y <= 0.0f)
	{
		g_player.pos.y = 0.0f;
		g_player.bJump = true;
	}

	if (KeyboardTrigger(DIK_SPACE) == true && g_player.bJump == true)
	{
		g_player.move.y = 15.0f;
		g_player.bJump = false;
	}

	if (g_player.rotDestPlayer.y - g_player.rot.y >= D3DX_PI)
	{
		g_player.rot.y += D3DX_PI * 2.0f;
	}
	else if (g_player.rotDestPlayer.y - g_player.rot.y <= -D3DX_PI)
	{
		g_player.rot.y -= D3DX_PI * 2.0f;
	}

	if (KeyboardTrigger(DIK_RETURN) == true)
	{
		SetBullet(D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 20, g_player.pos.z),//pos
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),//dir
			D3DXVECTOR3(sinf(g_player.rot.y + D3DX_PI) * 5.0f, 0.0f, cosf(g_player.rot.y + D3DX_PI) * 5.0f),//move
			50);//life

		SetParticle(g_player.pos, 50, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	}

	g_player.rot.y += (g_player.rotDestPlayer.y - g_player.rot.y) * 0.1f;
}
//============================
//�v���C���[�̕`�揈��
//============================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//�v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans,mtxSize;

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_player.mtxWorldPlayer);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorldPlayer, &g_player.mtxWorldPlayer, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorldPlayer, &g_player.mtxWorldPlayer, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorldPlayer);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexturePlayer[nCntMat]);//����NULL

		//���f��(�p�[�c)�̕`��
		g_pMeshPlayer->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A�������ɖ߂�
	pDevice->SetMaterial(&matDef);
}
//============================
//�v���C���[�̎擾����
//============================
PLAYER* GetPlayer(void)
{
	return &g_player;
}
