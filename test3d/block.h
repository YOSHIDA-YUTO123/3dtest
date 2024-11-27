//============================
//
// �u���b�N[block.h]
// Author:YOSHIDA YUUTO
//
//============================

#ifndef _BLOCK_H_
#define _BLOCK_H_

//***************************
//�C���N���[�h�t�@�C��
//***************************
#include"main.h"
#include"player.h"

//***************************
//�u���b�N�̍\����
//***************************
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 rot;//����
	D3DXVECTOR3 Scal;//�傫��
	D3DXMATRIX mtxWorldBlock;//���[���h�}�g���b�N�X
	D3DXVECTOR3 vtxMin, vtxMax;
	D3DXVECTOR3 Size;
}BLOCK;

//***************************
//�v���g�^�C�v�錾
//***************************
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
bool CollisionBlock(void);
#endif
