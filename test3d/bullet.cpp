//============================
//
// �e[billboard.cpp]
// Author:YOSHIDA YUUTO
//
//============================

//****************************
//�C���N���[�h�t�@�C��
//****************************
#include "bullet.h"
#include "input.h"
#include "player.h"
#include "camera.h"
#include "shadow.h"
#include "explosion.h"
#include "effect.h"

//****************************
//�}�N����`
//****************************
#define BULLET_WIDTH (25.0f) //����
#define BULLET_HEIGHT (25.0f) //����
#define MAX_BULLET (128) //�e�̍ő吔
#define MAX_MOVE (5.0f) //�ړ���

//****************************
//�O���[�o���ϐ��錾
//****************************
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL; //���_�o�b�t�@�ւ̃|�C���^
BULLET g_Bullet[MAX_BULLET];

//============================
//�e�̏���������
//============================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_pTextureBullet);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_3D* pVtx = NULL;

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		g_Bullet[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].nLife = 0;
		g_Bullet[nCnt].bUse = false;
	}
	
	//���_�o�b�t�@�����b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].Pos = D3DXVECTOR3(g_Bullet[nCnt].pos.x - BULLET_WIDTH, g_Bullet[nCnt].pos.y + BULLET_HEIGHT, 0.0f);
		pVtx[1].Pos = D3DXVECTOR3(g_Bullet[nCnt].pos.x + BULLET_WIDTH, g_Bullet[nCnt].pos.y + BULLET_HEIGHT, 0.0f);
		pVtx[2].Pos = D3DXVECTOR3(g_Bullet[nCnt].pos.x - BULLET_WIDTH, g_Bullet[nCnt].pos.y - BULLET_HEIGHT, 0.0f);
		pVtx[3].Pos = D3DXVECTOR3(g_Bullet[nCnt].pos.x + BULLET_WIDTH, g_Bullet[nCnt].pos.y - BULLET_HEIGHT, 0.0f);

		//�e���_�̖@���̐ݒ�(�x�N�g���̑傫���͂P�ɂ���K�v������)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);//�J�����ɑ΂��Đ�����
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
	g_pVtxBuffBullet->Unlock();
}
//============================
//�e�̏I������
//============================
void UninitBullet(void)
{
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//���_�o�b�t�@�̉��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}
//============================
//�e�̍X�V����
//============================
void UpdateBullet(void)
{
	PLAYER* pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		//�g�p����Ă���
		if (g_Bullet[nCnt].bUse == true)
		{	
			g_Bullet[nCnt].pos += g_Bullet[nCnt].move;
			
			g_Bullet[nCnt].nLife--;

			SetEffect(g_Bullet[nCnt].pos, D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 30,D3DXVECTOR3(1.0f,1.0f,1.0f));
			SetPositionShadow(g_Bullet[nCnt].nIdxShadow, D3DXVECTOR3(g_Bullet[nCnt].pos.x, 1.0f, g_Bullet[nCnt].pos.z));

			//�������s����
			if (g_Bullet[nCnt].nLife <= 0)
			{
				g_Bullet[nCnt].bUse = false;
				EnableShadow(g_Bullet[nCnt].nIdxShadow);//�e�̎g�p���

				SetExplosion(g_Bullet[nCnt].pos);
			}
		}
	}
}
//============================
//�e�̕`�揈��
//============================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	CAMERA* pCamera = GetCamera();

	//�A���t�@�e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, NULL);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxView;

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		if (g_Bullet[nCnt].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Bullet[nCnt].mtxWorld);

			pDevice->GetTransform(D3DTS_VIEW, &mtxView);//�r���[�}�g���b�N�X�̎擾

			//�J�����̋t�s��̐ݒ�
			g_Bullet[nCnt].mtxWorld._11 = mtxView._11;
			g_Bullet[nCnt].mtxWorld._12 = mtxView._21;
			g_Bullet[nCnt].mtxWorld._13 = mtxView._31;
			g_Bullet[nCnt].mtxWorld._21 = mtxView._12;
			g_Bullet[nCnt].mtxWorld._22 = mtxView._22;
			g_Bullet[nCnt].mtxWorld._23 = mtxView._32;
			g_Bullet[nCnt].mtxWorld._31 = mtxView._13;
			g_Bullet[nCnt].mtxWorld._32 = mtxView._23;
			g_Bullet[nCnt].mtxWorld._33 = mtxView._33;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Bullet[nCnt].pos.x + pCamera->rot.y, g_Bullet[nCnt].pos.y + pCamera->rot.y, g_Bullet[nCnt].pos.z + pCamera->rot.y);
			D3DXMatrixMultiply(&g_Bullet[nCnt].mtxWorld, &g_Bullet[nCnt].mtxWorld, &mtxTrans);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Bullet[nCnt].mtxWorld);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			//�e�N�X�`���t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}

	//�A���t�@�e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//============================
//�e�̕`�揈��
//============================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 dir, D3DXVECTOR3 move, int nLife)
{
	VERTEX_3D* pVtx = NULL;

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		if (g_Bullet[nCnt].bUse == false)
		{
			g_Bullet[nCnt].nIdxShadow = SetShadow(D3DXVECTOR3(g_Bullet[nCnt].pos.x, 1.0f, g_Bullet[nCnt].pos.z) ,D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			
			g_Bullet[nCnt].pos = pos;
			g_Bullet[nCnt].move = move;
			g_Bullet[nCnt].dir = dir;
			g_Bullet[nCnt].nLife = nLife;
			g_Bullet[nCnt].bUse = true;

			break;
		}
	}
}
