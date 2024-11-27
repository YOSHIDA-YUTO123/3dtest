//============================
//
// メイン[main.h]
// Author:YOSHIDA YUUTO
//
//============================
#ifndef _MAIN_H_
#define _MAIN_H_

//****************************
//インクルードファイル
//****************************
#include<windows.h>
#include"d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)//ビルド時の警告対処マクロ
#include "dinput.h"
#include"Xinput.h"
#include"xaudio2.h"

//*****************************
//ライブラリのリンク
//*****************************
#pragma comment(lib,"d3d9.lib")//描画処理に必要
#pragma comment(lib,"d3dx9.lib")//[d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")//DirectXコンポネーション(部品)使用に必要
#pragma comment(lib,"winmm.lib")//システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")//入力処理に必要
#pragma comment(lib,"xinput.lib")//ジョイパッド処理に必要

//マクロ定義
#define CLASS_NAME "WindowClass" //ウインドウクラスの名前
#define WINDOW_NAME "3DTEST" //ウインドウの名前(キャプションに表示)
#define SCREEN_WIDTH (1280) //ウインドウの幅
#define SCREEN_HEIGHT (720) //ウインドウの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)//座標、法線、カラー、テクスチャ

//*******************
//2D構造体
//*******************
typedef struct
{
	D3DXVECTOR3 Pos; //頂点座標
	float rhw;       //座標返還係数(1.0fで指定)
	D3DCOLOR col;    //頂点カラー
	D3DXVECTOR2 tex;//テクスチャ座標
}VERTEX_2D;

//*******************
//3D構造体
//*******************
typedef struct
{
	D3DXVECTOR3 Pos; //頂点座標
	D3DXVECTOR3 nor; //法線ベクトル
	D3DCOLOR col;    //頂点カラー
	D3DXVECTOR2 tex;//テクスチャ座標
	D3DXVECTOR3 rot;
}VERTEX_3D;

//********************
//モード
//********************
typedef enum
{
	MODE_TITLE = 0, //タイトル画面
	MODE_SELECT,//	選択画面
	MODE_STAGESELECT,//	選択画面
	MODE_TUTORIAL,//チュートリアル画面
	MODE_TUTORIAL2,//チュートリアル画面
	MODE_GAME,//ゲーム画面
	MODE_GAME2,//ゲーム2画面
	MODE_RESULT,//リザルト画面
	MODE_RANKING,//ランキング画面
	MODE_EDIT,//ツール
	MODE_MAX
}MODE;

//********************
//パッドのボタン
//********************
typedef enum
{
	JOYKEY_UP=0,//十字キー上
	JOYKEY_DOWN,//十字キー下
	JOYKEY_LEFT,//十字キー左
	JOYKEY_RIGHT,//十字キー右
	JOYKEY_START,//START
	JOYKEY_BAKC,//BACK
	JOYKEY_LEFT_L3,
	JOYKEY_RIGHT_R3,
	JOYKEY_LEFT_LT,//左トリガー
	JOYKEY_RIGHT_RT,//右トリガー
	JOYKEY_LB,
	JOYKEY_RB,
	JOYKEY_A,//Aボタン
	JOYKEY_B,//Bボタン
	JOYKEY_X,//Xボタン
	JOYKEY_Y,//Yボタン
	JOYKEY_MAX

}JOYKEY;

//**********************************
//プロトタイプ宣言
//**********************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//メイン関数
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);//初期化処理
void Uninit(void);//終了処理
void Update(void);//更新処理
void Draw(void);//描画処理
void DrawFps(void);//fps表示用デバックフォント
void DrawCameraRot(void);//カメラ回転表示用デバックフォント
void DrawCameraState(void);//カメラ状態表示用デバックフォント
LPDIRECT3DDEVICE9 GetDevice(void);//デバイスの取得
void SetMode(MODE mode);//モード設定
MODE GetMode(void);//モード取得
void ToggleFullscreen(HWND hWnd);                                                   // ウィンドウをフルスクリーンにする方法
void onWireFrame();
void offWireFrame();


#endif
