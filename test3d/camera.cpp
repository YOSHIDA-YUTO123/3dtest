//============================
//
// �J���� [camera.cpp]
// Author:YOSHIDA YUUTO
//
//============================

//***********************
//�C���N���[�h�t�@�C��
//***********************

#include "camera.h"
#include"input.h"
#include"player.h"

//****************************
//�}�N����`
//****************************

#define MAX_MOVE (0.6f) // �v���C���[�ړ���

//****************************
//�O���[�o���ϐ�
//****************************
CAMERA g_Camera;//�J�������

//=============================
//�J�����̏���������
//=============================
void InitCamera(void)
{
	PLAYER* pPlayer = GetPlayer();

//********************************
//���_�A�����_�A�������ݒ肷��
//********************************

	g_Camera.posV = D3DXVECTOR3(0.0f, 150.0f, -300.0f);
	//g_Camera.posVDest = D3DXVECTOR3(0.0f, 150.0f, -300.0f);
	g_Camera.state = CAMERASTATE_PLAYER;
	g_Camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_Camera.rot = D3DXVECTOR3(D3DX_PI*0.65f, 0.0f, 0.0f);
	g_Camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Camera.behind = false;
	g_Camera.fDistance = sqrtf(((g_Camera.posR.x - g_Camera.posV.x) * (g_Camera.posR.x - g_Camera.posV.x)) + ((g_Camera.posR.z - g_Camera.posV.z) * (g_Camera.posR.z - g_Camera.posV.z)));
}

//=============================
//�J�����̏I������
//=============================
void UninitCamera(void)
{
	//�Ȃ�
}
//=============================
//�J�����̍X�V����
//=============================
void UpdateCamera(void)
{
	PLAYER* pPlayer = GetPlayer();

	switch (g_Camera.state)
	{
	case CAMERASTATE_NORMAL:
		break;
	case CAMERASTATE_PLAYER:
		break;
	}
//*************************************************************************************************
//�����_�̐���
//*************************************************************************************************
	if (GetKeyboardPress(DIK_Q) == true)
	{
		g_Camera.rot.y -= 0.1f;

		if (g_Camera.rot.y < -D3DX_PI)
		{
			g_Camera.rot.y += D3DX_PI * 2.0f;
		}

		g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.rot.y) * g_Camera.fDistance;
		g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.rot.y) * g_Camera.fDistance;
	}
	else if (GetKeyboardPress(DIK_E) == true)
	{
		g_Camera.rot.y += 0.1f;

		if (g_Camera.rot.y > D3DX_PI)
		{
			g_Camera.rot.y += -D3DX_PI * 2.0f;
		}

		g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.rot.y) * g_Camera.fDistance;
		g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.rot.y) * g_Camera.fDistance;
	}
	else if (GetKeyboardPress(DIK_I) == true)
	{
		g_Camera.rot.x -= 0.01f;

		if (g_Camera.rot.x < -D3DX_PI)
		{
			g_Camera.rot.x += D3DX_PI * 2;
		}

		g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.rot.x) * sinf(g_Camera.rot.y) * g_Camera.fDistance;
		g_Camera.posR.y = g_Camera.posV.y + cosf(g_Camera.rot.x) * g_Camera.fDistance;
		g_Camera.posR.z = g_Camera.posV.z + sinf(g_Camera.rot.x) * cosf(g_Camera.rot.y) * g_Camera.fDistance;
	}
	else if (GetKeyboardPress(DIK_K) == true)
	{
		g_Camera.rot.x += 0.01f;

		if (g_Camera.rot.x > D3DX_PI)
		{
			g_Camera.rot.x += -D3DX_PI * 2;
		}

		g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.rot.x) * sinf(g_Camera.rot.y) * g_Camera.fDistance;
		g_Camera.posR.y = g_Camera.posV.y + cosf(g_Camera.rot.x) * g_Camera.fDistance;
		g_Camera.posR.z = g_Camera.posV.z + sinf(g_Camera.rot.x) * cosf(g_Camera.rot.y) * g_Camera.fDistance;
	}

