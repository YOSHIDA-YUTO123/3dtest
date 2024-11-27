//============================
//
// キーボード [input.h]
// Author:YOSHIDA YUUTO
//
//============================

#ifndef _INPUT_H_
#define _INPUT_H_

//***********************
//インクルードファイル
//***********************
#include "main.h"

//************************
//プロトタイプ宣言
//************************
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);

void UninitKeyboard(void);
void UpdateKeyboard(void);
bool GetKeyboardPress(int nKey);
bool KeyboardTrigger(int nKey);
bool KeyboardRelease(int nKey);
bool KeyboardRepeat(int nKey);

HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool GetJoypadPress(JOYKEY key);
//bool JoyPadTrigger(JOYKEY key);
bool GetJoyTrigger(JOYKEY key);
bool GetJoyTriggerTrigger(JOYKEY key);
bool GetJoyTriggerRelease(JOYKEY key);
//bool JoyKeyRelease(JOYKEY key);
bool JoyKeyRepeat(JOYKEY key);
bool GetJoyPadTrigger(JOYKEY key);
bool GetJoyPadRelease(JOYKEY key);

bool InitDInput(HINSTANCE hInstApp, HWND hWnd);
bool ReleaseDInput(void);
bool ReleaseDInputMouse();
void GetMouseState(HWND hWnd);

//スティック
bool GetJoyStick(void);
XINPUT_STATE* GetJoySticAngle(void);
#endif
