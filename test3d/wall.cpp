//============================
//
// 壁[wall.cpp]
// Author:YOSHIDA YUUTO
//
//============================

//****************************
//インクルードファイル
//****************************
#include "wall.h"
#include "player.h"

//****************************
//マクロ定義
//****************************
#define MAX_WALL (4) //壁の最大数

//****************************
//グローバル変数宣言
//****************************
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL; //頂点バッファへのポインタ
//D3DXVECTOR3 g_posWall; //位置
//D3DXVECTOR3 g_rotWall; //向き
//D3DXMATRIX g_mtxWorldWall;//ワールドマトリックス
WALL g_Wall[MAX_WALL];//壁の構造体

//=============================
//壁の初期化処理
//=============================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\wall000.jpg",
		&g_pTextureWall);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	VERTEX_3D* pVtx = NULL;

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		g_Wall[nCntWall].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCntWall].vecLine = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCntWall].vecPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCntWall].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Wall[nCntWall].fA = 1.0f;
		g_Wall[nCntWall].fWidth = 0.0f;
		g_Wall[nCntWall].fHeight = 0.0f;
		g_Wall[nCntWall].bUse = false;
		g_Wall[nCntWall].fScal = D3DXVECTOR3(0.0f,0.0f,0.0f);//基準を決める
	}

	//頂点バッファをロック
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		//頂点座標の設定
		pVtx[0].Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		pVtx[1].Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		pVtx[2].Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		pVtx[3].Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);

		//各頂点の法線の設定(ベクトルの大きさは１にする必要がある)
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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

	g_pVtxBuffWall->Unlock();
}
//=============================
//壁の終了処理
//=============================
void UninitWall(void)
{
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//頂点バッファの解放
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}
}
//=============================
//壁の更新処理
//=============================
void UpdateWall(void)
{
	
}
//=============================
//壁の描画処理
//=============================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans,mtxScal;

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Wall[nCntWall].mtxWorld);

			////大きさを反映
			//D3DXMatrixScaling(&mtxScal, g_Wall[nCntWall].fScal.x, g_Wall[nCntWall].fScal.y, g_Wall[nCntWall].fScal.z);
			//D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorld, &g_Wall[nCntWall].mtxWorld, &mtxScal);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[nCntWall].rot.y, g_Wall[nCntWall].rot.x, g_Wall[nCntWall].rot.z);
			D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorld, &g_Wall[nCntWall].mtxWorld, &mtxRot);

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Wall[nCntWall].pos.x, g_Wall[nCntWall].pos.y, g_Wall[nCntWall].pos.z);
			D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorld, &g_Wall[nCntWall].mtxWorld, &mtxTrans);
			
			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Wall[nCntWall].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

			//テクスチャフォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureWall);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWall * 4, 2);
		}
	}
}
//=============================
//壁の設定処理
//=============================
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float fA,float fWidth,float fHeight)
{
	VERTEX_3D* pVtx;

	int nCntWall;

	//頂点バッファをロック
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		if (g_Wall[nCntWall].bUse == false)
		{
			g_Wall[nCntWall].pos = pos;
			g_Wall[nCntWall].fWidth = fWidth;
			g_Wall[nCntWall].fHeight = fHeight;
			g_Wall[nCntWall].fA = fA;
			g_Wall[nCntWall].rot = rot;

			g_Wall[nCntWall].bUse = true;

			//頂点座標の設定
			pVtx[0].Pos = D3DXVECTOR3(0.0f, fHeight, 0.0f);
			pVtx[1].Pos = D3DXVECTOR3(fWidth * 2.0f, fHeight, 0.0f);
			pVtx[2].Pos = D3DXVECTOR3(0.0f, -fHeight, 0.0f);
			pVtx[3].Pos = D3DXVECTOR3(fWidth * 2.0f, -fHeight, 0.0f);

			//各頂点の法線の設定(ベクトルの大きさは１にする必要がある)
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fA);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fA);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fA);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fA);

			//テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			break;
		}
		pVtx += 4;
	}

	g_pVtxBuffWall->Unlock();
}
//==========================
//壁との衝突判定
//==========================
void CollisionWall(void)
{
	VERTEX_3D* pVtx;

	PLAYER* pPlayer = GetPlayer();

	//頂点バッファをロック
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_WALL; nCnt++)
	{
		int nCntNext = (nCnt + 1) % MAX_WALL;

		if (g_Wall[nCnt].bUse == true && g_Wall[nCntNext].bUse == true)
		{
			D3DXVECTOR3 pos = g_Wall[nCnt].pos;

			//計算用
			D3DXVECTOR3 vecA, vecB;

			D3DXVECTOR3 PlayerVecPos(pPlayer->pos.x,0.0f,pPlayer->pos.z);

			vecA = g_Wall[nCntNext].pos - pos;

			D3DXVec3Normalize(&vecA,&vecA);

			vecB = PlayerVecPos - pos;

			D3DXVec3Normalize(&vecB, &vecB);

			D3DXVECTOR3 Cross = {};

			D3DXVec3Cross(&Cross, &vecA, &vecB);

			if (Cross.y < 0.0f)
			{
				pPlayer->pos = pPlayer->posOld;
				pPlayer->move.z = 0.0f;
			}
		}
	}

	//頂点バッファをアンロック
	g_pVtxBuffWall->Unlock();
}