//**********************************************************************************
//���_�̐���
//**********************************************************************************
	if (GetKeyboardPress(DIK_Z) == true)
	{
		g_Camera.rot.y += 0.05f;

		//if (g_Camera.rot.y >= D3DX_PI)
		//{
		//	g_Camera.rot.y = -D3DX_PI;
		//}

		if (g_Camera.rot.y > D3DX_PI)
		{
			g_Camera.rot.y += -D3DX_PI * 2.0f;
		}

		g_Camera.posV.x = g_Camera.posR.x - sinf(g_Camera.rot.y) * g_Camera.fDistance;
		g_Camera.posV.z = g_Camera.posR.z - cosf(g_Camera.rot.y) * g_Camera.fDistance;
	}
	else if (GetKeyboardPress(DIK_C) == true)
	{
		g_Camera.rot.y -= 0.05f;

		//if (g_Camera.rot.y <= -D3DX_PI)
		//{
		//	g_Camera.rot.y = D3DX_PI;
		//}

		if (g_Camera.rot.y < -D3DX_PI)
		{
			g_Camera.rot.y += D3DX_PI * 2.0f;
		}

		g_Camera.posV.x = g_Camera.posR.x - sinf(g_Camera.rot.y) * g_Camera.fDistance;
		g_Camera.posV.z = g_Camera.posR.z - cosf(g_Camera.rot.y) * g_Camera.fDistance;
	}
	else if (GetKeyboardPress(DIK_U) == true)
	{

		if (g_Camera.rot.x < -D3DX_PI)
		{
			g_Camera.rot.x += D3DX_PI * 2;
		}

		//if (g_Camera.rot.x > D3DX_PI * 0.55f)
		//{
			g_Camera.rot.x -= 0.01f;

			g_Camera.posV.x = g_Camera.posR.x - sinf(g_Camera.rot.x) * sinf(g_Camera.rot.y) * g_Camera.fDistance;
			g_Camera.posV.y = g_Camera.posR.y - cosf(g_Camera.rot.x) * g_Camera.fDistance;
			g_Camera.posV.z = g_Camera.posR.z - sinf(g_Camera.rot.x) * cosf(g_Camera.rot.y) * g_Camera.fDistance;
		//}
	}
	else if (GetKeyboardPress(DIK_J) == true)
	{

		if (g_Camera.rot.x > D3DX_PI)
		{
			g_Camera.rot.x += -D3DX_PI * 2;
		}

		if (g_Camera.rot.x < 3.10)
		{
			g_Camera.rot.x += 0.01f;

			g_Camera.posV.x = g_Camera.posR.x - sinf(g_Camera.rot.x) * sinf(g_Camera.rot.y) * g_Camera.fDistance;
			g_Camera.posV.y = g_Camera.posR.y - cosf(g_Camera.rot.x) * g_Camera.fDistance;
			g_Camera.posV.z = g_Camera.posR.z - sinf(g_Camera.rot.x) * cosf(g_Camera.rot.y) * g_Camera.fDistance;
		}
	}
//************************************************************************************
//�J�����̈ړ�
//*************************************************************************************
	if (GetKeyboardPress(DIK_UP) == true)
	{
		g_Camera.posV.x += sinf(g_Camera.rot.y) * 20;
		g_Camera.posV.z += cosf(g_Camera.rot.y) * 20;

		g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.rot.y) * g_Camera.fDistance;
		g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.rot.y) * g_Camera.fDistance;
	}
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_Camera.posV.x -= sinf(g_Camera.rot.y) * 20;
		g_Camera.posV.z -= cosf(g_Camera.rot.y) * 20;

		g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.rot.y) * g_Camera.fDistance;
		g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.rot.y) * g_Camera.fDistance;
	}

	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		//g_Camera.rot.x -= 0.1f;

		g_Camera.posV.z += sinf(g_Camera.rot.y) * 20;
		g_Camera.posV.x -= cosf(g_Camera.rot.y) * 20;

		g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.rot.y) * g_Camera.fDistance;
		g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.rot.y) * g_Camera.fDistance;
	}

	else if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_Camera.posV.z -= sinf(g_Camera.rot.y) * 20;
		g_Camera.posV.x += cosf(g_Camera.rot.y) * 20;

		g_Camera.posR.x = g_Camera.posV.x + sinf(g_Camera.rot.y) * g_Camera.fDistance;
		g_Camera.posR.z = g_Camera.posV.z + cosf(g_Camera.rot.y) * g_Camera.fDistance;
	}
