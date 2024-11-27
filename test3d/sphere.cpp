//=================================
//
// メッシュスフィア [meshsphere.cpp]
// Author:YOSHIDA YUUTO
//
//=================================

//****************************
//インクルードファイル
//****************************
#include "sphere.h"
#include "input.h"

//****************************
//グローバル変数宣言
//****************************
LPDIRECT3DTEXTURE9 g_pTextureMeshSphere = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshSphere = NULL; //頂点バッファへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshSphere = NULL;//インデックスバッファへのポインタ
MESHSPHERE g_MeshSphere;
D3DPRIMITIVETYPE pType;

//===============================
//メッシュウォールの初期化処理
//===============================
void InitMeshSphere(void)
{
	int nCnt = 0;

	LPDIRECT3DDEVICE9 pDevice;//デバイスへのポインタ

	pDevice = GetDevice();//デバイスを取得

		//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&g_pTextureMeshSphere);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshSphere,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * 8,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshSphere,
		NULL);

	g_MeshSphere.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshSphere.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pType = D3DPT_TRIANGLEFAN;

	VERTEX_3D* pVtx = NULL;

	//頂点バッファをロック
	g_pVtxBuffMeshSphere->Lock(0, 0, (void**)&pVtx, 0);

	float fTexX = 1.0f / SPHERE_XVTX;
	float fTexY = 1.0f / SPHERE_ZVTX;

	D3DXVECTOR3 nor;

	int radius = 500;

	//縦
	for (int nCntV = 0; nCntV < SPHERE_ZVTX + 1; nCntV++)
	{
		//横
		for (int nCntH = 0; nCntH < SPHERE_XVTX + 1; nCntH++)
		{
			float fAngel = (D3DX_PI * 2.0f) / SPHERE_XVTX * nCntH;

			////頂点座標の設定
			//pVtx[nCnt].Pos = D3DXVECTOR3(
			//);

			//nor = pVtx[nCnt].Pos - g_MeshSphere.pos;

			////法線ベクトルの設定
			//pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			////頂点カラーの設定
			//pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			////テクスチャ座標の設定
			//pVtx[nCnt].tex = D3DXVECTOR2(fTexX * nCntH, nCntV * fTexY);

			nCnt++;//加算

		}
	}

	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		//float fAngleSp = (D3DX_PI * 2.0f) / 5 * nCnt;
		//
		//pVtx[nCntSp].Pos = D3DXVECTOR3(sinf(fAngleSp) * 100.0f, 80.0f, cosf(fAngleSp) * 100.0f);

		//法線ベクトルの設定
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の設定
		pVtx[nCnt].tex = D3DXVECTOR2(fTexX * nCnt, nCnt * fTexY);
	}

	if (pType == D3DPT_TRIANGLEFAN)
	{

		pVtx[0].Pos = D3DXVECTOR3(0.0f, 200.0f, 0.0f);

		pVtx[1].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 0) * 100.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 0) * 100.0f);
		pVtx[2].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 1) * 100.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 1) * 100.0f);
		pVtx[3].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 2) * 100.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 2) * 100.0f);
		pVtx[4].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 3) * 100.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 3) * 100.0f);
		pVtx[5].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 4) * 100.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 4) * 100.0f);
		pVtx[6].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 5) * 100.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 5) * 100.0f);
		pVtx[7].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 6) * 100.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 6) * 100.0f);
	}
	else if (pType == D3DPT_TRIANGLESTRIP)
	{
		pVtx[8].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 0) * 50.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 0) * 50.0f);
		pVtx[9].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 1) * 0.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 1) * 0.0f);
		pVtx[10].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 2) * 0.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 2) * 0.0f);
		pVtx[11].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 3) * 0.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 3) * 0.0f);
		pVtx[12].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 4) * 0.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 4) * 0.0f);
		pVtx[13].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 5) * 0.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 5) * 0.0f);
		pVtx[14].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 6) * 0.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 6) * 0.0f);
		pVtx[15].Pos = D3DXVECTOR3(sinf((D3DX_PI * 2.0f) / 6 * 7) * 0.0f, 80.0f, cosf((D3DX_PI * 2.0f) / 6 * 7) * 0.0f);
	}
	g_pVtxBuffMeshSphere->Unlock();

	WORD* pIdx;

	//インデックスバッファのロック
	g_pIdxBuffMeshSphere->Lock(0, 0, (void**)&pIdx, 0);

	int IndxCount3 = SPHERE_XVTX + 1;//X

	int IdxCnt = 0;//配列

	int Num = 0;//

	////インデックスの設定
	//for (int IndxCount1 = 0; IndxCount1 < SPHERE_ZVTX; IndxCount1++)
	//{
	//	for (int IndxCount2 = 0; IndxCount2 <= SPHERE_XVTX; IndxCount2++, IndxCount3++, Num++)
	//	{
	//		pIdx[IdxCnt] = IndxCount3;
	//		pIdx[IdxCnt + 1] = Num;
	//		IdxCnt += 2;
	//	}

	//	if (IndxCount1 < SPHERE_ZVTX - 1)
	//	{
	//		pIdx[IdxCnt] = Num - 1;
	//		pIdx[IdxCnt + 1] = IndxCount3;
	//		IdxCnt += 2;
	//	}
	//}

	pIdx[0] = 0;
	pIdx[1] = 1;
	pIdx[2] = 2;
	pIdx[3] = 3;
	pIdx[4] = 4;
	pIdx[5] = 5;
	pIdx[6] = 6;
	pIdx[7] = 7;
	pIdx[8] = 8;
	pIdx[9] = 9;
	pIdx[10] = 10;
	pIdx[11] = 11;
	pIdx[12] = 12;
	pIdx[13] = 13;
	pIdx[14] = 14;
	pIdx[15] = 15;


	//インデックスバッファのアンロック
	g_pIdxBuffMeshSphere->Unlock();
}

