//============================
//
// カメラ[camera.h]
// Author:YOSHIDA YUUTO
//
//============================

#ifndef _CAMERA_H_
#define _CAMERA_H_

//***********************
//インクルードファイル
//***********************

#include"main.h"

//*******************
//カメラの状態変更
//*******************
typedef enum
{
	CAMERASTATE_NORMAL=0,//通常状態
	CAMERASTATE_PLAYER,//プレイヤー追従状態
	CAMERASTATE_MAX
}CAMERASTATE;

//*******************
//カメラの構造体
//*******************
typedef struct
{
	D3DXVECTOR3 posV;//視点
	D3DXVECTOR3 posR;//注視点
	D3DXVECTOR3 posVDest;//目的の視点
	D3DXVECTOR3 posRDest;//目的の注視点
	D3DXVECTOR3 vecU;//上方向ベクトル
	D3DXMATRIX mtxProjection;//プロジェクションマトリックス
	D3DXMATRIX mtxView;//ビューマトリックス
	D3DXVECTOR3 rot;//向き
	D3DXVECTOR3 rotDest;//向き
	float fDistance;//視点から注視点までの距離
	CAMERASTATE state;//カメラの状態
	bool behind;
}CAMERA;

//*********************
//プロトタイプ宣言
//*********************
void InitCamera(void);//カメラの初期化処理
void UninitCamera(void);//カメラの終了処理
void UpdateCamera(void);//カメラの更新処理
void SetCamera(void);//カメラの設定処理
CAMERA* GetCamera(void);//カメラの取得処理
#endif
