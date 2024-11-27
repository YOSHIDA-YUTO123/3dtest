//============================
//
// ���C��[main.cpp]
// Author:YOSHIDA YUUTO
//
//============================

//****************************
//�C���N���[�h�t�@�C��
//****************************
#include "main.h"
#include "polygon.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "input.h"
#include<stdio.h>
#include "player.h"
#include "shadow.h"
#include "wall.h"
#include "bullet.h"
#include "effect.h"
#include "explosion.h"
#include "particle.h"
#include "meshfield.h"
#include "meshwall.h"
#include "sphere.h"
#include "block.h"

//****************************
//�O���[�o���ϐ��錾
//****************************
bool g_isFullscreen = false;            //�E�B���h�E��؂�ւ��邽�߂̃t���O
RECT g_windowRect;                      //�E�B���h�E��؂�ւ��邽�߂̕ϐ�
LPDIRECT3D9 g_pD3D = NULL;//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;//Direct3D�f�o�C�X�ւ̃|�C���^
MODE g_mode = MODE_TITLE;//���݂̃��[�h
LPD3DXFONT g_pFont = NULL;//�t�H���g�ւ̃|�C���^
int g_nCountFPS = 0;//FPS�J�E���^�[

//===================================
//���C���֐�
//===================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);//�������[���[�N���m�p�t���O
	DWORD dwCurrentTime;//���ݎ���
	DWORD dwExecLastTime = timeGetTime();//�Ō�ɏ�����������

	//����\��ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;//����������
	dwExecLastTime = timeGetTime();//���ݎ����ۑ�

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),//WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,        //�E�C���h�E�̃X�^�C��
		WindowProc,        //�E�C���h�E�v���V�[�W��
		0,                 //0�ɂ���(�ʏ�͎g�p���Ȃ�)
		0,                 //0�ɂ���(�ʏ�͎g�p���Ȃ�)
		hInstance,         //�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),//�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),//�N���C�A���g�̈�̐F
		NULL,//���j���[�o�[
		CLASS_NAME,//�E�C���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)//�t�@�C���̃A�C�R��
	};
	HWND hWnd;//�E�C���h�E�̃n���h��

	MSG msg;

	//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�C���h�E�𐶐�
	hWnd = CreateWindowEx(0,//�g���E�B���h�E�X�^�C��
		CLASS_NAME,           //�E�C���h�E�N���X�̖��O
		WINDOW_NAME,          //�E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,  //�E�C���h�E�̃X�^�C��
		CW_USEDEFAULT,        //�E�C���h�E����X���W
		CW_USEDEFAULT,        //�E�C���h�E����Y���W
		(rect.right - rect.left),//�E�C���h�E����x���W��
		(rect.bottom - rect.top),//�E�C���h�E����Y���W����
		NULL,                 //�e�E�C���h�E�̃n���h��
		NULL,                 //���j���[�n���h���܂��̓E�C���h�EID
		hInstance,            //�C���X�^���X�n���h��
		NULL);                 //�E�C���h�E�쐬�f�[�^

		//�E�C���h�E�̕\��
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);//�E�C���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);            //�N���C�A���g�̈���X�V

	DWORD dwFrameCount;//�t���[���J�E���g
	DWORD dwFPSLastTime;//�Ō��FPS���v����������

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//���������������s�����ꍇ
		return -1;
	}
	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windows�̏���
			if (msg.message == WM_QUIT)
			{//WM_QUIT���b�Z�[�W���󂯎�����烋�[�v�𔲂���
				break;
			}
			else
			{
				TranslateMessage(&msg);//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg); //�E�C���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{
			//DirectX�̏���
			//���b�Z�[�W�̐ݒ�
			dwCurrentTime = timeGetTime();//���ݎ���

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				//FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;//FPS���v������������ۑ�
				dwFrameCount = 0;//�t���[���J�E���g���N���A

			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60����1�b�o��
				dwExecLastTime = dwCurrentTime;//�����J�n�̎���(���ݎ���)��ۑ�

				dwFrameCount++;//�t���[���J�E���g�����Z

				//�X�V����
				Update();

				//�`�揈��
				Draw();
			}
			
		}
		
	}
	//�I������
	Uninit();

	//�E�C���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);


	return(int)msg.wParam;
}
//=======================
//�E�C���h�E�v���V�[�W��
//=======================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//HDC hDC;//�f�o�C�X�R���e�L�X�g(GDI�I�u�W�F�N�g)�̃n���h��

	const RECT rect = { 0,0, SCREEN_WIDTH,SCREEN_HEIGHT };//�E�C���h�E�̗̈�

	switch (uMsg)
	{
	case WM_DESTROY: //�E�C���h�E�̔j�����b�Z�[�W
		//WM_QUIT�փ��b�Z�[�W�𑗂�
		ReleaseDInputMouse();	// DirectInput(Mouse)�I�u�W�F�N�g�̊J��
		ReleaseDInput();		// DirectInput�I�u�W�F�N�g�̊J��
		PostQuitMessage(0);
		break;
	case WM_ACTIVATE:	// �A�N�e�B�u���F1�@��A�N�e�B�u���F0
		if (wParam == 0) {
			// ��A�N�e�B�u�ɂȂ����ꍇ
			ReleaseDInputMouse();
		}
		return 0L;
	case WM_SETCURSOR:	// �J�[�\���̐ݒ�
		SetCursor(NULL);
		return TRUE;
	case WM_KEYDOWN: //�L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE://[Esc]�L�[�����ꂽ
			DestroyWindow(hWnd);
			break;
		case VK_F11:
			ToggleFullscreen(hWnd);//F11�Ńt���X�N���[��
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);    //����̏�����Ԃ�
}
//========================
//����������
//========================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{

	D3DDISPLAYMODE d3ddm; //�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp; //�v���[���e�[�V�����p�����[�^

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));//�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;//�Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//�Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//�o�b�N�o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//�f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;//�E�C���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//�C���^�[�o��

	//Direct3D�f�o�C�X�̐����`�揈���ƒ��_�������n�[�h�E�F�A�ōs��
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�f�o�b�N�\���p�t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFont);

	//�L�[�{�[�h�̏���������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	if (FAILED(InitDInput(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	//�W���C�p�b�h�̏���������
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

