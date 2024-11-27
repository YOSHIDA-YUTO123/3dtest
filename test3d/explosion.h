//============================
//
// ����[explosion.h]
// Author:YOSHIDA YUUTO
//
//============================

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//****************************
//�C���N���[�h�t�@�C��
//****************************
#include"main.h"

//****************************
//�����̍\����
//****************************
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X
	int nCounterAnim;
	int nPatternAnim;
	int nIdxShadow;//�ԍ�
	int nLife;//����
	bool bUse;//�g�p���Ă��邩�ǂ���
}EXPLOSION;

//****************************
//�v���g�^�C�v�錾
//****************************
void InitExplosion(void);//�����̏���������
void UninitExplosion(void);//�����̏I������
void UpdateExplosion(void);//�����̍X�V����
void DrawExplosion(void);//�����̕`�揈��
void SetExplosion(D3DXVECTOR3 pos);//�����̐ݒ菈��
#endif
