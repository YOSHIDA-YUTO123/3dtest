//============================
//
// ライト[light.cpp]
// Author:YOSHIDA YUUTO
//
//============================

//****************************
//インクルードファイル
//****************************
#include "light.h"

//****************************
//マクロ定義
//****************************
#define MAX_LIGHT (4)

//****************************
//グローバル変数宣言
//****************************
D3DLIGHT9 g_Light[MAX_LIGHT];//ライト情報
D3DXVECTOR3 g_vecDir[MAX_LIGHT];//ライトの方向ベクトル

//============================
//ライトの初期化処理
//============================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();

	//ライトをクリアする
	ZeroMemory(&g_Light, sizeof(g_Light));

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		g_vecDir[nCntLight];

		//ライトの情報を設定
		g_Light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		//ライトの拡散光を設定
		g_Light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//ライトの方向を設定
	g_vecDir[0] = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
	g_vecDir[1] = D3DXVECTOR3(-0.5f, -0.8f, 0.0f);
	g_vecDir[2] = D3DXVECTOR3(0.5f, -0.8f, -0.8f);
	g_vecDir[3] = D3DXVECTOR3(0.5f, -0.8f, -0.8f);

	for (int nCntLight1 = 0; nCntLight1 < MAX_LIGHT; nCntLight1++)
	{
		//正視化する(大きさ位置のベクトルにする)
		D3DXVec3Normalize(&g_vecDir[nCntLight1], &g_vecDir[nCntLight1]);

		g_Light[nCntLight1].Direction = g_vecDir[nCntLight1];

		//ライトを設定する
		pDevice->SetLight(nCntLight1, &g_Light[nCntLight1]);

		//ライトを有効にする(ON,OFF)
		pDevice->LightEnable(nCntLight1, TRUE);
	}
}
//============================
//ライトの終了処理
//============================
void UninitLight(void)
{

}
//============================
//ライトの更新処理
//============================
void UpdateLight(void)
{

}
