//============================
//
// エフェクト[effect.h]
// Author:YOSHIDA YUUTO
//
//============================

#ifndef _EFFECT_H_
#define _EFFECT_H_

//****************************
//インクルードファイル
//****************************
#include"main.h"

//****************************
//エフェクト種類の列挙型
//****************************
typedef enum
{
	EFFECTTYPE_PLAYER=0,
	EFFECTTYPE_BULLET,
	EFFECTTYPE_MAX
}EFFECTTYPE;

//****************************
//エフェクトの構造体
//****************************
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 move;//移動量
	D3DXCOLOR col;//色
	D3DXMATRIX mtxWorld;//ワールドマトリックス
	D3DXVECTOR3 fScal;
	float fRadius;
	int nLife;//寿命
	bool bUse;//使用しているかどうか
	EFFECTTYPE nType;//種類
}EFFECT;

//****************************
//プロトタイプ宣言
//****************************
void InitEffect(void);//エフェクトの初期化処理
void UninitEffect(void);//エフェクトの終了処理
void UpdateEffect(void);//エフェクトの更新処理
void DrawEffect(void);//エフェクトの描画処理
void SetEffect(D3DXVECTOR3 pos,D3DXVECTOR3 move, D3DXCOLOR col, int nLife,D3DXVECTOR3 fScal);//エフェクトの設定処理
#endif
