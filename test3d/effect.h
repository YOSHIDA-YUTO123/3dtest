//============================
//
// �G�t�F�N�g[effect.h]
// Author:YOSHIDA YUUTO
//
//============================

#ifndef _EFFECT_H_
#define _EFFECT_H_

//****************************
//�C���N���[�h�t�@�C��
//****************************
#include"main.h"

//****************************
//�G�t�F�N�g��ނ̗񋓌^
//****************************
typedef enum
{
	EFFECTTYPE_PLAYER=0,
	EFFECTTYPE_BULLET,
	EFFECTTYPE_MAX
}EFFECTTYPE;

//****************************
//�G�t�F�N�g�̍\����
//****************************
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXVECTOR3 move;//�ړ���
	D3DXCOLOR col;//�F
	D3DXMATRIX mtxWorld;//���[���h�}�g���b�N�X
	D3DXVECTOR3 fScal;
	float fRadius;
	int nLife;//����
	bool bUse;//�g�p���Ă��邩�ǂ���
	EFFECTTYPE nType;//���
}EFFECT;

//****************************
//�v���g�^�C�v�錾
//****************************
void InitEffect(void);//�G�t�F�N�g�̏���������
void UninitEffect(void);//�G�t�F�N�g�̏I������
void UpdateEffect(void);//�G�t�F�N�g�̍X�V����
void DrawEffect(void);//�G�t�F�N�g�̕`�揈��
void SetEffect(D3DXVECTOR3 pos,D3DXVECTOR3 move, D3DXCOLOR col, int nLife,D3DXVECTOR3 fScal);//�G�t�F�N�g�̐ݒ菈��
#endif
