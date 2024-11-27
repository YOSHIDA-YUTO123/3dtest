//============================
//
// パーティクル[particle.h]
// Author:YOSHIDA YUUTO
//
//============================

#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//****************************
//インクルードファイル
//****************************
#include"main.h"
#include"shadow.h"

//****************************
//パーティクル種類の列挙型
//****************************
typedef enum
{
	PARTICLETYPE_NORMAL = 0,
	PARTICLETYPE_MAX
}PARTICLETYPE;

//****************************
//パーティクルの構造体
//****************************
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXCOLOR col;//色
	int nLife;//寿命
	int nType;//種類
	bool bUse;//使用しているかどうか
}PARTICLE;

//****************************
//プロトタイプ宣言
//****************************
void InitParticle(void);//パーティクルの初期化処理
void UninitParticle(void);//パーティクルの終了処理
void UpdateParticle(void);//パーティクルの更新処理
void DrawParticle(void);//パーティクルの描画処理
void SetParticle(D3DXVECTOR3 pos,int nLife, D3DXCOLOR col);//パーティクルの設定処理
#endif
