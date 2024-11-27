//============================
//
// キーボード[input.cpp]
// Author:YOSHIDA YUUTO
//
//============================

//***********************
//インクルードファイル
//***********************
#include"input.h"

//***********************
//マクロ定義
//***********************
#define NUM_KEY_MAX (256)//キーの最大数

//***********************
//グローバル変数		 
//***********************
LPDIRECTINPUT8 g_pInput=NULL;//DirectInputオブジェクトへのぽいんた
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;//入力デバイス(キーボード)へのポインタ
BYTE g_aKeyState[NUM_KEY_MAX];//キーボードのプレス情報
BYTE g_aOldState[NUM_KEY_MAX];
XINPUT_STATE g_joykeyState;//ジョイパッドのプレス情報
XINPUT_STATE g_Oldjoykeystate;
XINPUT_STATE g_joykeyStateTrigger;
XINPUT_STATE g_joykeyStateRelease;
LPDIRECTINPUTDEVICE8 g_pDIMouse = NULL;	// マウスデバイス
LPDIRECTINPUT8 g_pDInput = NULL;	// DirectInputオブジェクト
DIMOUSESTATE g_zdiMouseState;			// マウス状態

//=====================
//キーボードの入力処理
//=====================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//入力デバイス(キーボード)の生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モードを設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//キーボードへのアクセス権を獲得
	g_pDevKeyboard->Acquire();

	return S_OK;
}
//=====================
//キーボードの終了処理
//=====================
void UninitKeyboard(void)
{
	//入力デバイス(キーボード)の破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();//キーボードへのアクセス権を放棄
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInputオブジェクトの攻撃
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}
//=====================
//キーボードの更新処理
//=====================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];//キーボードの入力処理
	int nCntKey;

	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		g_aOldState[nCntKey] = g_aKeyState[nCntKey];//ひとつ前のキーボードプレス情報を保存
	}

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyState[nCntKey] = aKeyState[nCntKey];//キーボードのプレス情報を保存
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();//キーボードへのアクセス権を獲得
	}
}
//===========================
//キーボードのプレス情報取得
//===========================
bool GetKeyboardPress(int Key)
{
	return (g_aKeyState[Key] & 0x80) ? true : false;
}
//===========================
//キーボードのトリガー情報取得
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
//キーボードのリリース情報取得
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
//ジョイパッドの初期化処理
//=========================
HRESULT InitJoypad(void)
{
	//メモのクリア
	memset(&g_joykeyState, 0, sizeof(XINPUT_STATE));
	
	//memset(&g_Oldjoykeystate, 0, sizeof(XINPUT_STATE));

	//xinputのステートを有効にする
	XInputEnable(true);

	return S_OK;
}
//=======================
//ジョイパッドの終了処理
//=======================
void UninitJoypad(void)
{
	//XInputのステートを無効にする
	XInputEnable(false);
}

