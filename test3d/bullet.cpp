//============================
//
// 弾[billboard.cpp]
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

//****************************
//マクロ定義
//****************************
#define BULLET_WIDTH (25.0f) //横幅
#define BULLET_HEIGHT (25.0f) //高さ
#define MAX_BULLET (128) //弾の最大数
#define MAX_MOVE (5.0f) //移動量

//****************************
//グローバル変数宣言
//****************************
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL; //頂点バッファへのポインタ
BULLET g_Bullet[MAX_BULLET];

//============================
//弾の初期化処理
//============================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_pTextureBullet);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_3D* pVtx = NULL;

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		g_Bullet[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCnt].nLife = 0;
		g_Bullet[nCnt].bUse = false;
	}
	
	//頂点バッファをロック
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].Pos = D3DXVECTOR3(g_Bullet[nCnt].pos.x - BULLET_WIDTH, g_Bullet[nCnt].pos.y + BULLET_HEIGHT, 0.0f);
		pVtx[1].Pos = D3DXVECTOR3(g_Bullet[nCnt].pos.x + BULLET_WIDTH, g_Bullet[nCnt].pos.y + BULLET_HEIGHT, 0.0f);
		pVtx[2].Pos = D3DXVECTOR3(g_Bullet[nCnt].pos.x - BULLET_WIDTH, g_Bullet[nCnt].pos.y - BULLET_HEIGHT, 0.0f);
		pVtx[3].Pos = D3DXVECTOR3(g_Bullet[nCnt].pos.x + BULLET_WIDTH, g_Bullet[nCnt].pos.y - BULLET_HEIGHT, 0.0f);

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
	g_pVtxBuffBullet->Unlock();
}
//============================
//弾の終了処理
//============================
void UninitBullet(void)
{
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//頂点バッファの解放
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}
//============================
//弾の更新処理
//============================
void UpdateBullet(void)
{
	PLAYER* pPlayer = GetPlayer();

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		//使用されている
		if (g_Bullet[nCnt].bUse == true)
		{	
			g_Bullet[nCnt].pos += g_Bullet[nCnt].move;
			
			g_Bullet[nCnt].nLife--;

			SetEffect(g_Bullet[nCnt].pos, D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 30,D3DXVECTOR3(1.0f,1.0f,1.0f));
			SetPositionShadow(g_Bullet[nCnt].nIdxShadow, D3DXVECTOR3(g_Bullet[nCnt].pos.x, 1.0f, g_Bullet[nCnt].pos.z));

			//寿命が尽きた
			if (g_Bullet[nCnt].nLife <= 0)
			{
				g_Bullet[nCnt].bUse = false;
				EnableShadow(g_Bullet[nCnt].nIdxShadow);//影の使用状態

				SetExplosion(g_Bullet[nCnt].pos);
			}
		}
	}
}
//============================
//弾の描画処理
//============================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	CAMERA* pCamera = GetCamera();

	//アルファテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, NULL);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	//ライトを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//計算用のマトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxView;

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		if (g_Bullet[nCnt].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Bullet[nCnt].mtxWorld);

			pDevice->GetTransform(D3DTS_VIEW, &mtxView);//ビューマトリックスの取得

			//カメラの逆行列の設定
			g_Bullet[nCnt].mtxWorld._11 = mtxView._11;
			g_Bullet[nCnt].mtxWorld._12 = mtxView._21;
			g_Bullet[nCnt].mtxWorld._13 = mtxView._31;
			g_Bullet[nCnt].mtxWorld._21 = mtxView._12;
			g_Bullet[nCnt].mtxWorld._22 = mtxView._22;
			g_Bullet[nCnt].mtxWorld._23 = mtxView._32;
			g_Bullet[nCnt].mtxWorld._31 = mtxView._13;
			g_Bullet[nCnt].mtxWorld._32 = mtxView._23;
			g_Bullet[nCnt].mtxWorld._33 = mtxView._33;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Bullet[nCnt].pos.x + pCamera->rot.y, g_Bullet[nCnt].pos.y + pCamera->rot.y, g_Bullet[nCnt].pos.z + pCamera->rot.y);
			D3DXMatrixMultiply(&g_Bullet[nCnt].mtxWorld, &g_Bullet[nCnt].mtxWorld, &mtxTrans);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Bullet[nCnt].mtxWorld);

			//頂点バッファをデバイスのデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			//テクスチャフォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBullet);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt * 4, 2);
		}
	}

	//アルファテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	//ライトを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//============================
//弾の描画処理
//============================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 dir, D3DXVECTOR3 move, int nLife)
{
	VERTEX_3D* pVtx = NULL;

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		if (g_Bullet[nCnt].bUse == false)
		{
			g_Bullet[nCnt].nIdxShadow = SetShadow(D3DXVECTOR3(g_Bullet[nCnt].pos.x, 1.0f, g_Bullet[nCnt].pos.z) ,D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			
			g_Bullet[nCnt].pos = pos;
			g_Bullet[nCnt].move = move;
			g_Bullet[nCnt].dir = dir;
			g_Bullet[nCnt].nLife = nLife;
			g_Bullet[nCnt].bUse = true;

			break;
		}
	}
}
