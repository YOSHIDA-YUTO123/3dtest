//============================
//
// ���C�g[light.cpp]
// Author:YOSHIDA YUUTO
//
//============================

//****************************
//�C���N���[�h�t�@�C��
//****************************
#include "light.h"

//****************************
//�}�N����`
//****************************
#define MAX_LIGHT (4)

//****************************
//�O���[�o���ϐ��錾
//****************************
D3DLIGHT9 g_Light[MAX_LIGHT];//���C�g���
D3DXVECTOR3 g_vecDir[MAX_LIGHT];//���C�g�̕����x�N�g��

//============================
//���C�g�̏���������
//============================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();

	//���C�g���N���A����
	ZeroMemory(&g_Light, sizeof(g_Light));

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		g_vecDir[nCntLight];

		//���C�g�̏���ݒ�
		g_Light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		//���C�g�̊g�U����ݒ�
		g_Light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//���C�g�̕�����ݒ�
	g_vecDir[0] = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
	g_vecDir[1] = D3DXVECTOR3(-0.5f, -0.8f, 0.0f);
	g_vecDir[2] = D3DXVECTOR3(0.5f, -0.8f, -0.8f);
	g_vecDir[3] = D3DXVECTOR3(0.5f, -0.8f, -0.8f);

	for (int nCntLight1 = 0; nCntLight1 < MAX_LIGHT; nCntLight1++)
	{
		//����������(�傫���ʒu�̃x�N�g���ɂ���)
		D3DXVec3Normalize(&g_vecDir[nCntLight1], &g_vecDir[nCntLight1]);

		g_Light[nCntLight1].Direction = g_vecDir[nCntLight1];

		//���C�g��ݒ肷��
		pDevice->SetLight(nCntLight1, &g_Light[nCntLight1]);

		//���C�g��L���ɂ���(ON,OFF)
		pDevice->LightEnable(nCntLight1, TRUE);
	}
}
//============================
//���C�g�̏I������
//============================
void UninitLight(void)
{

}
//============================
//���C�g�̍X�V����
//============================
void UpdateLight(void)
{

}
