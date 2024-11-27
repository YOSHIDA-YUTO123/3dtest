//=================================
//
// メッシュウォール [meshwall.h]
// Author:YOSHIDA YUUTO
//
//=================================

#ifndef _MESHWALL_H_
#define _MESHWALL_H_

//****************************
//インクルードファイル
//****************************
#include"main.h"

//****************************
//マクロ定義
//****************************
#define MAX_WALL_WIDTH (150.0f) //横幅
#define MAX_WALL_HEIGHT (150.0f) //高さ

#define WALL_XVTX (8) //Xの値
#define WALL_ZVTX (8) //yの値

#define WALL_VERTEX ((WALL_XVTX + 1) * (WALL_ZVTX + 1)) //頂点数
#define WALL_INDEX (WALL_POLYGON + 2)  //インデックス
#define WALL_POLYGON (((WALL_XVTX * WALL_ZVTX) * 2)) + (4 * (WALL_ZVTX - 1)) //ポリゴン数
//****************************
//メッシュウォールの構造体
//****************************
typedef struct
{
	D3DXVECTOR3 pos;//メッシュウォールの位置
	D3DXVECTOR3 rot;//メッシュウォールの向き
	D3DXMATRIX mtxWorldMeshWall;//メッシュウォールのワールドマトリックス
}MESHWALL;

//****************************
//プロトタイプ宣言
//****************************
void InitMeshWall(void);//メッシュウォールの初期化処理
void UninitMeshWall(void);//メッシュウォールの終了処理
void UpdateMeshWall(void);//メッシュウォールの更新処理
void DrawMeshWall(void);//メッシュウォールの描画処理
#endif
