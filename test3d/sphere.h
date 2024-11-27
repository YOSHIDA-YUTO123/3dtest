//=================================
//
// ���b�V���X�t�B�A [meshsphere.h]
// Author:YOSHIDA YUUTO
//
//=================================

#ifndef _SPHERE_H_
#define _SPHERE_H_

//****************************
//�C���N���[�h�t�@�C��
//****************************
#include"main.h"

//****************************
//�}�N����`
//****************************
#define MAX_SPHERE_WIDTH (350.0f) //����
#define MAX_SPHERE_HEIGHT (350.0f) //����

#define SPHERE_XVTX (2) //X�̒l
#define SPHERE_ZVTX (2) //y�̒l

#define SPHERE_VERTEX ((SPHERE_XVTX + 1) * (SPHERE_ZVTX +1) + 1) //���_��
#define SPHERE_INDEX (SPHERE_POLYGON + 2)  //�C���f�b�N�X
#define SPHERE_POLYGON (((SPHERE_XVTX * SPHERE_ZVTX) * 2)) + (4 * (SPHERE_ZVTX - 1)) //�|���S����

//****************************
//���b�V���X�t�B�A�̍\����
//****************************
typedef struct
{
	D3DXVECTOR3 pos;//���b�V���X�t�B�A�̈ʒu
	D3DXVECTOR3 rot;//���b�V���X�t�B�A�̌���
	D3DXMATRIX mtxWorldMeshSphere;//���b�V���X�t�B�A�̃��[���h�}�g���b�N�X
}MESHSPHERE;

//****************************
//�v���g�^�C�v�錾
//****************************
void InitMeshSphere(void);//���b�V���X�t�B�A�̏���������
void UninitMeshSphere(void);//���b�V���X�t�B�A�̏I������
void UpdateMeshSphere(void);//���b�V���X�t�B�A�̍X�V����
void DrawMeshSphere(void);//���b�V���X�t�B�A�̕`�揈��
#endif
