//============================
//
// �p�[�e�B�N��[particle.cpp]
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
#include "particle.h"

//****************************
//�}�N����`
//****************************
#define BULLET_WIDTH (25.0f) //����
#define BULLET_HEIGHT (25.0f) //����
#define MAX_PARTICLE (128) //�e�̍ő吔
#define MAX_MOVE (5.0f) //�ړ���

//****************************
//�O���[�o���ϐ��錾
//****************************
PARTICLE g_aParticle[MAX_PARTICLE];

//============================
//�e�̏���������
//============================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		g_aParticle[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCnt].col = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
		g_aParticle[nCnt].nLife = 0;
		g_aParticle[nCnt].bUse = false;
	}
}
//============================
//�e�̏I������
//============================
void UninitParticle(void)
{

}
//============================
//�e�̍X�V����
//============================
void UpdateParticle(void)
{
	int nCntParticle, nCntApper;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXCOLOR col;
	D3DXVECTOR3 fScal;

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{//�g�p���Ă���

			//�p�[�e�B�N������
			for (nCntApper = 0; nCntApper < 5/*���������������q�̐�*/; nCntApper++)
			{
				float fAngleX = (float)(rand() % 629 - 314) * 0.01f;
				float fAngleY = (float)(rand() % 629 - 314) * 0.01f;
				float fAngleZ = (float)(rand() % 629 - 314) * 0.01f;

				float fMove = ((float)(rand() % 5) + 0.5f);

				//�ʒu�̐ݒ�pos
				pos = g_aParticle[nCntParticle].pos;

				//�ړ��ʂ̐ݒ�
				move.x = sinf(fAngleX) * fMove;
				move.y = cosf(fAngleY) * fMove;
				move.z = cosf(fAngleZ) * fMove;

				//�F�̐ݒ�col
				col = g_aParticle[nCntParticle].col;

				//���a�̐ݒ�fRadius
				fScal.x = ((float)(rand() % 1)+ 1.0f);
				fScal.y = ((float)(rand() % 1)+ 1.0f);
				fScal.z = ((float)(rand() % 1)+ 1.0f);

				int nLife = (rand() % 60) + 1;

				//�G�t�F�N�g�̐ݒ�SetEffect
				SetEffect(pos, move, col, nLife, fScal);
			}

			g_aParticle[nCntParticle].nLife--;

			//�����̐ݒ�
			if (g_aParticle[nCntParticle].nLife <= 0)//�������s����
			{
				g_aParticle[nCntParticle].bUse = false;
			}
		}
	}

}
//============================
//�e�̕`�揈��
//============================
void DrawParticle(void)
{
}
//============================
//�e�̕`�揈��
//============================
void SetParticle(D3DXVECTOR3 pos ,int nLife, D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse == false)
		{
			g_aParticle[nCnt].pos = pos;
			g_aParticle[nCnt].col = col;
			g_aParticle[nCnt].nLife = nLife;
			g_aParticle[nCnt].bUse = true;

			break;
		}
	}
}
