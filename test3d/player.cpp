//============================
//
// プレイヤー[player.cpp]
// Author:YOSHIDA YUUTO
//
//============================

//****************************
//インクルードファイル
//****************************
#include "player.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "billboard.h"
#include "bullet.h"
#include "particle.h"
#include "block.h"
#include "wall.h"

//****************************
//グローバル変数宣言
//****************************
LPDIRECT3DTEXTURE9 g_apTexturePlayer[128] = {};//プレイヤーのテクスチャへのポインタ
LPD3DXMESH g_pMeshPlayer = NULL;//メッシュ(頂点座標)へのポインタ
LPD3DXBUFFER g_pBuffMatPlayer = NULL;//マテリアルへのポインタ
DWORD g_dwNumMatPlayer = 0;//マテリアルの数
PLAYER g_player;//プレイヤー構造体

//============================
//プレイヤーの初期化処理
//============================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	CAMERA* pCamera = GetCamera();

	g_player.nIdxShadow = SetShadow(D3DXVECTOR3(g_player.pos.x, g_player.pos.y, g_player.pos.z), D3DXVECTOR3(g_player.rot.x, g_player.rot.y, g_player.rot.z));
	g_player.pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);

	//g_player.vtxMinPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_player.vtxMaxPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rotDestPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.bJump = false;
	g_player.bDisp = true;

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\obj2.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer);

	D3DXMATERIAL* pMat;//マテリアルへのポインタ

	//マテリアルのデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//このファイル名を使用してテクスチャを読み込む
				//テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&g_apTexturePlayer[nCntMat]);
		}
	}

	//頂点座標の取得
	int nNumVtx;//頂点数
	DWORD sizeFVF;//頂点フォーマットのサイズ
	BYTE* pVtxBuff;//頂点バッファへのポインタ

	//頂点数の取得
	nNumVtx = g_pMeshPlayer->GetNumVertices();

	//頂点フォーマットのサイズ取得
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshPlayer->GetFVF());

	//頂点バッファのロック
	g_pMeshPlayer->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;

		//頂点座標を比較してブロックの最小値,最大値を取得
		if (vtx.x < g_player.vtxMinPlayer.x)
		{
			g_player.vtxMinPlayer.x = vtx.x;
		}
		else if (vtx.y < g_player.vtxMinPlayer.y)
		{
			g_player.vtxMinPlayer.y = vtx.y;
		}
		else if (vtx.z < g_player.vtxMinPlayer.z)
		{
			g_player.vtxMinPlayer.z = vtx.z;
		}

		else if (vtx.x > g_player.vtxMaxPlayer.x)
		{
			g_player.vtxMaxPlayer.x = vtx.x;
		}

		else if (vtx.y > g_player.vtxMaxPlayer.y)
		{
			g_player.vtxMaxPlayer.y = vtx.y;
		}

		else if (vtx.z > g_player.vtxMaxPlayer.z)
		{
			g_player.vtxMaxPlayer.z = vtx.z;
		}

		//頂点フォーマットのサイズ分ポインタを進める
		pVtxBuff += sizeFVF;
	}

	g_player.Size.x = g_player.vtxMaxPlayer.x - g_player.vtxMinPlayer.x;
	g_player.Size.y = g_player.vtxMaxPlayer.y - g_player.vtxMinPlayer.y;
	g_player.Size.z = g_player.vtxMaxPlayer.z - g_player.vtxMinPlayer.z;

	//頂点バッファのアンロック
	g_pMeshPlayer->UnlockVertexBuffer();

}
//============================
//プレイヤーの終了処理
//============================
void UninitPlayer(void)
{
	for (int nCnt = 0; nCnt < (int)g_dwNumMatPlayer; nCnt++)
	{
		if (g_apTexturePlayer[nCnt] != NULL)
		{
			g_apTexturePlayer[nCnt]->Release();
			g_apTexturePlayer[nCnt] = NULL;
		}
	}

	//メッシュの破棄
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}
}
//============================
//プレイヤーの更新処理
//============================
void UpdatePlayer(void)
{
	CAMERA* pCamera = GetCamera();

	if (g_player.bDisp == true)
	{
		SetPositionShadow(g_player.nIdxShadow, D3DXVECTOR3(g_player.pos.x, 1.0f, g_player.pos.z));
	}

	if (GetKeyboardPress(DIK_A) == true)
	{
		//プレイヤーの移動(上)
		if (GetKeyboardPress(DIK_W) == true)
		{
			g_player.move.x += sinf(pCamera->rot.y - D3DX_PI * 0.25f) * PLAYER_MOVE;
			g_player.move.z += cosf(pCamera->rot.y - D3DX_PI * 0.25f) * PLAYER_MOVE;

			g_player.rotDestPlayer.y = pCamera->rot.y + D3DX_PI * 0.75f;
		}
		//プレイヤーの移動(下)
		else if (GetKeyboardPress(DIK_S) == true)
		{
			g_player.move.x += sinf(pCamera->rot.y - D3DX_PI * 0.75f) * PLAYER_MOVE;
			g_player.move.z += cosf(pCamera->rot.y - D3DX_PI * 0.75f) * PLAYER_MOVE;

			g_player.rotDestPlayer.y = pCamera->rot.y + D3DX_PI * 0.25f;
		}
		//プレイヤーの移動(左)
		else
		{
			g_player.move.z += sinf(pCamera->rot.y) * PLAYER_MOVE;
			g_player.move.x -= cosf(pCamera->rot.y) * PLAYER_MOVE;

			g_player.rotDestPlayer.y = pCamera->rot.y + D3DX_PI * 0.5f;

			//if (g_player.rotDestPlayer.y < D3DX_PI * 2.0f)
			//{
			//	g_player.rotDestPlayer.y -= D3DX_PI;
			//}
		}

	}
	//プレイヤーの移動(右)
	else if (GetKeyboardPress(DIK_D) == true)
	{
		//プレイヤーの移動(上)
		if (GetKeyboardPress(DIK_W) == true)
		{
			g_player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.25f) * PLAYER_MOVE;
			g_player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.25f) * PLAYER_MOVE;

			g_player.rotDestPlayer.y = pCamera->rot.y - D3DX_PI * 0.75f;
		}
		//プレイヤーの移動(下)
		else if (GetKeyboardPress(DIK_S) == true)
		{
			g_player.move.x += sinf(pCamera->rot.y + D3DX_PI * 0.75f) * PLAYER_MOVE;
			g_player.move.z += cosf(pCamera->rot.y + D3DX_PI * 0.75f) * PLAYER_MOVE;

			g_player.rotDestPlayer.y = pCamera->rot.y - D3DX_PI * 0.25f;
		}
		//プレイヤーの移動(右)
		else
		{
			g_player.move.z -= sinf(pCamera->rot.y) * PLAYER_MOVE;
			g_player.move.x += cosf(pCamera->rot.y) * PLAYER_MOVE;

			g_player.rotDestPlayer.y = pCamera->rot.y - D3DX_PI * 0.5f;
		}

	}
	//プレイヤーの移動(上)
	else if (GetKeyboardPress(DIK_W) == true)
	{
		g_player.move.x += sinf(pCamera->rot.y) * PLAYER_MOVE;
		g_player.move.z += cosf(pCamera->rot.y) * PLAYER_MOVE;

		g_player.rotDestPlayer.y = pCamera->rot.y + D3DX_PI;

		//pCamera->posV.z += PLAYER_MOVE;
		//pCamera->posR.z += PLAYER_MOVE;
	}
	//プレイヤーの移動(下)
	else if (GetKeyboardPress(DIK_S) == true)
	{
		g_player.move.x -= sinf(pCamera->rot.y) * PLAYER_MOVE;
		g_player.move.z -= cosf(pCamera->rot.y) * PLAYER_MOVE;

		g_player.rotDestPlayer.y = pCamera->rot.y;

		//pCamera->posV.z -= PLAYER_MOVE;
		//pCamera->posR.z -= PLAYER_MOVE;
	}

	//移動量を減衰
	g_player.move.x += (0.0f - g_player.move.x) * 0.25f;
	//g_player.move.y += (0.0f - g_player.move.y) * 0.25f;
	g_player.move.z += (0.0f - g_player.move.z) * 0.25f;

	//前回の位置を保存
	g_player.posOld = g_player.pos;

	//プレイヤーの位置の更新
	g_player.pos += g_player.move;

	//プレイヤーの重力ddd
	g_player.move.y -= 1.0f;

	if (CollisionBlock() == true)
	{
		g_player.bJump = true;
	}
	else
	{
		g_player.bJump = false;
	}
	
	CollisionWall();

	//着地
	if (g_player.pos.y <= 0.0f)
	{
		g_player.pos.y = 0.0f;
		g_player.bJump = true;
	}

	if (KeyboardTrigger(DIK_SPACE) == true && g_player.bJump == true)
	{
		g_player.move.y = 15.0f;
		g_player.bJump = false;
	}

	if (g_player.rotDestPlayer.y - g_player.rot.y >= D3DX_PI)
	{
		g_player.rot.y += D3DX_PI * 2.0f;
	}
	else if (g_player.rotDestPlayer.y - g_player.rot.y <= -D3DX_PI)
	{
		g_player.rot.y -= D3DX_PI * 2.0f;
	}

	if (KeyboardTrigger(DIK_RETURN) == true)
	{
		SetBullet(D3DXVECTOR3(g_player.pos.x, g_player.pos.y + 20, g_player.pos.z),//pos
			D3DXVECTOR3(0.0f, 0.0f, 0.0f),//dir
			D3DXVECTOR3(sinf(g_player.rot.y + D3DX_PI) * 5.0f, 0.0f, cosf(g_player.rot.y + D3DX_PI) * 5.0f),//move
			50);//life

		SetParticle(g_player.pos, 50, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	}

	g_player.rot.y += (g_player.rotDestPlayer.y - g_player.rot.y) * 0.1f;
}
//============================
//プレイヤーの描画処理
//============================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans,mtxSize;

	D3DMATERIAL9 matDef;//現在のマテリアル保存用

	D3DXMATERIAL* pMat;//マテリアルデータへのポインタ

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_player.mtxWorldPlayer);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorldPlayer, &g_player.mtxWorldPlayer, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorldPlayer, &g_player.mtxWorldPlayer, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorldPlayer);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルのデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_apTexturePlayer[nCntMat]);//今はNULL

		//モデル(パーツ)の描画
		g_pMeshPlayer->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを元に戻す
	pDevice->SetMaterial(&matDef);
}
//============================
//プレイヤーの取得処理
//============================
PLAYER* GetPlayer(void)
{
	return &g_player;
}
