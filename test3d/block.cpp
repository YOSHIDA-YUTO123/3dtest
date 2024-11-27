//============================
//
// �u���b�N[block.cpp]
// Author:YOSHIDA YUUTO
//
//============================

//****************************
//�C���N���[�h�t�@�C��
//****************************
#include "block.h"

//****************************
//�O���[�o���ϐ��錾
//****************************
LPDIRECT3DTEXTURE9 g_apTextureBlock[128] = {};
LPD3DXMESH g_pMeshBlock = NULL;//���b�V��(���_���W)�ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatBlock = NULL;//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatBlock = 0;//�}�e���A���̐�
BLOCK g_Block;

//=============================
//�u���b�N�̏���������
//=============================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	g_Block.pos = D3DXVECTOR3(-100.0f, 50.0f, 0.0f);
	g_Block.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Block.Scal = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//g_Block.vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_Block.vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\obj.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatBlock,
		NULL,
		&g_dwNumMatBlock,
		&g_pMeshBlock);

	D3DXMATERIAL* pMat;//�}�e���A���ւ̃|�C���^

	//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatBlock->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatBlock; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//���̃t�@�C�������g�p���ăe�N�X�`����ǂݍ���
				//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTextureBlock[nCntMat]);
		}
	}

	//���_���W�̎擾
	int nNumVtx;//���_��
	DWORD sizeFVF;//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE* pVtxBuff;//���_�o�b�t�@�ւ̃|�C���^

	//���_���̎擾
	nNumVtx = g_pMeshBlock->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y�擾
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshBlock->GetFVF());

	//���_�o�b�t�@�̃��b�N
	g_pMeshBlock->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//���_���W���r���ău���b�N�̍ŏ��l,�ő�l���擾
		if (vtx.x < g_Block.vtxMin.x)
		{
			g_Block.vtxMin.x = vtx.x;
		}
		else if (vtx.y < g_Block.vtxMin.y)
		{
			g_Block.vtxMin.y = vtx.y;
		}
		else if (vtx.z < g_Block.vtxMin.z)
		{
			g_Block.vtxMin.z = vtx.z;
		}
		else if (vtx.x > g_Block.vtxMax.x)
		{
			g_Block.vtxMax.x = vtx.x;
		}
		else if (vtx.y > g_Block.vtxMax.y)
		{
			g_Block.vtxMax.y = vtx.y;
		}
		else if (vtx.z > g_Block.vtxMax.z)
		{
			g_Block.vtxMax.z = vtx.z;
		}

		//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFVF;
	}

	g_Block.Size.x = g_Block.vtxMax.x - g_Block.vtxMin.x;
	g_Block.Size.y = g_Block.vtxMax.y - g_Block.vtxMin.y;
	g_Block.Size.z = g_Block.vtxMax.z - g_Block.vtxMin.z;

	//���_�o�b�t�@�̃A�����b�N
	g_pMeshBlock->UnlockVertexBuffer();

}
//=============================
//�u���b�N�̏I������
//=============================
void UninitBlock(void)
{
	//���b�V���̔j��
	if (g_pMeshBlock != NULL)
	{
		g_pMeshBlock->Release();
		g_pMeshBlock = NULL;
	}

	//�}�e���A���̔j��
	if (g_pBuffMatBlock != NULL)
	{
		g_pBuffMatBlock->Release();
		g_pBuffMatBlock = NULL;
	}
}
//=============================
//�u���b�N�̍X�V����
//=============================
void UpdateBlock(void)
{
	//���͂Ȃ�
}
//=============================
//�u���b�N�̕`�揈��
//=============================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//�v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxScal;

	D3DMATERIAL9 matDef;//���݂̃}�e���A���ۑ��p

	D3DXMATERIAL* pMat;//�}�e���A���f�[�^�ւ̃|�C���^

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Block.mtxWorldBlock);

	//�傫���𔽉f
	D3DXMatrixScaling(&mtxScal, g_Block.Scal.x, g_Block.Scal.y, g_Block.Scal.z);
	D3DXMatrixMultiply(&g_Block.mtxWorldBlock, &g_Block.mtxWorldBlock, &mtxScal);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Block.rot.y, g_Block.rot.x, g_Block.rot.z);
	D3DXMatrixMultiply(&g_Block.mtxWorldBlock, &g_Block.mtxWorldBlock, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Block.pos.x, g_Block.pos.y, g_Block.pos.z);
	D3DXMatrixMultiply(&g_Block.mtxWorldBlock, &g_Block.mtxWorldBlock, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Block.mtxWorldBlock);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���̃f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatBlock->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatBlock; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureBlock[nCntMat]);

		//�u���b�N(�p�[�c)�̕`��
		g_pMeshBlock->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A�������ɖ߂�
	pDevice->SetMaterial(&matDef);
}
//=======================
//�u���b�N�̔��菈��
//=======================
bool CollisionBlock(void)
{
	PLAYER* pPlayer = GetPlayer();

	bool bLanding = false;

	if (pPlayer->posOld.y < g_Block.pos.y + g_Block.Size.y
		&&pPlayer->posOld.y + pPlayer->Size.y > g_Block.pos.y)
	{
		//���E�̂߂荞�ݔ���
		if (pPlayer->pos.z - pPlayer->Size.z * 0.5f < g_Block.pos.z + g_Block.Size.z * 0.5f
			&& pPlayer->pos.z + pPlayer->Size.z * 0.5f > g_Block.pos.z - g_Block.Size.z * 0.5f)
		{
			//x��������E�ɂ߂荞��	
			if (pPlayer->posOld.x + pPlayer->Size.x * 0.5f < g_Block.pos.x - g_Block.Size.x * 0.5f
				&& pPlayer->pos.x + pPlayer->Size.x * 0.5f > g_Block.pos.x - g_Block.Size.x * 0.5f)
			{
				pPlayer->pos.x = g_Block.pos.x - g_Block.Size.x * 0.5f - pPlayer->Size.x * 0.5f - 0.1f;
			}
			//x���E���獶�ɂ߂荞��	
			else if (pPlayer->posOld.x - pPlayer->Size.x * 0.5f > g_Block.pos.x + g_Block.Size.x * 0.5f
				&& pPlayer->pos.x - pPlayer->Size.x * 0.5f < g_Block.pos.x + g_Block.Size.x * 0.5f)
			{
				pPlayer->pos.x = g_Block.pos.x + g_Block.Size.x * 0.5f +  pPlayer->Size.x * 0.5f + 0.1f;
			}
		}

		//�O�ƌ��̔���
		if (pPlayer->pos.x - pPlayer->Size.x * 0.5f < g_Block.pos.x + g_Block.Size.x * 0.5f
			&& pPlayer->pos.x + pPlayer->Size.x * 0.5f > g_Block.pos.x - g_Block.Size.x * 0.5f)
		{
			//z���O������߂荞��
			if (pPlayer->posOld.z + pPlayer->Size.z * 0.5f < g_Block.pos.z - g_Block.Size.z * 0.5f
				&& pPlayer->pos.z + pPlayer->Size.z * 0.5f > g_Block.pos.z - g_Block.Size.z * 0.5f)
			{
				pPlayer->pos.z = g_Block.pos.z - g_Block.Size.z * 0.5f - pPlayer->Size.z * 0.5f - 0.1f;
			}
			//z���������߂荞��
			else if (pPlayer->posOld.z - pPlayer->Size.z * 0.5f > g_Block.pos.z + g_Block.Size.z * 0.5f
				&& pPlayer->pos.z - pPlayer->Size.z * 0.5f < g_Block.pos.z + g_Block.Size.z * 0.5f)
			{
				pPlayer->pos.z = g_Block.pos.z + pPlayer->Size.z + 0.1f;
			}
		}
	}

	if (pPlayer->pos.x - pPlayer->Size.x * 0.5f < g_Block.pos.x + g_Block.Size.x * 0.5f
		&& pPlayer->pos.x + pPlayer->Size.x * 0.5f > g_Block.pos.x - g_Block.Size.x * 0.5f)
	{
		if (pPlayer->pos.z - pPlayer->Size.z * 0.5f < g_Block.pos.z + g_Block.Size.z * 0.5f
			&& pPlayer->pos.z + pPlayer->Size.z * 0.5f > g_Block.pos.z - g_Block.Size.z * 0.5f)
		{
			//�ォ�牺
			if (pPlayer->posOld.y >= g_Block.pos.y + g_Block.Size.y
				&& pPlayer->pos.y < g_Block.pos.y + g_Block.Size.y)
			{
				bLanding = true;
				pPlayer->pos.y = g_Block.pos.y + g_Block.Size.y * 0.5f + pPlayer->Size.y * 0.45f + 0.1f;
				pPlayer->move.y = 0.0f;
			}
			//�������
			else if (pPlayer->posOld.y + pPlayer->Size.y * 0.5f < g_Block.pos.y - g_Block.Size.y * 0.5f
				&& pPlayer->pos.y + pPlayer->Size.y * 0.5f > g_Block.pos.y - g_Block.Size.y * 0.5f)
			{
				pPlayer->pos.y = g_Block.pos.y - pPlayer->Size.y;
				pPlayer->move.y = 0.0f;
			}

		}
	}
	return bLanding;
}