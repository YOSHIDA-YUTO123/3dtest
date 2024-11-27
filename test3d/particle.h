//============================
//
// �p�[�e�B�N��[particle.h]
// Author:YOSHIDA YUUTO
//
//============================

#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//****************************
//�C���N���[�h�t�@�C��
//****************************
#include"main.h"
#include"shadow.h"

//****************************
//�p�[�e�B�N����ނ̗񋓌^
//****************************
typedef enum
{
	PARTICLETYPE_NORMAL = 0,
	PARTICLETYPE_MAX
}PARTICLETYPE;

//****************************
//�p�[�e�B�N���̍\����
//****************************
typedef struct
{
	D3DXVECTOR3 pos;//�ʒu
	D3DXCOLOR col;//�F
	int nLife;//����
	int nType;//���
	bool bUse;//�g�p���Ă��邩�ǂ���
}PARTICLE;

//****************************
//�v���g�^�C�v�錾
//****************************
void InitParticle(void);//�p�[�e�B�N���̏���������
void UninitParticle(void);//�p�[�e�B�N���̏I������
void UpdateParticle(void);//�p�[�e�B�N���̍X�V����
void DrawParticle(void);//�p�[�e�B�N���̕`�揈��
void SetParticle(D3DXVECTOR3 pos,int nLife, D3DXCOLOR col);//�p�[�e�B�N���̐ݒ菈��
#endif
