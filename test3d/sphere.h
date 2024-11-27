//=================================
//
// メッシュスフィア [meshsphere.h]
// Author:YOSHIDA YUUTO
//
//=================================

#ifndef _SPHERE_H_
#define _SPHERE_H_

//****************************
//インクルードファイル
//****************************
#include"main.h"

//****************************
//マクロ定義
//****************************
#define MAX_SPHERE_WIDTH (350.0f) //横幅
#define MAX_SPHERE_HEIGHT (350.0f) //高さ

#define SPHERE_XVTX (2) //Xの値
#define SPHERE_ZVTX (2) //yの値

#define SPHERE_VERTEX ((SPHERE_XVTX + 1) * (SPHERE_ZVTX +1) + 1) //頂点数
#define SPHERE_INDEX (SPHERE_POLYGON + 2)  //インデックス
#define SPHERE_POLYGON (((SPHERE_XVTX * SPHERE_ZVTX) * 2)) + (4 * (SPHERE_ZVTX - 1)) //ポリゴン数

//****************************
//メッシュスフィアの構造体
//****************************
typedef struct
{
	D3DXVECTOR3 pos;//メッシュスフィアの位置
	D3DXVECTOR3 rot;//メッシュスフィアの向き
	D3DXMATRIX mtxWorldMeshSphere;//メッシュスフィアのワールドマトリックス
}MESHSPHERE;

//****************************
//プロトタイプ宣言
//****************************
void InitMeshSphere(void);//メッシュスフィアの初期化処理
void UninitMeshSphere(void);//メッシュスフィアの終了処理
void UpdateMeshSphere(void);//メッシュスフィアの更新処理
void DrawMeshSphere(void);//メッシュスフィアの描画処理
#endif
