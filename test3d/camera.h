//============================
//
// �J����[camera.h]
// Author:YOSHIDA YUUTO
//
//============================

#ifndef _CAMERA_H_
#define _CAMERA_H_

//***********************
//�C���N���[�h�t�@�C��
//***********************

#include"main.h"

//*******************
//�J�����̏�ԕύX
//*******************
typedef enum
{
	CAMERASTATE_NORMAL=0,//�ʏ���
	CAMERASTATE_PLAYER,//�v���C���[�Ǐ]���
	CAMERASTATE_MAX
}CAMERASTATE;

//*******************
//�J�����̍\����
//*******************
typedef struct
{
	D3DXVECTOR3 posV;//���_
	D3DXVECTOR3 posR;//�����_
	D3DXVECTOR3 posVDest;//�ړI�̎��_
	D3DXVECTOR3 posRDest;//�ړI�̒����_
	D3DXVECTOR3 vecU;//������x�N�g��
	D3DXMATRIX mtxProjection;//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;//�r���[�}�g���b�N�X
	D3DXVECTOR3 rot;//����
	D3DXVECTOR3 rotDest;//����
	float fDistance;//���_���璍���_�܂ł̋���
	CAMERASTATE state;//�J�����̏��
	bool behind;
}CAMERA;

//*********************
//�v���g�^�C�v�錾
//*********************
void InitCamera(void);//�J�����̏���������
void UninitCamera(void);//�J�����̏I������
void UpdateCamera(void);//�J�����̍X�V����
void SetCamera(void);//�J�����̐ݒ菈��
CAMERA* GetCamera(void);//�J�����̎擾����
#endif
