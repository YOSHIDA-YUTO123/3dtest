//============================
//
//�v���C���[
//Author:YOSHIDA YUUTO
//
//
//============================

#ifndef _PLAYER_H_
#define _PLAYER_H_

//**************************
//�C���N���[�h�t�@�C��
//**************************
#include"main.h"

//**************************
//�}�N����`
//**************************
#define PLAYER_MOVE (1.0f)
#define WIDTH (100.0f) //�ǂ̉���
#define HEIGHT (100.0f) //�ǂ̍���

//**************************
//�v���C���[�\����
//**************************
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 posOld;//�O��̈ʒu
	D3DXVECTOR3 Size;//�傫��
	D3DXVECTOR3 rot;//����
	D3DXVECTOR3 rotDestPlayer;//�ړI�̊p�x
	D3DXVECTOR3 move;//�ړ���
	D3DXVECTOR3	vtxMinPlayer;
	D3DXVECTOR3	vtxMaxPlayer;
	D3DXMATRIX mtxWorldPlayer;//���[���h�}�g���b�N�X
	int nIdxShadow;
	bool bJump;
	bool bDisp;
}PLAYER;

//**************************
//�v���g�^�C�v�錾
//**************************
void InitPlayer(void);//�v���C���[�̏���������
void UninitPlayer(void);//�v���C���[�̏I������
void UpdatePlayer(void);//�v���C���[�̍X�V����
void DrawPlayer(void);//�v���C���[�̕`�揈��
PLAYER* GetPlayer(void);//�v���C���[�̎擾����

#endif
