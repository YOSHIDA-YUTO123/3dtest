//============================
//
// ��[wall.h]
// Author:YOSHIDA YUUTO
//
//============================

#ifndef _WALL_H_
#define _WALL_H_

//****************************
//�C���N���[�h�t�@�C��
//****************************
#include"main.h"

//****************************
//�ǂ̍\����
//****************************
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	float fA;
	float fDepth;
	float fWidth;
	float fHeight;
	D3DXVECTOR3 fScal;
	bool bUse;
	D3DXVECTOR3 vecLine;
	D3DXVECTOR3 vecPos;
	D3DXMATRIX rotmtx;
	D3DXMATRIX posmtx;
}WALL;

//****************************
//�v���g�^�C�v�錾
//****************************
void InitWall(void);//�ǂ̏���������
void UninitWall(void);//�ǂ̏I������
void UpdateWall(void);//�ǂ̍X�V����
void DrawWall(void);//�ǂ̕`�揈��
//void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 fScal,float fA);//�ǂ̐ݒ菈��
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float fA,float fWidth,float fHeight);//�ǂ̐ݒ菈��
void CollisionWall(void);
#endif