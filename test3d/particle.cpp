//============================
//
// パーティクル[particle.cpp]
// Author:YOSHIDA YUUTO
//
//============================

//****************************
//インクルードファイル
//****************************
#include "bullet.h"
#include "input.h"
#include "player.h"
#include "camera.h"
#include "shadow.h"
#include "explosion.h"
#include "effect.h"
#include "particle.h"

//****************************
//マクロ定義
//****************************
#define BULLET_WIDTH (25.0f) //横幅
#define BULLET_HEIGHT (25.0f) //高さ
#define MAX_PARTICLE (128) //弾の最大数
#define MAX_MOVE (5.0f) //移動量

//****************************
//グローバル変数宣言
//****************************
PARTICLE g_aParticle[MAX_PARTICLE];

//============================
//弾の初期化処理
//============================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		g_aParticle[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCnt].col = D3DXCOLOR(0.0f,0.0f,0.0f,0.0f);
		g_aParticle[nCnt].nLife = 0;
		g_aParticle[nCnt].bUse = false;
	}
}
//============================
//弾の終了処理
//============================
void UninitParticle(void)
{

}
//============================
//弾の更新処理
//============================
void UpdateParticle(void)
{
	int nCntParticle, nCntApper;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 move;
	D3DXCOLOR col;
	D3DXVECTOR3 fScal;

	for (nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		if (g_aParticle[nCntParticle].bUse == true)
		{//使用している

			//パーティクル生成
			for (nCntApper = 0; nCntApper < 5/*発生させたい粒子の数*/; nCntApper++)
			{
				float fAngleX = (float)(rand() % 629 - 314) * 0.01f;
				float fAngleY = (float)(rand() % 629 - 314) * 0.01f;
				float fAngleZ = (float)(rand() % 629 - 314) * 0.01f;

				float fMove = ((float)(rand() % 5) + 0.5f);

				//位置の設定pos
				pos = g_aParticle[nCntParticle].pos;

				//移動量の設定
				move.x = sinf(fAngleX) * fMove;
				move.y = cosf(fAngleY) * fMove;
				move.z = cosf(fAngleZ) * fMove;

				//色の設定col
				col = g_aParticle[nCntParticle].col;

				//半径の設定fRadius
				fScal.x = ((float)(rand() % 1)+ 1.0f);
				fScal.y = ((float)(rand() % 1)+ 1.0f);
				fScal.z = ((float)(rand() % 1)+ 1.0f);

				int nLife = (rand() % 60) + 1;

				//エフェクトの設定SetEffect
				SetEffect(pos, move, col, nLife, fScal);
			}

			g_aParticle[nCntParticle].nLife--;

			//寿命の設定
			if (g_aParticle[nCntParticle].nLife <= 0)//寿命が尽きた
			{
				g_aParticle[nCntParticle].bUse = false;
			}
		}
	}

}
//============================
//弾の描画処理
//============================
void DrawParticle(void)
{
}
//============================
//弾の描画処理
//============================
void SetParticle(D3DXVECTOR3 pos ,int nLife, D3DXCOLOR col)
{
	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		if (g_aParticle[nCnt].bUse == false)
		{
			g_aParticle[nCnt].pos = pos;
			g_aParticle[nCnt].col = col;
			g_aParticle[nCnt].nLife = nLife;
			g_aParticle[nCnt].bUse = true;

			break;
		}
	}
}
