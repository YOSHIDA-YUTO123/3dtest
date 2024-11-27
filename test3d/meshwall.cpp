//=================================
//
// メッシュウォール[meshfield.cpp]
// Author:YOSHIDA YUUTO
//
//=================================

//****************************
//インクルードファイル
//****************************
#include "meshwall.h"

//****************************
//グローバル変数宣言
//****************************
LPDIRECT3DTEXTURE9 g_pTextureMeshWall = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL; //頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;//インデックスバッファへのポインタ
MESHWALL g_MeshWall;

//===============================
//メッシュウォールの初期化処理
//===============================
void InitMeshWall(void)
{
	int nCnt = 0;

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();//デバイスを取得

		//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&g_pTextureMeshWall);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * WALL_VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * WALL_INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall,
		NULL);

	g_MeshWall.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshWall.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	float fTexX = 1.0f / WALL_XVTX;
	float fTexY = 1.0f / WALL_ZVTX;

	D3DXVECTOR3 nor;

	int radius = 700;

	//縦
	for (int nCntV = 0; nCntV < WALL_ZVTX + 1; nCntV++)
	{
		//横
		for (int nCntH = 0; nCntH < WALL_XVTX + 1; nCntH++)
		{
			float fAngel = (D3DX_PI * 2.0f) / WALL_XVTX * nCntH;
			
			//頂点座標の設定
			pVtx[nCnt].Pos = D3DXVECTOR3(
				MAX_WALL_WIDTH + sinf(fAngel) * radius,
				500.0f - ((nCntV * MAX_WALL_WIDTH)),
				MAX_WALL_WIDTH + cosf(fAngel) * radius);
		
			nor = pVtx[nCnt].Pos - g_MeshWall.pos;

			//法線ベクトルの設定
			pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			
			D3DXVec3Normalize(&pVtx[nCnt].nor,&nor);

			//頂点カラーの設定
			pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ座標の設定
			pVtx[nCnt].tex = D3DXVECTOR2(fTexX * nCntH, nCntV * fTexY);

			nCnt++;//加算

		}
	}

	g_pVtxBuffMeshWall->Unlock();

	WORD* pIdx;

	//インデックスバッファのロック
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	int IndxCount3 = WALL_XVTX + 1;//X

	int IdxCnt = 0;//配列

	int Num = 0;//

	//インデックスの設定
	for (int IndxCount1 = 0; IndxCount1 < WALL_ZVTX; IndxCount1++)
	{
		for (int IndxCount2 = 0; IndxCount2 <= WALL_XVTX; IndxCount2++, IndxCount3++, Num++)
		{
			pIdx[IdxCnt] = IndxCount3;
			pIdx[IdxCnt + 1] = Num;
			IdxCnt +=2;
		}

		if (IndxCount1 < WALL_ZVTX - 1)
		{
			pIdx[IdxCnt] = Num - 1;
			pIdx[IdxCnt + 1] = IndxCount3;
			IdxCnt += 2;
		}
	}

	//インデックスバッファのアンロック
	g_pIdxBuffMeshWall->Unlock();
}

//===============================
//メッシュウォールの終了処理
//===============================ccc
void UninitMeshWall(void)
{
	//テクスチャの解放
	if (g_pTextureMeshWall != NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}

	//頂点バッファの解放
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}

	//インデックスバッファの解放
	if (g_pIdxBuffMeshWall != NULL)
	{
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}

//===============================
//メッシュウォールの更新処理
//===============================
void UpdateMeshWall(void)
{

}

//===============================
//メッシュウォールの描画処理
//===============================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_MeshWall.mtxWorldMeshWall);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshWall.rot.y, g_MeshWall.rot.x, g_MeshWall.rot.z);
	D3DXMatrixMultiply(&g_MeshWall.mtxWorldMeshWall, &g_MeshWall.mtxWorldMeshWall, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_MeshWall.pos.x, g_MeshWall.pos.y, g_MeshWall.pos.z);
	D3DXMatrixMultiply(&g_MeshWall.mtxWorldMeshWall, &g_MeshWall.mtxWorldMeshWall, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshWall.mtxWorldMeshWall);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshWall);

	//テクスチャフォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshWall);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, WALL_VERTEX, 0, WALL_POLYGON);
}