//===============================
//メッシュウォールの終了処理
//===============================ccc
void UninitMeshSphere(void)
{
	//テクスチャの解放
	if (g_pTextureMeshSphere != NULL)
	{
		g_pTextureMeshSphere->Release();
		g_pTextureMeshSphere = NULL;
	}

	//頂点バッファの解放
	if (g_pVtxBuffMeshSphere != NULL)
	{
		g_pVtxBuffMeshSphere->Release();
		g_pVtxBuffMeshSphere = NULL;
	}

	//インデックスバッファの解放
	if (g_pIdxBuffMeshSphere != NULL)
	{
		g_pIdxBuffMeshSphere->Release();
		g_pIdxBuffMeshSphere = NULL;
	}
}

//===============================
//メッシュウォールの更新処理
//===============================
void UpdateMeshSphere(void)
{
	if (KeyboardTrigger(DIK_L))
	{
		pType = D3DPT_TRIANGLESTRIP;
	}
}

//===============================
//メッシュウォールの描画処理
//===============================
void DrawMeshSphere(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_MeshSphere.mtxWorldMeshSphere);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshSphere.rot.y, g_MeshSphere.rot.x, g_MeshSphere.rot.z);
	D3DXMatrixMultiply(&g_MeshSphere.mtxWorldMeshSphere, &g_MeshSphere.mtxWorldMeshSphere, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_MeshSphere.pos.x, g_MeshSphere.pos.y, g_MeshSphere.pos.z);
	D3DXMatrixMultiply(&g_MeshSphere.mtxWorldMeshSphere, &g_MeshSphere.mtxWorldMeshSphere, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshSphere.mtxWorldMeshSphere);

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshSphere, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshSphere);

	//テクスチャフォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshSphere);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLEFAN, 0, 0, 16, 0, 16);

	if (pType == D3DPT_TRIANGLESTRIP)
	{
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, 16, 0, 16);
	}
}
