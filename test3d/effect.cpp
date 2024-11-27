//============================
//
// エフェクト[effect.cpp]
// Author:YOSHIDA YUUTO
//
//============================

//****************************
//インクルードファイル
//****************************
#include "camera.h"
#include "effect.h"

//****************************
//マクロ定義
//****************************
#define EFFECT_WIDTH (25.0f) //横幅
#define EFFECT_HEIGHT (25.0f) //高さ
#define MAX_EFFECT (4096) //爆発の最大数

//****************************
//グローバル変数宣言
//****************************
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL; //頂点バッファへのポインタ
EFFECT g_Effect[MAX_EFFECT];

//============================
//爆発の初期化処理
//============================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\effect000.png",
		&g_pTextureEffect);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	VERTEX_3D* pVtx = NULL;

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		g_Effect[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Effect[nCnt].fScal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Effect[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Effect[nCnt].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
		g_Effect[nCnt].nLife = 0;
		g_Effect[nCnt].nType = EFFECTTYPE_PLAYER;
		g_Effect[nCnt].fRadius = 25.0f;
		g_Effect[nCnt].bUse = false;
	}
	//頂点バッファをロック
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].Pos.x = -EFFECT_WIDTH;
		pVtx[0].Pos.y = EFFECT_HEIGHT;
		pVtx[0].Pos.z = 0.0f;

		pVtx[1].Pos.x = EFFECT_WIDTH;
		pVtx[1].Pos.y = EFFECT_HEIGHT;
		pVtx[1].Pos.z = 0.0f;

		pVtx[2].Pos.x = -EFFECT_WIDTH;
		pVtx[2].Pos.y = -EFFECT_HEIGHT;
		pVtx[2].Pos.z = 0.0f;

		pVtx[3].Pos.x = EFFECT_WIDTH;
		pVtx[3].Pos.y = -EFFECT_HEIGHT;
		pVtx[3].Pos.z = 0.0f;

		//各頂点の法線の設定(ベクトルの大きさは１にする必要がある)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);//カメラに対して垂直に
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	g_pVtxBuffEffect->Unlock();
}
//============================
//爆発の終了処理
//============================
void UninitEffect(void)
{
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	//頂点バッファの解放
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}
//============================
//爆発の更新処理
//============================
void UpdateEffect(void)
{
	VERTEX_3D* pVtx;

	//頂点バッファをロック
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_Effect[nCnt].bUse == true)
		{
			g_Effect[nCnt].pos += g_Effect[nCnt].move;

			g_Effect[nCnt].nLife--;
			g_Effect[nCnt].col.a -= 0.02f;

			if (g_Effect[nCnt].nLife <= 0)
			{
				g_Effect[nCnt].bUse = false;
			}
			//頂点カラー
			pVtx[0].col = (g_Effect[nCnt].col);
			pVtx[1].col = (g_Effect[nCnt].col);
			pVtx[2].col = (g_Effect[nCnt].col);
			pVtx[3].col = (g_Effect[nCnt].col);
			
			g_Effect[nCnt].fScal.x -= 0.01f;
			g_Effect[nCnt].fScal.y -= 0.01f;
			g_Effect[nCnt].fScal.z -= 0.01f;

		}
		pVtx += 4;
	}
	g_pVtxBuffEffect->Unlock();
}
//============================
//爆発の描画処理
//============================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//aブレンディング
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//アルファテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, NULL);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//ゼットテスト
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	CAMERA* pCamera = GetCamera();

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxView, mtxScal;

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_Effect[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Effect[nCnt].mtxWorld);

			if (g_Effect[nCnt].nType == EFFECTTYPE_PLAYER)
			{
				pDevice->GetTransform(D3DTS_VIEW, &mtxView);//ビューマトリックスの取得

				//カメラの逆行列の設定
				g_Effect[nCnt].mtxWorld._11 = mtxView._11;
				g_Effect[nCnt].mtxWorld._12 = mtxView._21;
				g_Effect[nCnt].mtxWorld._13 = mtxView._31;
				g_Effect[nCnt].mtxWorld._21 = mtxView._12;
				g_Effect[nCnt].mtxWorld._22 = mtxView._22;
				g_Effect[nCnt].mtxWorld._23 = mtxView._32;
				g_Effect[nCnt].mtxWorld._31 = mtxView._13;
				g_Effect[nCnt].mtxWorld._32 = mtxView._23;
				g_Effect[nCnt].mtxWorld._33 = mtxView._33;
			}

			//大きさ
			D3DXMatrixScaling(&mtxScal, g_Effect[nCnt].fScal.x, g_Effect[nCnt].fScal.y, g_Effect[nCnt].fScal.z);
			D3DXMatrixMultiply(&g_Effect[nCnt].mtxWorld, &g_Effect[nCnt].mtxWorld, &mtxScal);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Effect[nCnt].pos.x + pCamera->rot.y, g_Effect[nCnt].pos.y + pCamera->rot.y, g_Effect[nCnt].pos.z + pCamera->rot.y);
			D3DXMatrixMultiply(&g_Effect[nCnt].mtxWorld, &g_Effect[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Effect[nCnt].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			//テクスチャフォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureEffect);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}

	//ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//aブレンディングをもとに戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//アルファテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//ゼットテスト
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}
//============================
//爆発の設定処理
//============================
void SetEffect(D3DXVECTOR3 pos,D3DXVECTOR3 move,D3DXCOLOR col,int nLife, D3DXVECTOR3 fScal)
{
	VERTEX_3D* pVtx = NULL;

	for (int nCnt = 0; nCnt < MAX_EFFECT; nCnt++)
	{
		if (g_Effect[nCnt].bUse == false)
		{
			g_Effect[nCnt].pos = pos;
			g_Effect[nCnt].move = move;
			g_Effect[nCnt].col = col;
			g_Effect[nCnt].nLife = nLife;
			g_Effect[nCnt].fScal = fScal;
			g_Effect[nCnt].bUse = true;

			break;
		}
	}
}
