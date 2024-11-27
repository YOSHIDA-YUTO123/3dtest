//=================================
//
// ���b�V���X�t�B�A [meshsphere.cpp]
// Author:YOSHIDA YUUTO
//
//=================================

//****************************
//�C���N���[�h�t�@�C��
//****************************
#include "sphere.h"
#include "input.h"

//****************************
//�O���[�o���ϐ��錾
//****************************
LPDIRECT3DTEXTURE9 g_pTextureMeshSphere = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshSphere = NULL; //���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshSphere = NULL;//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
MESHSPHERE g_MeshSphere;
D3DPRIMITIVETYPE pType;

//===============================
//���b�V���E�H�[���̏���������
//===============================
void InitMeshSphere(void)
{
	int nCnt = 0;

	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();//�f�o�C�X���擾

		//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&g_pTextureMeshSphere);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshSphere,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * 8,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshSphere,
		NULL);

	g_MeshSphere.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshSphere.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pType = D3DPT_TRIANGLEFAN;

	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffMeshSphere->Lock(0, 0, (void**)&pVtx, 0);

	float fTexX = 1.0f / SPHERE_XVTX;
	float fTexY = 1.0f / SPHERE_ZVTX;

	D3DXVECTOR3 nor;

	int radius = 500;

	//�c
	for (int nCntV = 0; nCntV < SPHERE_ZVTX + 1; nCntV++)
	{
		//��
		for (int nCntH = 0; nCntH < SPHERE_XVTX + 1; nCntH++)
		{
			float fAngel = (D3DX_PI * 2.0f) / SPHERE_XVTX * nCntH;

			////���_���W�̐ݒ�
			//pVtx[nCnt].Pos = D3DXVECTOR3(
			//);

			//nor = pVtx[nCnt].Pos - g_MeshSphere.pos;

			////�@���x�N�g���̐ݒ�
			//pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			////���_�J���[�̐ݒ�
			//pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			////�e�N�X�`�����W�̐ݒ�
			//pVtx[nCnt].tex = D3DXVECTOR2(fTexX * nCntH, nCntV * fTexY);

			nCnt++;//���Z

		}
	}

	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		//float fAngleSp = (D3DX_PI * 2.0f) / 5 * nCnt;
		//
		//pVtx[nCntSp].Pos = D3DXVECTOR3(sinf(fAngleSp) * 100.0f, 80.0f, cosf(fAngleSp) * 100.0f);

		//�@���x�N�g���̐ݒ�
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[nCnt].tex = D3DXVECTOR2(fTexX * nCnt, nCnt * fTexY);
	}

	if (pType == D3DPT_TRIANGLEFAN)
	{

		pVtx[0].Pos = D3DXVECTOR3(0.0f, 200.0f, 0.0f);

		pVtx[1].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 0) * 100.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 0) * 100.0f);
		pVtx[2].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 1) * 100.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 1) * 100.0f);
		pVtx[3].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 2) * 100.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 2) * 100.0f);
		pVtx[4].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 3) * 100.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 3) * 100.0f);
		pVtx[5].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 4) * 100.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 4) * 100.0f);
		pVtx[6].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 5) * 100.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 5) * 100.0f);
		pVtx[7].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 6) * 100.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 6) * 100.0f);
	}
	else if (pType == D3DPT_TRIANGLESTRIP)
	{
		pVtx[8].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 0) * 50.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 0) * 50.0f);
		pVtx[9].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 1) * 0.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 1) * 0.0f);
		pVtx[10].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 2) * 0.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 2) * 0.0f);
		pVtx[11].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 3) * 0.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 3) * 0.0f);
		pVtx[12].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 4) * 0.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 4) * 0.0f);
		pVtx[13].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 5) * 0.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 5) * 0.0f);
		pVtx[14].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 6) * 0.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 6) * 0.0f);
		pVtx[15].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 7) * 0.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 7) * 0.0f);
	}
	g_pVtxBuffMeshSphere->Unlock();

	WORD* pIdx;

	//�C���f�b�N�X�o�b�t�@�̃��b�N
	g_pIdxBuffMeshSphere->Lock(0, 0, (void**)&pIdx, 0);

	int IndxCount3 = SPHERE_XVTX + 1;//X

	int IdxCnt = 0;//�z��

	int Num = 0;//

	////�C���f�b�N�X�̐ݒ�
	//for (int IndxCount1 = 0; IndxCount1 < SPHERE_ZVTX; IndxCount1++)
	//{
	//	for (int IndxCount2 = 0; IndxCount2 <= SPHERE_XVTX; IndxCount2++, IndxCount3++, Num++)
	//	{
	//		pIdx[IdxCnt] = IndxCount3;
	//		pIdx[IdxCnt + 1] = Num;
	//		IdxCnt += 2;
	//	}

	//	if (IndxCount1 < SPHERE_ZVTX - 1)
	//	{
	//		pIdx[IdxCnt] = Num - 1;
	//		pIdx[IdxCnt + 1] = IndxCount3;
	//		IdxCnt += 2;
	//	}
	//}

	pIdx[0] = 0;
	pIdx[1] = 1;
	pIdx[2] = 2;
	pIdx[3] = 3;
	pIdx[4] = 4;
	pIdx[5] = 5;
	pIdx[6] = 6;
	pIdx[7] = 7;
	pIdx[8] = 8;
	pIdx[9] = 9;
	pIdx[10] = 10;
	pIdx[11] = 11;
	pIdx[12] = 12;
	pIdx[13] = 13;
	pIdx[14] = 14;
	pIdx[15] = 15;


	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	g_pIdxBuffMeshSphere->Unlock();
}

//===============================
//���b�V���E�H�[���̏I������
//===============================ccc
void UninitMeshSphere(void)
{
	//�e�N�X�`���̉��
	if (g_pTextureMeshSphere != NULL)
	{
		g_pTextureMeshSphere->Release();
		g_pTextureMeshSphere = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_pVtxBuffMeshSphere != NULL)
	{
		g_pVtxBuffMeshSphere->Release();
		g_pVtxBuffMeshSphere = NULL;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (g_pIdxBuffMeshSphere != NULL)
	{
		g_pIdxBuffMeshSphere->Release();
		g_pIdxBuffMeshSphere = NULL;
	}
}

//===============================
//���b�V���E�H�[���̍X�V����
//===============================
void UpdateMeshSphere(void)
{
	if (KeyboardTrigger(DIK_L))
	{
		pType = D3DPT_TRIANGLESTRIP;
	}
}

//===============================
//���b�V���E�H�[���̕`�揈��
//===============================
void DrawMeshSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//�v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_MeshSphere.mtxWorldMeshSphere);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshSphere.rot.y, g_MeshSphere.rot.x, g_MeshSphere.rot.z);
	D3DXMatrixMultiply(&g_MeshSphere.mtxWorldMeshSphere, &g_MeshSphere.mtxWorldMeshSphere, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_MeshSphere.pos.x, g_MeshSphere.pos.y, g_MeshSphere.pos.z);
	D3DXMatrixMultiply(&g_MeshSphere.mtxWorldMeshSphere, &g_MeshSphere.mtxWorldMeshSphere, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshSphere.mtxWorldMeshSphere);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMeshSphere, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(g_pIdxBuffMeshSphere);

	//�e�N�X�`���t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureMeshSphere);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN, 0, 0, 16, 0, 16);

	if (pType == D3DPT_TRIANGLESTRIP)
	{
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 16, 0, 16);
	}
}
