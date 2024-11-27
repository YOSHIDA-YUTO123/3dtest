//============================
//
// 弾[bullet.h]
// Author:YOSHIDA YUUTO
//
//============================

#ifndef _BULLET_H_
#define _BULLET_H_

//****************************
//インクルードファイル
//****************************
#include"main.h"
#include"shadow.h"

//****************************
//弾の種類
//****************************
typedef enum
{
	BULLETTYPE_PLAYER=0,
	BULLETTYPE_ENEMY,
	BULLETTYPE_MAX
}BULLETTYPE;

//****************************
//弾の構造体
//****************************
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 move;//移動量
	D3DXVECTOR3 dir;//向き
	D3DXMATRIX mtxWorld;//ワールドマトリックス
	int nIdxShadow;//
	int nLife;//寿命
	bool bUse;//使用しているかどうか
}BULLET;

//****************************
//プロトタイプ宣言
//****************************
void InitBullet(void);//弾の初期化処理
void UninitBullet(void);//弾の終了処理
void UpdateBullet(void);//弾の更新処理
void DrawBullet(void);//弾の描画処理
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 dir, D3DXVECTOR3 move, int nLife);//弾の設定処理
#endif