//**************************************************************************************
//�v���C���[�Ǐ]
//**************************************************************************************

	if (KeyboardTrigger(DIK_F3) == true&&g_Camera.behind == false)
	{
		g_Camera.behind = true;
	}
	else if (KeyboardTrigger(DIK_F3) == true && g_Camera.behind == true)
	{
		g_Camera.behind = false;
	}

	if (g_Camera.behind == true)
	{
		g_Camera.rotDest.y = D3DX_PI;

		if (g_Camera.rot.y > D3DX_PI)
		{
			g_Camera.rot.y += -D3DX_PI * 2.0f;
		}

		g_Camera.rot.y += (g_Camera.rotDest.y - g_Camera.rot.y) * 0.01f;

		g_Camera.posVDest.x = g_Camera.posR.x - sinf(g_Camera.rotDest.y + g_Camera.rot.y) * g_Camera.fDistance;
		g_Camera.posVDest.z = g_Camera.posR.z - cosf(g_Camera.rotDest.y + g_Camera.rot.y) * g_Camera.fDistance;

		g_Camera.posVDest.x += (g_Camera.posVDest.x - g_Camera.posVDest.x) * 0.01f;
		g_Camera.posVDest.z += (g_Camera.posVDest.z - g_Camera.posVDest.z) * 0.01f;
	}

	if (KeyboardTrigger(DIK_F2) == true && g_Camera.state == CAMERASTATE_NORMAL)
	{
		g_Camera.state = CAMERASTATE_PLAYER;
	}
	else if (KeyboardTrigger(DIK_F2) == true && g_Camera.state == CAMERASTATE_PLAYER)
	{
		g_Camera.state = CAMERASTATE_NORMAL;
	}


	if (g_Camera.state == CAMERASTATE_PLAYER)
	{
		g_Camera.posRDest.x = pPlayer->pos.x - sinf(g_Camera.rot.y) * PLAYER_MOVE;
		g_Camera.posRDest.y = pPlayer->pos.y - sinf(g_Camera.rot.y) * PLAYER_MOVE;
		g_Camera.posRDest.z = pPlayer->pos.z - cosf(g_Camera.rot.y) * PLAYER_MOVE;

		g_Camera.posVDest.x = pPlayer->pos.x - sinf(g_Camera.rot.y) * g_Camera.fDistance;
		g_Camera.posVDest.y = pPlayer->pos.y - sinf(g_Camera.rot.y) * g_Camera.fDistance;
		g_Camera.posVDest.z = pPlayer->pos.z - cosf(g_Camera.rot.y) * g_Camera.fDistance;


		g_Camera.posR.x += (g_Camera.posRDest.x - g_Camera.posR.x) * 0.1f;
		g_Camera.posR.y += (g_Camera.posRDest.y - g_Camera.posR.y) * 0.1f;
		g_Camera.posR.z += (g_Camera.posRDest.z - g_Camera.posR.z) * 0.1f;

		g_Camera.posV.x += (g_Camera.posVDest.x - g_Camera.posV.x) * 0.1f;
		//g_Camera.posV.y += (g_Camera.posVDest.y - g_Camera.posV.y) * 0.1f;
		g_Camera.posV.z += (g_Camera.posVDest.z - g_Camera.posV.z) * 0.1f;
	}
}
//=============================
//�J�����̐ݒ菈��
//=============================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;//�f�o�C�X�ւ̃|�C���^

	pDevice = GetDevice();

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxView);

	D3DXMatrixLookAtLH(&g_Camera.mtxView,
		&g_Camera.posV,
		&g_Camera.posR,
		&g_Camera.vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_Camera.mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Camera.mtxProjection);

	D3DXMatrixPerspectiveFovLH(&g_Camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_Camera.mtxProjection);

}
//=============================
//�J�����̎擾����
//=============================
CAMERA* GetCamera(void)
{
	return &g_Camera;
}
