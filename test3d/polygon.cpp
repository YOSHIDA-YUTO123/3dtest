//============================
//
// ポリゴン[polygon.cpp]
// Author:YOSHIDA YUUTO
//
//============================

//****************************
//インクルードファイル
//****************************
#include"polygon.h"

//****************************
//グローバル変数宣言
//****************************
LPDIRECT3DTEXTURE9 g_pTexturePolygon = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL; //頂点バッファへのポインタ
D3DXVECTOR3 g_posPolygon; //位置
D3DXVECTOR3 g_rotPolygon; //向き
D3DXMATRIX g_mtxWorldPolygon;//ワールドマトリックス

//============================
//ポリゴンの初期化処理
//=============================
void InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\jimen.jpg",
		&g_pTexturePolygon);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL);

	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].Pos = D3DXVECTOR3(-350.0f, 0.0f, 350.0f);
	pVtx[1].Pos = D3DXVECTOR3(350.0f, 0.0f, 350.0f);
	pVtx[2].Pos = D3DXVECTOR3(-350.0f, 0.0f, -350.0f);
	pVtx[3].Pos = D3DXVECTOR3(350.0f, 0.0f, -350.0f);

	//各頂点の法線の設定(ベクトルの大きさは１にする必要がある)
	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

	//頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

	g_pVtxBuffPolygon->Unlock();
}
//============================
//ポリゴンの終了処理
//=============================
void UninitPolygon(void)
{
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon -> Release();
		g_pTexturePolygon = NULL;
	}

	//頂点バッファの解放
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}
//============================
//ポリゴンの更新処理
//=============================
void UpdatePolygon(void)
{

}
//============================
//ポリゴンの描画処理
//=============================
void DrawPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldPolygon);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotPolygon.y, g_rotPolygon.x, g_rotPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);
	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolygon);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

	//テクスチャフォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePolygon);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