//*************************
//�֐��̏�����
//*************************
	////�|���S���̏���������
	//InitPolygon();

	//���b�V���t�B�[���h�̏���������
	InitMeshField();

	//���b�V���E�H�[��
	InitMeshWall();

	////���b�V���X�t�B�A�̏���������
	//InitMeshSphere();

	//�J�����̏���������
	InitCamera();

	//���C�g�̏���������
	InitLight();
	
	//�ǂ̏���������
	InitWall();

	//�e�̏���������
	InitShadow();

	//�e�̏���������
	InitBullet();

	//�G�t�F�N�g�̏���������
	InitEffect();

	//�����̏���������
	InitExplosion();

	//�p�[�e�B�N���̏���������
	InitParticle();

	//�u���b�N�̏���������
	InitBlock();

	//�v���C���[�̏���������
	InitPlayer();

//*************************
//�ǂ̐ݒ�
//*************************

	//����
	SetWall(D3DXVECTOR3(-350.0f,50.0f,350.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),1.0f,300.0f,100.0f);

	//migi
	SetWall(D3DXVECTOR3(350.0f, 50.0f, 350.0f),D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), 1.0f, 300.0f, 100.0f);

	//temae
	SetWall(D3DXVECTOR3(350.0f, 50.0f, -350.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 1.0f, 300.0f, 100.0f);

	//hif
	SetWall(D3DXVECTOR3(-350.0f, 50.0f, -350.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), 1.0f, 300.0f, 100.0f);
	

//*************************
	return S_OK;
}
//========================
//�f�o�C�X�̎擾
//========================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
//========================
//�I������
//========================
void Uninit(void)
{
	//�W���C�p�b�h�̏I������
	UninitJoypad();

	//�L�[�{�[�h�̏I������
	UninitKeyboard();

	////�|���S���̏I������
	//UninitPolygon();

	//���b�V���t�B�[���h�̏I������
	UninitMeshField();

	//���b�V���E�H�[���̏I������
	UninitMeshWall();

	////���b�V���X�t�B�A�̏I������
	//UninitMeshSphere();

	//�J�����̏I������
	UninitCamera();

	//���C�g�̏I������
	UninitLight();

	/*UninitModel();*/

	//�ǂ̏I������
	UninitWall();

	//�e�̏I������
	UninitBullet();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�����̏I������
	UninitExplosion();

	//�p�[�e�B�N���̏I������
	UninitParticle();

	//�u���b�N�̏I������
	UninitBlock();

	//�v���C���[�̏I������
	UninitPlayer();

	//�e�̏I������
	UninitShadow();
}
//========================
//�X�V����
//========================
void Update(void)
{
	//�W���C�p�b�h�̍X�V����
	UpdateJoypad();

	//�W���C�p�b�h�̍X�V����
	UpdateKeyboard();

	////�|���S���̍X�V����
	//UpdatePolygon();

	//���b�V���t�B�[���h�̍X�V����
	UpdateMeshField();

	//���b�V���E�H�[���̍X�V����
	UpdateMeshWall();

	////���b�V���X�t�B�A�̍X�V����
	//UpdateMeshSphere();

	//�J�����̍X�V����
	UpdateCamera();

	//���C�g�̍X�V����
	UpdateLight();

	//�e�̍X�V����
	UpdateBullet();

	//�G�t�F�N�g�̍X�V����
	UpdateEffect();

	//�����̍X�V����
	UpdateExplosion();

	//�p�[�e�B�N���̍X�V����
	UpdateParticle();

	//�ǂ̍X�V����
	UpdateWall();

	//�u���b�N�̍X�V����
	UpdateBlock();

	//�v���C���[�̍X�V����
	UpdatePlayer();

	//�e�̍X�V����
	UpdateShadow();

	if (KeyboardTrigger(DIK_F4) == true)
	{
		onWireFrame();
	}
	else if (KeyboardTrigger(DIK_F5) == true)
	{
		offWireFrame();
	}

	/*UpdateModel();*/
}
//========================
//�`�揈��
//========================
void Draw(void)
{
	//��ʃN���A(�o�b�N�o�b�t�@&Z�o�b�t�@�̃N���A)
	g_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ

		//�J�����̐ݒ菈��
		SetCamera();

		//�|���S���̕`�揈��
		DrawPolygon();

		//���b�V���t�B�[���h�̕`�揈��
		DrawMeshField();

		//���b�V���E�H�[���̕`�揈��
		DrawMeshWall();

		////���b�V���X�t�B�A�̕`�揈��
		//DrawMeshSphere();

		//�e�̕`�揈��
		DrawBullet();

		//�v���C���[�̕`�揈��
		DrawPlayer();

		//�u���b�N�̕`�揈��
		DrawBlock();

		//�G�t�F�N�g�̕`�揈��
		DrawEffect();

		//�����̕`�揈��
		DrawExplosion();

		//�p�[�e�B�N���̕`�揈��
		DrawParticle();

		//�ǂ̕`�揈��
		DrawWall();

		//�v���C���[�̉e�̕`�揈��
		DrawShadow();

#ifdef _DEBUG

		//fps�̕\��
		DrawFps();

		//�J������rot�̕\��
		DrawCameraRot();

		//�J�����̏��
		DrawCameraState();
#endif 

		//�`��I��
		g_pD3DDevice->EndScene();
	}
	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//========================
