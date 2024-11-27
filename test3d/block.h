//============================
//
// ブロック[block.h]
// Author:YOSHIDA YUUTO
//
//============================

#ifndef _BLOCK_H_
#define _BLOCK_H_

//***************************
//インクルードファイル
//***************************
#include"main.h"
#include"player.h"

//***************************
//ブロックの構造体
//***************************
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 rot;//向き
	D3DXVECTOR3 Scal;//大きさ
	D3DXMATRIX mtxWorldBlock;//ワールドマトリックス
	D3DXVECTOR3 vtxMin, vtxMax;
	D3DXVECTOR3 Size;
}BLOCK;

//***************************
//プロトタイプ宣言
//***************************
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
bool CollisionBlock(void);
#endif
