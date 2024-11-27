//=================================
//
// ���b�V���E�H�[�� [meshwall.h]
// Author:YOSHIDA YUUTO
//
//=================================

#ifndef _MESHWALL_H_
#define _MESHWALL_H_

//****************************
//�C���N���[�h�t�@�C��
//****************************
#include"main.h"

//****************************
//�}�N����`
//****************************
#define MAX_WALL_WIDTH (150.0f) //����
#define MAX_WALL_HEIGHT (150.0f) //����

#define WALL_XVTX (8) //X�̒l
#define WALL_ZVTX (8) //y�̒l

#define WALL_VERTEX ((WALL_XVTX + 1) * (WALL_ZVTX + 1)) //���_��
#define WALL_INDEX (WALL_POLYGON + 2)  //�C���f�b�N�X
#define WALL_POLYGON (((WALL_XVTX * WALL_ZVTX) * 2)) + (4 * (WALL_ZVTX - 1)) //�|���S����
//****************************
//���b�V���E�H�[���̍\����
//****************************
typedef struct
{
	D3DXVECTOR3 pos;//���b�V���E�H�[���̈ʒu
	D3DXVECTOR3 rot;//���b�V���E�H�[���̌���
	D3DXMATRIX mtxWorldMeshWall;//���b�V���E�H�[���̃��[���h�}�g���b�N�X
}MESHWALL;

//****************************
//�v���g�^�C�v�錾
//****************************
void InitMeshWall(void);//���b�V���E�H�[���̏���������
void UninitMeshWall(void);//���b�V���E�H�[���̏I������
void UpdateMeshWall(void);//���b�V���E�H�[���̍X�V����
void DrawMeshWall(void);//���b�V���E�H�[���̕`�揈��
#endif
