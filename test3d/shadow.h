//============================
//
// 影[shadow.h]
// Author:YOSHIDA YUUTO
//
//============================

#ifndef _SHADOW_H_
#define _SHADOW_H_

//****************************
//インクルードファイル
//****************************
#include"main.h"

//****************************
//影の構造体
//****************************
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	bool bUse;
}SHADOW;

//****************************
//プロトタイプ宣言
//****************************
void InitShadow(void);//影の初期化処理
void UninitShadow(void);//影の終了処理
void UpdateShadow(void);//影の更新処理
void DrawShadow(void);//影の描画処理
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot);//影の設定処理
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos);//影の位置設定処理
void EnableShadow(int nIdxShadow); //影の使用状態の設定処理
//SHADOW* GetShadow(void);
#endif
