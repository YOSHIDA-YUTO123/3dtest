//============================
//
//プレイヤー
//Author:YOSHIDA YUUTO
//
//
//============================

#ifndef _PLAYER_H_
#define _PLAYER_H_

//**************************
//インクルードファイル
//**************************
#include"main.h"

//**************************
//マクロ定義
//**************************
#define PLAYER_MOVE (1.0f)
#define WIDTH (100.0f) //壁の横幅
#define HEIGHT (100.0f) //壁の高さ

//**************************
//プレイヤー構造体
//**************************
typedef struct
{
	D3DXVECTOR3 pos;//位置
	D3DXVECTOR3 posOld;//前回の位置
	D3DXVECTOR3 Size;//大きさ
	D3DXVECTOR3 rot;//向き
	D3DXVECTOR3 rotDestPlayer;//目的の角度
	D3DXVECTOR3 move;//移動量
	D3DXVECTOR3	vtxMinPlayer;
	D3DXVECTOR3	vtxMaxPlayer;
	D3DXMATRIX mtxWorldPlayer;//ワールドマトリックス
	int nIdxShadow;
	bool bJump;
	bool bDisp;
}PLAYER;

//**************************
//プロトタイプ宣言
//**************************
void InitPlayer(void);//プレイヤーの初期化処理
void UninitPlayer(void);//プレイヤーの終了処理
void UpdatePlayer(void);//プレイヤーの更新処理
void DrawPlayer(void);//プレイヤーの描画処理
PLAYER* GetPlayer(void);//プレイヤーの取得処理

#endif
