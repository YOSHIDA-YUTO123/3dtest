//============================
//
// �e[bullet.h]
// Author:YOSHIDA YUUTO
//
//============================

#ifndef _BULLET_H_
#define _BULLET_H_

//****************************
//�C���N���[�h�t�@�C��
//****************************
#include"main.h"
#include"shadow.h"

//****************************
//�e�̎��
//****************************
typedef enum
{
	BULLETTYPE_PLAYER=0,
	BULLETTYPE_ENEMY,
	BULLETTYPE_MAX
}BULLETTYPE;

//****************************
//�e�̍\����
//****************************
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	D3DXVECTOR3 dir;//����
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X
	int nIdxShadow;//
	int nLife;//����
	bool bUse;//�g�p���Ă��邩�ǂ���
}BULLET;

//****************************
//�v���g�^�C�v�錾
//****************************
void InitBullet(void);//�e�̏���������
void UninitBullet(void);//�e�̏I������
void UpdateBullet(void);//�e�̍X�V����
void DrawBullet(void);//�e�̕`�揈��
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 dir, D3DXVECTOR3 move, int nLife);//�e�̐ݒ菈��
#endif