//=======================
//ジョイパッドの更新処理
//=======================
void UpdateJoypad(void)
{
	XINPUT_STATE joykeyState;//ジョイパッドの初期化処理
	
	//ジョイパッドの状態取得
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		WORD Button = joykeyState.Gamepad.wButtons;
		WORD OldButton = g_joykeyState.Gamepad.wButtons;

		g_joykeyStateTrigger.Gamepad.wButtons = Button & ~OldButton;
		g_joykeyStateRelease.Gamepad.wButtons = OldButton & ~Button;
		g_joykeyState = joykeyState;//ジョイパッドの入力情報
	}
}
//===============================
//ジョイパッドのプレス情報を取得
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
////ジョイパッドのトリガー処理
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
bool GetJoyTriggerTrigger(JOYKEY key)//押したとき
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
bool GetJoyTriggerRelease(JOYKEY key)//離したとき
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
//スティック処理
//===============
bool GetJoyStick()
{
	bool joykey = false;
	//真ん中じゃなかったら
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
//スティック情報の取得
//=====================
XINPUT_STATE* GetJoySticAngle(void)
{
	return &g_joykeyState;
}
bool InitDInput(HINSTANCE hInstApp, HWND hWnd)
{
	HRESULT ret = DirectInput8Create(hInstApp, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pDInput, NULL);
	if (FAILED(ret)) {
		return false;	// 作成に失敗
	}
	return true;
}
bool ReleaseDInput(void)
{
	// DirectInputのデバイスを開放
	if (g_pDInput) 
{
		g_pDInput->Release();
		g_pDInput = NULL;
	}

	return true;
}
//-----------------------------------------------------------------------------
//
// DirectInput(Mouse)用関数
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// DirectInputのマウスデバイス用の初期化処理
//-----------------------------------------------------------------------------
bool InitDInputMouse(HWND hWnd)
{
	HRESULT ret = S_FALSE;
	if (g_pDInput == NULL) {
		return false;
	}

	// マウス用にデバイスオブジェクトを作成
	ret = g_pDInput->CreateDevice(GUID_SysMouse, &g_pDIMouse, NULL);
	if (FAILED(ret)) {
		// デバイスの作成に失敗
		return false;
	}

	// データフォーマットを設定
	ret = g_pDIMouse->SetDataFormat(&c_dfDIMouse);	// マウス用のデータ・フォーマットを設定
	if (FAILED(ret)) {
		// データフォーマットに失敗
		return false;
	}

	// モードを設定（フォアグラウンド＆非排他モード）
	ret = g_pDIMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(ret)) {
		// モードの設定に失敗
		return false;
	}

	// デバイスの設定
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）

	ret = g_pDIMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph);
	if (FAILED(ret)) 
	{
		// デバイスの設定に失敗
		return false;
	}

	// 入力制御開始
	g_pDIMouse->Acquire();

	return true;
}
//-----------------------------------------------------------------------------
// DirectInputのマウスデバイス用の解放処理
//-----------------------------------------------------------------------------
bool ReleaseDInputMouse()
{
	// DirectInputのデバイスを開放
	if (g_pDIMouse) {
		g_pDIMouse->Release();
		g_pDIMouse = NULL;
	}

	return true;

}
// --> ここまで、DirectInputで必要なコード

//-----------------------------------------------------------------------------
// DirectInputのマウスデバイス状態取得処理
//-----------------------------------------------------------------------------
void GetMouseState(HWND hWnd)
{
	if (g_pDIMouse == NULL) {
		// オブジェクト生成前に呼ばれたときはここで生成させる
		InitDInputMouse(hWnd);
	}

	// 読取前の値を保持します
	DIMOUSESTATE g_zdiMouseState_bak;	// マウス情報(変化検知用)
	memcpy(&g_zdiMouseState_bak, &g_zdiMouseState, sizeof(g_zdiMouseState_bak));

	// ここから、DirectInputで必要なコード -->
		// マウスの状態を取得します
	HRESULT	hr = g_pDIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &g_zdiMouseState);
	if (hr == DIERR_INPUTLOST) {
		g_pDIMouse->Acquire();
		hr = g_pDIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &g_zdiMouseState);
	}
	// --> ここまで、DirectInputで必要なコード

	if (memcmp(&g_zdiMouseState_bak, &g_zdiMouseState, sizeof(g_zdiMouseState_bak)) != 0) {
		// 確認用の処理、ここから -->
				// 値が変わったら表示します
		char buf[128];
		wsprintf(buf, "(%5d, %5d, %5d) %s %s %s\n",
			g_zdiMouseState.lX, g_zdiMouseState.lY, g_zdiMouseState.lZ,
			(g_zdiMouseState.rgbButtons[0] & 0x80) ? "Left" : "--",
			(g_zdiMouseState.rgbButtons[1] & 0x80) ? "Right" : "--",
			(g_zdiMouseState.rgbButtons[2] & 0x80) ? "Center" : "--");
		OutputDebugString(buf);
		// --> ここまで、確認用の処理
	}
}
