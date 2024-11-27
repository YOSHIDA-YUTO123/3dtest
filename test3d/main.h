//============================
//
// ���C��[main.h]
// Author:YOSHIDA YUUTO
//
//============================
#ifndef _MAIN_H_
#define _MAIN_H_

//****************************
//�C���N���[�h�t�@�C��
//****************************
#include<windows.h>
#include"d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)//�r���h���̌x���Ώ��}�N��
#include "dinput.h"
#include"Xinput.h"
#include"xaudio2.h"

//*****************************
//���C�u�����̃����N
//*****************************
#pragma comment(lib,"d3d9.lib")//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")//DirectX�R���|�l�[�V����(���i)�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")//�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")//���͏����ɕK�v
#pragma comment(lib,"xinput.lib")//�W���C�p�b�h�����ɕK�v

//�}�N����`
#define CLASS_NAME "WindowClass" //�E�C���h�E�N���X�̖��O
#define WINDOW_NAME "3DTEST" //�E�C���h�E�̖��O(�L���v�V�����ɕ\��)
#define SCREEN_WIDTH (1280) //�E�C���h�E�̕�
#define SCREEN_HEIGHT (720) //�E�C���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)//���W�A�@���A�J���[�A�e�N�X�`��

//*******************
//2D�\����
//*******************
typedef struct
{
	D3DXVECTOR3 Pos; //���_���W
	float rhw;       //���W�ԊҌW��(1.0f�Ŏw��)
	D3DCOLOR col;    //���_�J���[
	D3DXVECTOR2 tex;//�e�N�X�`�����W
}VERTEX_2D;

//*******************
//3D�\����
//*******************
typedef struct
{
	D3DXVECTOR3 Pos; //���_���W
	D3DXVECTOR3 nor; //�@���x�N�g��
	D3DCOLOR col;    //���_�J���[
	D3DXVECTOR2 tex;//�e�N�X�`�����W
	D3DXVECTOR3 rot;
}VERTEX_3D;

//********************
//���[�h
//********************
typedef enum
{
	MODE_TITLE = 0, //�^�C�g�����
	MODE_SELECT,//	�I�����
	MODE_STAGESELECT,//	�I�����
	MODE_TUTORIAL,//�`���[�g���A�����
	MODE_TUTORIAL2,//�`���[�g���A�����
	MODE_GAME,//�Q�[�����
	MODE_GAME2,//�Q�[��2���
	MODE_RESULT,//���U���g���
	MODE_RANKING,//�����L���O���
	MODE_EDIT,//�c�[��
	MODE_MAX
}MODE;

//********************
//�p�b�h�̃{�^��
//********************
typedef enum
{
	JOYKEY_UP=0,//�\���L�[��
	JOYKEY_DOWN,//�\���L�[��
	JOYKEY_LEFT,//�\���L�[��
	JOYKEY_RIGHT,//�\���L�[�E
	JOYKEY_START,//START
	JOYKEY_BAKC,//BACK
	JOYKEY_LEFT_L3,
	JOYKEY_RIGHT_R3,
	JOYKEY_LEFT_LT,//���g���K�[
	JOYKEY_RIGHT_RT,//�E�g���K�[
	JOYKEY_LB,
	JOYKEY_RB,
	JOYKEY_A,//A�{�^��
	JOYKEY_B,//B�{�^��
	JOYKEY_X,//X�{�^��
	JOYKEY_Y,//Y�{�^��
	JOYKEY_MAX

}JOYKEY;

//**********************************
//�v���g�^�C�v�錾
//**********************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//���C���֐�
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);//����������
void Uninit(void);//�I������
void Update(void);//�X�V����
void Draw(void);//�`�揈��
void DrawFps(void);//fps�\���p�f�o�b�N�t�H���g
void DrawCameraRot(void);//�J������]�\���p�f�o�b�N�t�H���g
void DrawCameraState(void);//�J������ԕ\���p�f�o�b�N�t�H���g
LPDIRECT3DDEVICE9 GetDevice(void);//�f�o�C�X�̎擾
void SetMode(MODE mode);//���[�h�ݒ�
MODE GetMode(void);//���[�h�擾
void ToggleFullscreen(HWND hWnd);                                                   // �E�B���h�E���t���X�N���[���ɂ�����@
void onWireFrame();
void offWireFrame();


#endif