//���[�h�ݒ�
//========================
void SetMode(MODE mode)
{
	////���݂̃��[�h�̏I������
	//switch (g_mode)
	//{
	//case MODE_TITLE:
	//	UninitTitle();
	//	break;
	//case MODE_SELECT:
	//	UninitBackground();
	//	UninitSelect();
	//	break;
	//case MODE_STAGESELECT:
	//	UninitBackground();
	//	UninitStageSelect();
	//	break;
	//case MODE_TUTORIAL://�`���[�g���A�����
	//	UninitTutorial();
	//	break;
	//case MODE_TUTORIAL2://�`���[�g���A�����
	//	UninitTutorial2();
	//	break;
	//case MODE_GAME:
	//	UninitGame();
	//	break;
	//case MODE_GAME2:
	//	UninitGame2();
	//	break;
	//case MODE_RESULT:
	//	UninitMedal();
	//	UninitResult();
	//	break;
	//case MODE_RANKING:
	//	UninitRanking();
	//	break;
	//case MODE_EDIT:
	//	UninitEdit();
	//	break;
	//}

	////�V�����Q�[�����[�h�̏���������
	//switch (mode)
	//{
	//case MODE_TITLE:
	//	InitTitle();
	//	break;
	//case MODE_SELECT:
	//	InitBackground();
	//	InitSelect();
	//	break;
	//case MODE_STAGESELECT:
	//	InitBackground();
	//	InitStageSelect();
	//	break;
	//case MODE_TUTORIAL://�`���[�g���A�����
	//	InitTutorial();
	//	break;
	//case MODE_TUTORIAL2://�`���[�g���A�����
	//	InitTutorial2();
	//	break;
	//case MODE_GAME:
	//	InitGame();
	//	break;
	//case MODE_GAME2:
	//	InitGame2();
	//	break;
	//case MODE_RESULT:
	//	InitMedal();
	//	InitResult();
	//	break;
	//case MODE_RANKING:
	//	InitRanking();
	//	break;
	//case MODE_EDIT:
	//	InitEdit();
	//	break;
	/*}*/
	//g_mode = mode;
}
//========================
//���[�h�̎擾
//========================
MODE GetMode(void)
{
	return g_mode;
}

