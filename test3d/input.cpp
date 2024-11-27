//============================
//
// �L�[�{�[�h[input.cpp]
// Author:YOSHIDA YUUTO
//
//============================

//***********************
//�C���N���[�h�t�@�C��
//***********************
#include"input.h"

//***********************
//�}�N����`
//***********************
#define NUM_KEY_MAX (256)//�L�[�̍ő吔

//***********************
//�O���[�o���ϐ�		 
//***********************
LPDIRECTINPUT8 g_pInput=NULL;//DirectInput�I�u�W�F�N�g�ւ̂ۂ���
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;//���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX];//�L�[�{�[�h�̃v���X���
BYTE g_aOldState[NUM_KEY_MAX];
XINPUT_STATE g_joykeyState;//�W���C�p�b�h�̃v���X���
XINPUT_STATE g_Oldjoykeystate;
XINPUT_STATE g_joykeyStateTrigger;
XINPUT_STATE g_joykeyStateRelease;
LPDIRECTINPUTDEVICE8 g_pDIMouse = NULL;	// �}�E�X�f�o�C�X
LPDIRECTINPUT8 g_pDInput = NULL;	// DirectInput�I�u�W�F�N�g
DIMOUSESTATE g_zdiMouseState;			// �}�E�X���

//=====================
//�L�[�{�[�h�̓��͏���
//=====================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//�������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();

	return S_OK;
}
//=====================
//�L�[�{�[�h�̏I������
//=====================
void UninitKeyboard(void)
{
	//���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();//�L�[�{�[�h�ւ̃A�N�Z�X�������
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̍U��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//=====================
//�L�[�{�[�h�̍X�V����
//=====================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];//�L�[�{�[�h�̓��͏���
	int nCntKey;

	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		g_aOldState[nCntKey] = g_aKeyState[nCntKey];//�ЂƂO�̃L�[�{�[�h�v���X����ۑ�
	}

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyState[nCntKey] = aKeyState[nCntKey];//�L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}
//===========================
//�L�[�{�[�h�̃v���X���擾
//===========================
bool GetKeyboardPress(int Key)
{
	return (g_aKeyState[Key] & 0x80) ? true : false;
}
//===========================
//�L�[�{�[�h�̃g���K�[���擾
//===========================
bool KeyboardTrigger(int nKey)
{
	bool Trigger = false;
	if (g_aKeyState[nKey] & 0x80 && !(g_aOldState[nKey] & 0x80))
	{
		Trigger=true;
	}
	return Trigger;
}
//===========================
//�L�[�{�[�h�̃����[�X���擾
//===========================
bool KeyboardRelease(int nKey)
{
	bool Trigger = false;
	if (g_aOldState[nKey] & 0x80 && !(g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
bool KeyboardRepeat(int nKey)
{
	bool Trigger = true;
	if (g_aOldState[nKey] & 0x80 && (g_aKeyState[nKey] & 0x80))
	{
		Trigger = true;
	}
	return Trigger;
}
//bool JoyKeyRepeat(JOYKEY key)
//{
//	bool JoyStick = true;
//	if (g_Oldjoykeystate.Gamepad.wButtons & (0x01 << key))
//	{
//		JoyStick = true;
//	}
//	return JoyStick;
//}

//=========================
//�W���C�p�b�h�̏���������
//=========================
HRESULT InitJoypad(void)
{
	//�����̃N���A
	memset(&g_joykeyState, 0, sizeof(XINPUT_STATE));
	
	//memset(&g_Oldjoykeystate, 0, sizeof(XINPUT_STATE));

	//xinput�̃X�e�[�g��L���ɂ���
	XInputEnable(true);

	return S_OK;
}
//=======================
//�W���C�p�b�h�̏I������
//=======================
void UninitJoypad(void)
{
	//XInput�̃X�e�[�g�𖳌��ɂ���
	XInputEnable(false);
}

//=======================
//�W���C�p�b�h�̍X�V����
//=======================
void UpdateJoypad(void)
{
	XINPUT_STATE joykeyState;//�W���C�p�b�h�̏���������
	
	//�W���C�p�b�h�̏�Ԏ擾
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		WORD Button = joykeyState.Gamepad.wButtons;
		WORD OldButton = g_joykeyState.Gamepad.wButtons;

		g_joykeyStateTrigger.Gamepad.wButtons = Button & ~OldButton;
		g_joykeyStateRelease.Gamepad.wButtons = OldButton & ~Button;
		g_joykeyState = joykeyState;//�W���C�p�b�h�̓��͏��
	}
}
//===============================
//�W���C�p�b�h�̃v���X�����擾
//===============================
bool GetJoypadPress(JOYKEY key)
{
	return (g_joykeyState.Gamepad.wButtons & (0x01 << key))?true:false;
}
bool GetJoyPadTrigger(JOYKEY key)
{
	return (g_joykeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
}
bool GetJoyPadRelease(JOYKEY key)
{
	return (g_joykeyStateRelease.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

////===========================
////�W���C�p�b�h�̃g���K�[����
////===========================
//bool JoyPadTrigger(JOYKEY key)
//{
//	bool Trigger = false;
//	if (g_joykeyState.Gamepad.wButtons == (0x01 << key))
//	{
//		if (g_joykeyState.Gamepad.wButtons != g_Oldjoykeystate.Gamepad.wButtons)
//		{
//			Trigger = true;
//		}
//	}
//	return Trigger;
//}
//======
//L2,R2
//======
bool GetJoyTrigger(JOYKEY key)
{
	if (key == JOYKEY_LEFT_LT)
	{
		return  (g_joykeyState.Gamepad.bLeftTrigger) ? true : false;
	}
	else if (key == JOYKEY_RIGHT_RT)
	{
		return (g_joykeyState.Gamepad.bRightTrigger) ? true : false;
	}
}
bool GetJoyTriggerTrigger(JOYKEY key)//�������Ƃ�
{
	bool Trigger = false;
	if (key == JOYKEY_LEFT_LT)
	{
		if ((g_joykeyState.Gamepad.bLeftTrigger > 0) && !(g_Oldjoykeystate.Gamepad.bLeftTrigger > 0))
		{
			Trigger = true;
		}
	}
	else if (JOYKEY_RIGHT_RT)
	{
		if ((g_joykeyState.Gamepad.bRightTrigger > 0) && !(g_Oldjoykeystate.Gamepad.bRightTrigger > 0))
		{
			Trigger = true;
		}
	}
	return Trigger;
}
bool GetJoyTriggerRelease(JOYKEY key)//�������Ƃ�
{
	bool JoyStick = false;

	if (key == JOYKEY_LEFT_LT)
	{
		if ((g_joykeyState.Gamepad.bLeftTrigger > 0) && !(g_joykeyState.Gamepad.bLeftTrigger > 0))
		{
			JoyStick = true;
		}
	}
	else if (key == JOYKEY_RIGHT_RT)
	{
		if ((g_joykeyState.Gamepad.bRightTrigger > 0) && !(g_joykeyState.Gamepad.bRightTrigger > 0))
		{
			JoyStick = true;
		}
	}
	return JoyStick;
}
//===============
//�X�e�B�b�N����
//===============
bool GetJoyStick()
{
	bool joykey = false;
	//�^�񒆂���Ȃ�������
	if (g_joykeyState.Gamepad.sThumbLX >= 100 ||
		g_joykeyState.Gamepad.sThumbLX <= -100 ||
		g_joykeyState.Gamepad.sThumbLY >= 100 ||
		g_joykeyState.Gamepad.sThumbLY <= -100)
	{
		joykey = true;
	}
	return joykey;
}
//=====================
//�X�e�B�b�N���̎擾
//=====================
XINPUT_STATE* GetJoySticAngle(void)
{
	return &g_joykeyState;
}
bool InitDInput(HINSTANCE hInstApp, HWND hWnd)
{
	HRESULT ret = DirectInput8Create(hInstApp, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pDInput, NULL);
	if (FAILED(ret)) {
		return false;	// �쐬�Ɏ��s
	}
	return true;
}
bool ReleaseDInput(void)
{
	// DirectInput�̃f�o�C�X���J��
	if (g_pDInput) 
{
		g_pDInput->Release();
		g_pDInput = NULL;
	}

	return true;
}
//-----------------------------------------------------------------------------
//
// DirectInput(Mouse)�p�֐�
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// DirectInput�̃}�E�X�f�o�C�X�p�̏���������
//-----------------------------------------------------------------------------
bool InitDInputMouse(HWND hWnd)
{
	HRESULT ret = S_FALSE;
	if (g_pDInput == NULL) {
		return false;
	}

	// �}�E�X�p�Ƀf�o�C�X�I�u�W�F�N�g���쐬
	ret = g_pDInput->CreateDevice(GUID_SysMouse, &g_pDIMouse, NULL);
	if (FAILED(ret)) {
		// �f�o�C�X�̍쐬�Ɏ��s
		return false;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	ret = g_pDIMouse->SetDataFormat(&c_dfDIMouse);	// �}�E�X�p�̃f�[�^�E�t�H�[�}�b�g��ݒ�
	if (FAILED(ret)) {
		// �f�[�^�t�H�[�}�b�g�Ɏ��s
		return false;
	}

	// ���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	ret = g_pDIMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(ret)) {
		// ���[�h�̐ݒ�Ɏ��s
		return false;
	}

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j

	ret = g_pDIMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph);
	if (FAILED(ret)) 
	{
		// �f�o�C�X�̐ݒ�Ɏ��s
		return false;
	}

	// ���͐���J�n
	g_pDIMouse->Acquire();

	return true;
}
//-----------------------------------------------------------------------------
// DirectInput�̃}�E�X�f�o�C�X�p�̉������
//-----------------------------------------------------------------------------
bool ReleaseDInputMouse()
{
	// DirectInput�̃f�o�C�X���J��
	if (g_pDIMouse) {
		g_pDIMouse->Release();
		g_pDIMouse = NULL;
	}

	return true;

}
// --> �����܂ŁADirectInput�ŕK�v�ȃR�[�h

//-----------------------------------------------------------------------------
// DirectInput�̃}�E�X�f�o�C�X��Ԏ擾����
//-----------------------------------------------------------------------------
void GetMouseState(HWND hWnd)
{
	if (g_pDIMouse == NULL) {
		// �I�u�W�F�N�g�����O�ɌĂ΂ꂽ�Ƃ��͂����Ő���������
		InitDInputMouse(hWnd);
	}

	// �ǎ�O�̒l��ێ����܂�
	DIMOUSESTATE g_zdiMouseState_bak;	// �}�E�X���(�ω����m�p)
	memcpy(&g_zdiMouseState_bak, &g_zdiMouseState, sizeof(g_zdiMouseState_bak));

	// ��������ADirectInput�ŕK�v�ȃR�[�h -->
		// �}�E�X�̏�Ԃ��擾���܂�
	HRESULT	hr = g_pDIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &g_zdiMouseState);
	if (hr == DIERR_INPUTLOST) {
		g_pDIMouse->Acquire();
		hr = g_pDIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &g_zdiMouseState);
	}
	// --> �����܂ŁADirectInput�ŕK�v�ȃR�[�h

	if (memcmp(&g_zdiMouseState_bak, &g_zdiMouseState, sizeof(g_zdiMouseState_bak)) != 0) {
		// �m�F�p�̏����A�������� -->
				// �l���ς������\�����܂�
		char buf[128];
		wsprintf(buf, "(%5d, %5d, %5d) %s %s %s\n",
			g_zdiMouseState.lX, g_zdiMouseState.lY, g_zdiMouseState.lZ,
			(g_zdiMouseState.rgbButtons[0] & 0x80) ? "Left" : "--",
			(g_zdiMouseState.rgbButtons[1] & 0x80) ? "Right" : "--",
			(g_zdiMouseState.rgbButtons[2] & 0x80) ? "Center" : "--");
		OutputDebugString(buf);
		// --> �����܂ŁA�m�F�p�̏���
	}
}
