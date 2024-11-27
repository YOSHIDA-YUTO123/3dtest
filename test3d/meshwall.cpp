//=================================
//
// ���b�V���E�H�[��[meshfield.cpp]
// Author:YOSHIDA YUUTO
//
//=================================

//****************************
//�C���N���[�h�t�@�C��
//****************************
#include "meshwall.h"

//****************************
//�O���[�o���ϐ��錾
//****************************
LPDIRECT3DTEXTURE9 g_pTextureMeshWall = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL; //���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
MESHWALL g_MeshWall;

//===============================
//���b�V���E�H�[���̏���������
//===============================
void InitMeshWall(void)
{
	int nCnt = 0;

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();//�f�o�C�X���擾

		//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&g_pTextureMeshWall);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * WALL_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * WALL_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall,
		NULL);

	g_MeshWall.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshWall.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	float fTexX = 1.0f / WALL_XVTX;
	float fTexY = 1.0f / WALL_ZVTX;

	D3DXVECTOR3 nor;

	int radius = 700;

	//�c
	for (int nCntV = 0; nCntV < WALL_ZVTX + 1; nCntV++)
	{
		//��
		for (int nCntH = 0; nCntH < WALL_XVTX + 1; nCntH++)
		{
			float fAngel = (D3DX_PI * 2.0f) / WALL_XVTX * nCntH;
			
			//���_���W�̐ݒ�
			pVtx[nCnt].Pos = D3DXVECTOR3(
				MAX_WALL_WIDTH + sinf(fAngel) * radius,
				500.0f - ((nCntV * MAX_WALL_WIDTH)),
				MAX_WALL_WIDTH + cosf(fAngel) * radius);
		
			nor = pVtx[nCnt].Pos - g_MeshWall.pos;

			//�@���x�N�g���̐ݒ�
			pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			
			D3DXVec3Normalize(&pVtx[nCnt].nor,&nor);

			//���_�J���[�̐ݒ�
			pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W�̐ݒ�
			pVtx[nCnt].tex = D3DXVECTOR2(fTexX * nCntH, nCntV * fTexY);

			nCnt++;//���Z

		}
	}

	g_pVtxBuffMeshWall->Unlock();

	WORD* pIdx;

	//�C���f�b�N�X�o�b�t�@�̃��b�N
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	int IndxCount3 = WALL_XVTX + 1;//X

	int IdxCnt = 0;//�z��

	int Num = 0;//

	//�C���f�b�N�X�̐ݒ�
	for (int IndxCount1 = 0; IndxCount1 < WALL_ZVTX; IndxCount1++)
	{
		for (int IndxCount2 = 0; IndxCount2 <= WALL_XVTX; IndxCount2++, IndxCount3++, Num++)
		{
			pIdx[IdxCnt] = IndxCount3;
			pIdx[IdxCnt + 1] = Num;
			IdxCnt +=2;
		}

		if (IndxCount1 < WALL_ZVTX - 1)
		{
			pIdx[IdxCnt] = Num - 1;
			pIdx[IdxCnt + 1] = IndxCount3;
			IdxCnt += 2;
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBuffMeshWall->Unlock();
}

//===============================
//���b�V���E�H�[���̏I������
//===============================ccc
void UninitMeshWall(void)
{
	//�e�N�X�`���̉��
	if (g_pTextureMeshWall != NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffMeshWall != NULL)
	{
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}

//===============================
//���b�V���E�H�[���̍X�V����
//===============================
void UpdateMeshWall(void)
{

}

//===============================
//���b�V���E�H�[���̕`�揈��
//===============================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//�v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_MeshWall.mtxWorldMeshWall);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshWall.rot.y, g_MeshWall.rot.x, g_MeshWall.rot.z);
	D3DXMatrixMultiply(&g_MeshWall.mtxWorldMeshWall, &g_MeshWall.mtxWorldMeshWall, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_MeshWall.pos.x, g_MeshWall.pos.y, g_MeshWall.pos.z);
	D3DXMatrixMultiply(&g_MeshWall.mtxWorldMeshWall, &g_MeshWall.mtxWorldMeshWall, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshWall.mtxWorldMeshWall);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshWall);

	//�e�N�X�`���t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshWall);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, WALL_VERTEX, 0, WALL_POLYGON);
}
