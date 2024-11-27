//============================
//
// �e[shadow.h]
// Author:YOSHIDA YUUTO
//
//============================

#ifndef _SHADOW_H_
#define _SHADOW_H_

//****************************
//�C���N���[�h�t�@�C��
//****************************
#include"main.h"

//****************************
//�e�̍\����
//****************************
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	bool bUse;
}SHADOW;

//****************************
//�v���g�^�C�v�錾
//****************************
void InitShadow(void);//�e�̏���������
void UninitShadow(void);//�e�̏I������
void UpdateShadow(void);//�e�̍X�V����
void DrawShadow(void);//�e�̕`�揈��
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);//�e�̐ݒ菈��
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);//�e�̈ʒu�ݒ菈��
void EnableShadow(int nIdxShadow); //�e�̎g�p��Ԃ̐ݒ菈��
//SHADOW* GetShadow(void);
#endif
