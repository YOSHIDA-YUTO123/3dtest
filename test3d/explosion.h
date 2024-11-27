//============================
//
// 爆発[explosion.h]
// Author:YOSHIDA YUUTO
//
//============================

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//****************************
//インクルードファイル
//****************************
#include"main.h"

//****************************
//爆発の構造体
//****************************
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXMATRIX mtxWorld;//ワールドマトリックス
	int nCounterAnim;
	int nPatternAnim;
	int nIdxShadow;//番号
	int nLife;//寿命
	bool bUse;//使用しているかどうか
}EXPLOSION;

//****************************
//プロトタイプ宣言
//****************************
void InitExplosion(void);//爆発の初期化処理
void UninitExplosion(void);//爆発の終了処理
void UpdateExplosion(void);//爆発の更新処理
void DrawExplosion(void);//爆発の描画処理
void SetExplosion(D3DXVECTOR3 pos);//爆発の設定処理
#endif
