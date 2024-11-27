//============================
//
// 壁[wall.h]
// Author:YOSHIDA YUUTO
//
//============================

#ifndef _WALL_H_
#define _WALL_H_

//****************************
//インクルードファイル
//****************************
#include"main.h"

//****************************
//壁の構造体
//****************************
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXMATRIX mtxWorld;
	float fA;
	float fDepth;
	float fWidth;
	float fHeight;
	D3DXVECTOR3 fScal;
	bool bUse;
	D3DXVECTOR3 vecLine;
	D3DXVECTOR3 vecPos;
	D3DXMATRIX rotmtx;
	D3DXMATRIX posmtx;
}WALL;

//****************************
//プロトタイプ宣言
//****************************
void InitWall(void);//壁の初期化処理
void UninitWall(void);//壁の終了処理
void UpdateWall(void);//壁の更新処理
void DrawWall(void);//壁の描画処理
//void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 fScal,float fA);//壁の設定処理
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float fA,float fWidth,float fHeight);//壁の設定処理
void CollisionWall(void);
#endif