void DrawFps(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	//������
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}
void DrawCameraRot(void)
{
	CAMERA* pCamera = GetCamera();

	RECT rectRotx = { 0,15,SCREEN_WIDTH,SCREEN_HEIGHT };
	RECT rectRoty = { 180,15,SCREEN_WIDTH,SCREEN_HEIGHT };
	RECT rectRotz = { 360,15,SCREEN_WIDTH,SCREEN_HEIGHT };

	RECT rectPosx = { 0,45,SCREEN_WIDTH,SCREEN_HEIGHT };
	RECT rectPosy = { 180,45,SCREEN_WIDTH,SCREEN_HEIGHT };
	RECT rectPosz = { 360,45,SCREEN_WIDTH,SCREEN_HEIGHT };

	char aStrRotx[256];
	char aStrRoty[256];
	char aStrRotz[256];

	char aStrPosx[256];
	char aStrPosy[256];
	char aStrPosz[256];

	//�����ɑ��
	sprintf(&aStrRotx[0], "�J�����̉�]X:%.2f", pCamera->rot.x);
	sprintf(&aStrRoty[0], "�J�����̉�]Y:%.2f", pCamera->rot.y);
	sprintf(&aStrRotz[0], "�J�����̉�]Z:%.2f", pCamera->rot.z);
	
	//�����ɑ��
	sprintf(&aStrPosx[0], "�J�����̈ʒuX:%.2f", pCamera->posV.x);
	sprintf(&aStrPosy[0], "�J�����̈ʒuY:%.2f", pCamera->posV.y);
	sprintf(&aStrPosz[0], "�J�����̈ʒuZ:%.2f", pCamera->posV.z);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStrRotx[0], -1, &rectRotx, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawText(NULL, &aStrRoty[0], -1, &rectRoty, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawText(NULL, &aStrRotz[0], -1, &rectRotz, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStrPosx[0], -1, &rectPosx, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawText(NULL, &aStrPosy[0], -1, &rectPosy, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawText(NULL, &aStrPosz[0], -1, &rectPosz, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

}
////========================
////�v���C���[�f�o�b�O�\��
////========================
//void DebagDrawPlayer(void)
//{
//	Player* pPlayer = GetPlayer();
//
//	RECT rectPosx = { 0,15,SCREEN_WIDTH,SCREEN_HEIGHT };
//	RECT rectPosy = { 0,30,SCREEN_WIDTH,SCREEN_HEIGHT };
//
//	char aStrPosx[256];
//	char aStrPosy[256];
//
//	//�����ɑ��
//	sprintf(&aStrPosx[0], "PLAYER_POS_X:%.2f\n", pPlayer->pos.x);
//	sprintf(&aStrPosy[0], "PLAYER_POS_Y:%.2f\n", pPlayer->pos.y);
//
//	//�e�L�X�g�̕`��
//	g_pFont->DrawText(NULL, &aStrPosx[0], -1, &rectPosx, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
//	g_pFont->DrawText(NULL, &aStrPosy[0], -1, &rectPosy, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
//}
//
//void DebagDrawMove(void)
//{
//	EDITINFO* pEdit = GetEdit();
//
//	RECT rectMovex = { 0,45,SCREEN_WIDTH,SCREEN_HEIGHT };
//	RECT rectMovey = { 0,60,SCREEN_WIDTH,SCREEN_HEIGHT };
//
//	char aStrMovex[256];
//	char aStrMovey[256];
//
//	//�����ɑ��
//	sprintf(&aStrMovex[0], "BLOCK_MOVE_X:%.2f[M][N]\n",pEdit->move.x);
//	sprintf(&aStrMovey[0], "BLOCK_MOVE_Y:%.2f[H][Y]\n", pEdit->move.y);
//
//	//�e�L�X�g�̕`��
//	g_pFont->DrawText(NULL, &aStrMovex[0], -1, &rectMovex, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
//	g_pFont->DrawText(NULL, &aStrMovey[0], -1, &rectMovey, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
//}
//
//************************************************
// �E�B���h�E���t���X�N���[���ɕς��鏈��
//************************************************
void ToggleFullscreen(HWND hWnd)
{
	// ���݂̃E�B���h�E�X�^�C�����擾
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);
	if (g_isFullscreen)
	{
		// �E�B���h�E���[�h�ɐ؂�ւ�
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// �t���X�N���[�����[�h�ɐ؂�ւ�
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}
	g_isFullscreen = !g_isFullscreen;
}
//========================
//�J�����̏��
//========================
void DrawCameraState(void)
{
	CAMERA* pCamera = GetCamera();

	RECT rectPos = { 0,100,SCREEN_WIDTH,SCREEN_HEIGHT };
	RECT rectPosBe = { 0,150,SCREEN_WIDTH,SCREEN_HEIGHT };

	char aStrPos[256];
	char aStrPosBe[256];

	if (pCamera->state == CAMERASTATE_PLAYER)
	{
		//�����ɑ��
		wsprintf(&aStrPos[0], "�J�����Ǐ]:[ON][F2]");
	}
	else if (pCamera->state == CAMERASTATE_NORMAL)
	{
		//�����ɑ��
		wsprintf(&aStrPos[0], "�J�����Ǐ]:[OFF][F2]");
	}

	if (pCamera->behind == true)
	{
		//�����ɑ��
		wsprintf(&aStrPosBe[0], "�J������荞��:[ON][F3]");
	}
	else if (pCamera->behind == false)
	{
		//�����ɑ��
		wsprintf(&aStrPosBe[0], "�J������荞��:[OFF][F3]");

	}
	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStrPos[0], -1, &rectPos, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawText(NULL, &aStrPosBe[0], -1, &rectPosBe, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

}
void onWireFrame() 
{
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}

void offWireFrame() 
{
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}



