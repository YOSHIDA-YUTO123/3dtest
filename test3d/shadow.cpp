//============================
//
// 影[shadow.cpp]
// Author:YOSHIDA YUUTO
//
//============================

//****************************
//インクルードファイル
//****************************
#include"shadow.h"

//****************************
//マクロ定義
//****************************
#define MAX_SHADOW (128)

//****************************
//グローバル変数宣言
//****************************
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL; //頂点バッファへのポインタ
SHADOW g_Shadow[MAX_SHADOW];//影の構造体

//=============================
//影の初期化処理
//=============================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_pTextureShadow);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D* pVtx = NULL;

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_Shadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCntShadow].bUse = false;
	}

	//頂点バッファをロック
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//頂点座標の設定
		pVtx[0].Pos = D3DXVECTOR3(g_Shadow[nCntShadow].pos.x - 50.0f, 1.0f, g_Shadow[nCntShadow].pos.z + 50.0f);
		pVtx[1].Pos = D3DXVECTOR3(g_Shadow[nCntShadow].pos.x + 50.0f, 1.0f, g_Shadow[nCntShadow].pos.z + 50.0f);
		pVtx[2].Pos = D3DXVECTOR3(g_Shadow[nCntShadow].pos.x - 50.0f, 1.0f, g_Shadow[nCntShadow].pos.z - 50.0f);
		pVtx[3].Pos = D3DXVECTOR3(g_Shadow[nCntShadow].pos.x + 50.0f, 1.0f, g_Shadow[nCntShadow].pos.z - 50.0f);

		//各頂点の法線の設定(ベクトルの大きさは１にする必要がある)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

		//テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	g_pVtxBuffShadow->Unlock();
}
//=============================
//影の終了処理
//=============================
void UninitShadow(void)
{
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//頂点バッファの解放
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}
//=============================
//影の更新処理
//=============================
void UpdateShadow(void)
{

}
//=============================
//影の描画処理
//=============================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//減算合成
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//アルファテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, NULL);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Shadow[nCntShadow].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Shadow[nCntShadow].rot.y, g_Shadow[nCntShadow].rot.x, g_Shadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_Shadow[nCntShadow].mtxWorld, &g_Shadow[nCntShadow].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Shadow[nCntShadow].pos.x, g_Shadow[nCntShadow].pos.y, g_Shadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_Shadow[nCntShadow].mtxWorld, &g_Shadow[nCntShadow].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Shadow[nCntShadow].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			//テクスチャフォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureShadow);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntShadow * 4, 2);
		}
	}

	//アルファテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//設定をもとに戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//=============================
//影の設定処理
//=============================
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	int nCntShadow;

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == false)
		{
			g_Shadow[nCntShadow].pos = pos;
			g_Shadow[nCntShadow].rot = rot;
			g_Shadow[nCntShadow].bUse = true;

			break;
		}
	}

	return nCntShadow;//影の番号(index)を返す
	g_pVtxBuffShadow->Unlock();
}
//=============================
//影の位置の設定処理
//=============================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos)
{
	//引数で設定された番号の影のposを設定
	g_Shadow[nIdxShadow].pos = pos;
}
//=============================
//影の使用状態の設定処理
//=============================
void EnableShadow(int nIdxShadow)
{
	g_Shadow[nIdxShadow].bUse = false;
}
