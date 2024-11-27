//============================
//
// ブロック[block.cpp]
// Author:YOSHIDA YUUTO
//
//============================

//****************************
//インクルードファイル
//****************************
#include "block.h"

//****************************
//グローバル変数宣言
//****************************
LPDIRECT3DTEXTURE9 g_apTextureBlock[128] = {};
LPD3DXMESH g_pMeshBlock = NULL;//メッシュ(頂点座標)へのポインタ
LPD3DXBUFFER g_pBuffMatBlock = NULL;//マテリアルへのポインタ
DWORD g_dwNumMatBlock = 0;//マテリアルの数
BLOCK g_Block;

//=============================
//ブロックの初期化処理
//=============================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	g_Block.pos = D3DXVECTOR3(-100.0f, 50.0f, 0.0f);
	g_Block.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Block.Scal = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	//g_Block.vtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_Block.vtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\obj.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatBlock,
		NULL,
		&g_dwNumMatBlock,
		&g_pMeshBlock);

	D3DXMATERIAL* pMat;//マテリアルへのポインタ

	//マテリアルのデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatBlock->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatBlock; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//このファイル名を使用してテクスチャを読み込む
				//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTextureBlock[nCntMat]);
		}
	}

	//頂点座標の取得
	int nNumVtx;//頂点数
	DWORD sizeFVF;//頂点フォーマットのサイズ
	BYTE* pVtxBuff;//頂点バッファへのポインタ

	//頂点数の取得
	nNumVtx = g_pMeshBlock->GetNumVertices();

	//頂点フォーマットのサイズ取得
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshBlock->GetFVF());

	//頂点バッファのロック
	g_pMeshBlock->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//頂点座標を比較してブロックの最小値,最大値を取得
		if (vtx.x < g_Block.vtxMin.x)
		{
			g_Block.vtxMin.x = vtx.x;
		}
		else if (vtx.y < g_Block.vtxMin.y)
		{
			g_Block.vtxMin.y = vtx.y;
		}
		else if (vtx.z < g_Block.vtxMin.z)
		{
			g_Block.vtxMin.z = vtx.z;
		}
		else if (vtx.x > g_Block.vtxMax.x)
		{
			g_Block.vtxMax.x = vtx.x;
		}
		else if (vtx.y > g_Block.vtxMax.y)
		{
			g_Block.vtxMax.y = vtx.y;
		}
		else if (vtx.z > g_Block.vtxMax.z)
		{
			g_Block.vtxMax.z = vtx.z;
		}

		//頂点フォーマットのサイズ分ポインタを進める
		pVtxBuff += sizeFVF;
	}

	g_Block.Size.x = g_Block.vtxMax.x - g_Block.vtxMin.x;
	g_Block.Size.y = g_Block.vtxMax.y - g_Block.vtxMin.y;
	g_Block.Size.z = g_Block.vtxMax.z - g_Block.vtxMin.z;

	//頂点バッファのアンロック
	g_pMeshBlock->UnlockVertexBuffer();

}
//=============================
//ブロックの終了処理
//=============================
void UninitBlock(void)
{
	//メッシュの破棄
	if (g_pMeshBlock != NULL)
	{
		g_pMeshBlock->Release();
		g_pMeshBlock = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatBlock != NULL)
	{
		g_pBuffMatBlock->Release();
		g_pBuffMatBlock = NULL;
	}
}
//=============================
//ブロックの更新処理
//=============================
void UpdateBlock(void)
{
	//今はなし
}
//=============================
//ブロックの描画処理
//=============================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxScal;

	D3DMATERIAL9 matDef;//現在のマテリアル保存用

	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Block.mtxWorldBlock);

	//大きさを反映
	D3DXMatrixScaling(&mtxScal, g_Block.Scal.x, g_Block.Scal.y, g_Block.Scal.z);
	D3DXMatrixMultiply(&g_Block.mtxWorldBlock, &g_Block.mtxWorldBlock, &mtxScal);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Block.rot.y, g_Block.rot.x, g_Block.rot.z);
	D3DXMatrixMultiply(&g_Block.mtxWorldBlock, &g_Block.mtxWorldBlock, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Block.pos.x, g_Block.pos.y, g_Block.pos.z);
	D3DXMatrixMultiply(&g_Block.mtxWorldBlock, &g_Block.mtxWorldBlock, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Block.mtxWorldBlock);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルのデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatBlock->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatBlock; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureBlock[nCntMat]);

		//ブロック(パーツ)の描画
		g_pMeshBlock->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを元に戻す
	pDevice->SetMaterial(&matDef);
}
//=======================
//ブロックの判定処理
//=======================
bool CollisionBlock(void)
{
	PLAYER* pPlayer = GetPlayer();

	bool bLanding = false;

	if (pPlayer->posOld.y < g_Block.pos.y + g_Block.Size.y
		&&pPlayer->posOld.y + pPlayer->Size.y > g_Block.pos.y)
	{
		//左右のめり込み判定
		if (pPlayer->pos.z - pPlayer->Size.z * 0.5f < g_Block.pos.z + g_Block.Size.z * 0.5f
			&& pPlayer->pos.z + pPlayer->Size.z * 0.5f > g_Block.pos.z - g_Block.Size.z * 0.5f)
		{
			//xが左から右にめり込んだ	
			if (pPlayer->posOld.x + pPlayer->Size.x * 0.5f < g_Block.pos.x - g_Block.Size.x * 0.5f
				&& pPlayer->pos.x + pPlayer->Size.x * 0.5f > g_Block.pos.x - g_Block.Size.x * 0.5f)
			{
				pPlayer->pos.x = g_Block.pos.x - g_Block.Size.x * 0.5f - pPlayer->Size.x * 0.5f - 0.1f;
			}
			//xが右から左にめり込んだ	
			else if (pPlayer->posOld.x - pPlayer->Size.x * 0.5f > g_Block.pos.x + g_Block.Size.x * 0.5f
				&& pPlayer->pos.x - pPlayer->Size.x * 0.5f < g_Block.pos.x + g_Block.Size.x * 0.5f)
			{
				pPlayer->pos.x = g_Block.pos.x + g_Block.Size.x * 0.5f +  pPlayer->Size.x * 0.5f + 0.1f;
			}
		}

		//前と後ろの判定
		if (pPlayer->pos.x - pPlayer->Size.x * 0.5f < g_Block.pos.x + g_Block.Size.x * 0.5f
			&& pPlayer->pos.x + pPlayer->Size.x * 0.5f > g_Block.pos.x - g_Block.Size.x * 0.5f)
		{
			//zが前方からめり込んだ
			if (pPlayer->posOld.z + pPlayer->Size.z * 0.5f < g_Block.pos.z - g_Block.Size.z * 0.5f
				&& pPlayer->pos.z + pPlayer->Size.z * 0.5f > g_Block.pos.z - g_Block.Size.z * 0.5f)
			{
				pPlayer->pos.z = g_Block.pos.z - g_Block.Size.z * 0.5f - pPlayer->Size.z * 0.5f - 0.1f;
			}
			//zが後方からめり込んだ
			else if (pPlayer->posOld.z - pPlayer->Size.z * 0.5f > g_Block.pos.z + g_Block.Size.z * 0.5f
				&& pPlayer->pos.z - pPlayer->Size.z * 0.5f < g_Block.pos.z + g_Block.Size.z * 0.5f)
			{
				pPlayer->pos.z = g_Block.pos.z + pPlayer->Size.z + 0.1f;
			}
		}
	}

	if (pPlayer->pos.x - pPlayer->Size.x * 0.5f < g_Block.pos.x + g_Block.Size.x * 0.5f
		&& pPlayer->pos.x + pPlayer->Size.x * 0.5f > g_Block.pos.x - g_Block.Size.x * 0.5f)
	{
		if (pPlayer->pos.z - pPlayer->Size.z * 0.5f < g_Block.pos.z + g_Block.Size.z * 0.5f
			&& pPlayer->pos.z + pPlayer->Size.z * 0.5f > g_Block.pos.z - g_Block.Size.z * 0.5f)
		{
			//上から下
			if (pPlayer->posOld.y >= g_Block.pos.y + g_Block.Size.y
				&& pPlayer->pos.y < g_Block.pos.y + g_Block.Size.y)
			{
				bLanding = true;
				pPlayer->pos.y = g_Block.pos.y + g_Block.Size.y * 0.5f + pPlayer->Size.y * 0.45f + 0.1f;
				pPlayer->move.y = 0.0f;
			}
			//下から上
			else if (pPlayer->posOld.y + pPlayer->Size.y * 0.5f < g_Block.pos.y - g_Block.Size.y * 0.5f
				&& pPlayer->pos.y + pPlayer->Size.y * 0.5f > g_Block.pos.y - g_Block.Size.y * 0.5f)
			{
				pPlayer->pos.y = g_Block.pos.y - pPlayer->Size.y;
				pPlayer->move.y = 0.0f;
			}

		}
	}
	return bLanding;
}