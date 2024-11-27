//============================
//
// メイン[main.cpp]
// Author:YOSHIDA YUUTO
//
//============================

//****************************
//インクルードファイル
//****************************
#include "main.h"
#include "polygon.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "input.h"
#include<stdio.h>
#include "player.h"
#include "shadow.h"
#include "wall.h"
#include "bullet.h"
#include "effect.h"
#include "explosion.h"
#include "particle.h"
#include "meshfield.h"
#include "meshwall.h"
#include "sphere.h"
#include "block.h"

//****************************
//グローバル変数宣言
//****************************
bool g_isFullscreen = false;            //ウィンドウを切り替えるためのフラグ
RECT g_windowRect;                      //ウィンドウを切り替えるための変数
LPDIRECT3D9 g_pD3D = NULL;//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;//Direct3Dデバイスへのポインタ
MODE g_mode = MODE_TITLE;//現在のモード
LPD3DXFONT g_pFont = NULL;//フォントへのポインタ
int g_nCountFPS = 0;//FPSカウンター

//===================================
//メイン関数
//===================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);//メモリーリーク検知用フラグ
	DWORD dwCurrentTime;//現在時刻
	DWORD dwExecLastTime = timeGetTime();//最後に処理した時刻

	//分解能を設定
	timeBeginPeriod(1);

	dwCurrentTime = 0;//初期化する
	dwExecLastTime = timeGetTime();//現在時刻保存

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,        //ウインドウのスタイル
		WindowProc,        //ウインドウプロシージャ
		0,                 //0にする(通常は使用しない)
		0,                 //0にする(通常は使用しない)
		hInstance,         //インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),//タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),//クライアント領域の色
		NULL,//メニューバー
		CLASS_NAME,//ウインドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)//ファイルのアイコン
	};
	HWND hWnd;//ウインドウのハンドル

	MSG msg;

	//ウインドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定サイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウインドウを生成
	hWnd = CreateWindowEx(0,//拡張ウィンドウスタイル
		CLASS_NAME,           //ウインドウクラスの名前
		WINDOW_NAME,          //ウインドウの名前
		WS_OVERLAPPEDWINDOW,  //ウインドウのスタイル
		CW_USEDEFAULT,        //ウインドウ左上X座標
		CW_USEDEFAULT,        //ウインドウ左上Y座標
		(rect.right - rect.left),//ウインドウ左上x座標幅
		(rect.bottom - rect.top),//ウインドウ左上Y座標高さ
		NULL,                 //親ウインドウのハンドル
		NULL,                 //メニューハンドルまたはウインドウID
		hInstance,            //インスタンスハンドル
		NULL);                 //ウインドウ作成データ

		//ウインドウの表示
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);//ウインドウの表示状態を設定
	UpdateWindow(hWnd);            //クライアント領域を更新

	DWORD dwFrameCount;//フレームカウント
	DWORD dwFPSLastTime;//最後にFPSを計測した時間

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//初期化処理が失敗した場合
		return -1;
	}
	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windowsの処理
			if (msg.message == WM_QUIT)
			{//WM_QUITメッセージを受け取ったらループを抜ける
				break;
			}
			else
			{
				TranslateMessage(&msg);//仮想キーメッセージを文字メッセージへ変換
				DispatchMessage(&msg); //ウインドウプロシージャへメッセージを送出
			}
		}
		else
		{
			//DirectXの処理
			//メッセージの設定
			dwCurrentTime = timeGetTime();//現在時刻

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5秒経過
				//FPSを計測
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;//FPSを計測した時刻を保存
				dwFrameCount = 0;//フレームカウントをクリア

			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60分の1秒経過
				dwExecLastTime = dwCurrentTime;//処理開始の時刻(現在時刻)を保存

				dwFrameCount++;//フレームカウントを加算

				//更新処理
				Update();

				//描画処理
				Draw();
			}
			
		}
		
	}
	//終了処理
	Uninit();

	//ウインドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);


	return(int)msg.wParam;
}
//=======================
//ウインドウプロシージャ
//=======================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//HDC hDC;//デバイスコンテキスト(GDIオブジェクト)のハンドル

	const RECT rect = { 0,0, SCREEN_WIDTH,SCREEN_HEIGHT };//ウインドウの領域

	switch (uMsg)
	{
	case WM_DESTROY: //ウインドウの破棄メッセージ
		//WM_QUITへメッセージを送る
		ReleaseDInputMouse();	// DirectInput(Mouse)オブジェクトの開放
		ReleaseDInput();		// DirectInputオブジェクトの開放
		PostQuitMessage(0);
		break;
	case WM_ACTIVATE:	// アクティブ時：1　非アクティブ時：0
		if (wParam == 0) {
			// 非アクティブになった場合
			ReleaseDInputMouse();
		}
		return 0L;
	case WM_SETCURSOR:	// カーソルの設定
		SetCursor(NULL);
		return TRUE;
	case WM_KEYDOWN: //キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE://[Esc]キー押された
			DestroyWindow(hWnd);
			break;
		case VK_F11:
			ToggleFullscreen(hWnd);//F11でフルスクリーン
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);    //既定の処理を返す
}
//========================
//初期化処理
//========================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{

	D3DDISPLAYMODE d3ddm; //ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp; //プレゼンテーションパラメータ

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));//パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;//ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;//バックバッファの形式
	d3dpp.BackBufferCount = 1;//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//バックバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;//ウインドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//インターバル

	//Direct3Dデバイスの生成描画処理と頂点処理をハードウェアで行う
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}
	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//デバック表示用フォントの生成
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0,
		FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFont);

	//キーボードの初期化処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	if (FAILED(InitDInput(hInstance, hWnd)))
	{
		return E_FAIL;
	}
	//ジョイパッドの初期化処理
	if (FAILED(InitJoypad()))
	{
		return E_FAIL;
	}

//*************************
//関数の初期化
//*************************
	////ポリゴンの初期化処理
	//InitPolygon();

	//メッシュフィールドの初期化処理
	InitMeshField();

	//メッシュウォール
	InitMeshWall();

	////メッシュスフィアの初期化処理
	//InitMeshSphere();

	//カメラの初期化処理
	InitCamera();

	//ライトの初期化処理
	InitLight();
	
	//壁の初期化処理
	InitWall();

	//影の初期化処理
	InitShadow();

	//弾の初期化処理
	InitBullet();

	//エフェクトの初期化処理
	InitEffect();

	//爆発の初期化処理
	InitExplosion();

	//パーティクルの初期化処理
	InitParticle();

	//ブロックの初期化処理
	InitBlock();

	//プレイヤーの初期化処理
	InitPlayer();

//*************************
//壁の設定
//*************************

	//正面
	SetWall(D3DXVECTOR3(-350.0f,50.0f,350.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),1.0f,300.0f,100.0f);

	//migi
	SetWall(D3DXVECTOR3(350.0f, 50.0f, 350.0f),D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), 1.0f, 300.0f, 100.0f);

	//temae
	SetWall(D3DXVECTOR3(350.0f, 50.0f, -350.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 1.0f, 300.0f, 100.0f);

	//hif
	SetWall(D3DXVECTOR3(-350.0f, 50.0f, -350.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, 0.0f), 1.0f, 300.0f, 100.0f);
	

//*************************
	return S_OK;
}
//========================
//デバイスの取得
//========================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
//========================
//終了処理
//========================
void Uninit(void)
{
	//ジョイパッドの終了処理
	UninitJoypad();

	//キーボードの終了処理
	UninitKeyboard();

	////ポリゴンの終了処理
	//UninitPolygon();

	//メッシュフィールドの終了処理
	UninitMeshField();

	//メッシュウォールの終了処理
	UninitMeshWall();

	////メッシュスフィアの終了処理
	//UninitMeshSphere();

	//カメラの終了処理
	UninitCamera();

	//ライトの終了処理
	UninitLight();

	/*UninitModel();*/

	//壁の終了処理
	UninitWall();

	//弾の終了処理
	UninitBullet();

	//エフェクトの終了処理
	UninitEffect();

	//爆発の終了処理
	UninitExplosion();

	//パーティクルの終了処理
	UninitParticle();

	//ブロックの終了処理
	UninitBlock();

	//プレイヤーの終了処理
	UninitPlayer();

	//影の終了処理
	UninitShadow();
}
//========================
//更新処理
//========================
void Update(void)
{
	//ジョイパッドの更新処理
	UpdateJoypad();

	//ジョイパッドの更新処理
	UpdateKeyboard();

	////ポリゴンの更新処理
	//UpdatePolygon();

	//メッシュフィールドの更新処理
	UpdateMeshField();

	//メッシュウォールの更新処理
	UpdateMeshWall();

	////メッシュスフィアの更新処理
	//UpdateMeshSphere();

	//カメラの更新処理
	UpdateCamera();

	//ライトの更新処理
	UpdateLight();

	//弾の更新処理
	UpdateBullet();

	//エフェクトの更新処理
	UpdateEffect();

	//爆発の更新処理
	UpdateExplosion();

	//パーティクルの更新処理
	UpdateParticle();

	//壁の更新処理
	UpdateWall();

	//ブロックの更新処理
	UpdateBlock();

	//プレイヤーの更新処理
	UpdatePlayer();

	//影の更新処理
	UpdateShadow();

	if (KeyboardTrigger(DIK_F4) == true)
	{
		onWireFrame();
	}
	else if (KeyboardTrigger(DIK_F5) == true)
	{
		offWireFrame();
	}

	/*UpdateModel();*/
}
//========================
//描画処理
//========================
void Draw(void)
{
	//画面クリア(バックバッファ&Zバッファのクリア)
	g_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合

		//カメラの設定処理
		SetCamera();

		//ポリゴンの描画処理
		DrawPolygon();

		//メッシュフィールドの描画処理
		DrawMeshField();

		//メッシュウォールの描画処理
		DrawMeshWall();

		////メッシュスフィアの描画処理
		//DrawMeshSphere();

		//弾の描画処理
		DrawBullet();

		//プレイヤーの描画処理
		DrawPlayer();

		//ブロックの描画処理
		DrawBlock();

		//エフェクトの描画処理
		DrawEffect();

		//爆発の描画処理
		DrawExplosion();

		//パーティクルの描画処理
		DrawParticle();

		//壁の描画処理
		DrawWall();

		//プレイヤーの影の描画処理
		DrawShadow();

#ifdef _DEBUG

		//fpsの表示
		DrawFps();

		//カメラのrotの表示
		DrawCameraRot();

		//カメラの状態
		DrawCameraState();
#endif 

		//描画終了
		g_pD3DDevice->EndScene();
	}
	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//========================
//モード設定
//========================
void SetMode(MODE mode)
{
	////現在のモードの終了処理
	//switch (g_mode)
	//{
	//case MODE_TITLE:
	//	UninitTitle();
	//	break;
	//case MODE_SELECT:
	//	UninitBackground();
	//	UninitSelect();
	//	break;
	//case MODE_STAGESELECT:
	//	UninitBackground();
	//	UninitStageSelect();
	//	break;
	//case MODE_TUTORIAL://チュートリアル画面
	//	UninitTutorial();
	//	break;
	//case MODE_TUTORIAL2://チュートリアル画面
	//	UninitTutorial2();
	//	break;
	//case MODE_GAME:
	//	UninitGame();
	//	break;
	//case MODE_GAME2:
	//	UninitGame2();
	//	break;
	//case MODE_RESULT:
	//	UninitMedal();
	//	UninitResult();
	//	break;
	//case MODE_RANKING:
	//	UninitRanking();
	//	break;
	//case MODE_EDIT:
	//	UninitEdit();
	//	break;
	//}

	////新しいゲームモードの初期化処理
	//switch (mode)
	//{
	//case MODE_TITLE:
	//	InitTitle();
	//	break;
	//case MODE_SELECT:
	//	InitBackground();
	//	InitSelect();
	//	break;
	//case MODE_STAGESELECT:
	//	InitBackground();
	//	InitStageSelect();
	//	break;
	//case MODE_TUTORIAL://チュートリアル画面
	//	InitTutorial();
	//	break;
	//case MODE_TUTORIAL2://チュートリアル画面
	//	InitTutorial2();
	//	break;
	//case MODE_GAME:
	//	InitGame();
	//	break;
	//case MODE_GAME2:
	//	InitGame2();
	//	break;
	//case MODE_RESULT:
	//	InitMedal();
	//	InitResult();
	//	break;
	//case MODE_RANKING:
	//	InitRanking();
	//	break;
	//case MODE_EDIT:
	//	InitEdit();
	//	break;
	/*}*/
	//g_mode = mode;
}
//========================
//モードの取得
//========================
MODE GetMode(void)
{
	return g_mode;
}

void DrawFps(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	char aStr[256];

	//文字列
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}
void DrawCameraRot(void)
{
	CAMERA* pCamera = GetCamera();

	RECT rectRotx = { 0,15,SCREEN_WIDTH,SCREEN_HEIGHT };
	RECT rectRoty = { 180,15,SCREEN_WIDTH,SCREEN_HEIGHT };
	RECT rectRotz = { 360,15,SCREEN_WIDTH,SCREEN_HEIGHT };

	RECT rectPosx = { 0,45,SCREEN_WIDTH,SCREEN_HEIGHT };
	RECT rectPosy = { 180,45,SCREEN_WIDTH,SCREEN_HEIGHT };
	RECT rectPosz = { 360,45,SCREEN_WIDTH,SCREEN_HEIGHT };

	char aStrRotx[256];
	char aStrRoty[256];
	char aStrRotz[256];

	char aStrPosx[256];
	char aStrPosy[256];
	char aStrPosz[256];

	//文字に代入
	sprintf(&aStrRotx[0], "カメラの回転X:%.2f", pCamera->rot.x);
	sprintf(&aStrRoty[0], "カメラの回転Y:%.2f", pCamera->rot.y);
	sprintf(&aStrRotz[0], "カメラの回転Z:%.2f", pCamera->rot.z);
	
	//文字に代入
	sprintf(&aStrPosx[0], "カメラの位置X:%.2f", pCamera->posV.x);
	sprintf(&aStrPosy[0], "カメラの位置Y:%.2f", pCamera->posV.y);
	sprintf(&aStrPosz[0], "カメラの位置Z:%.2f", pCamera->posV.z);

	//テキストの描画
	g_pFont->DrawText(NULL, &aStrRotx[0], -1, &rectRotx, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawText(NULL, &aStrRoty[0], -1, &rectRoty, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawText(NULL, &aStrRotz[0], -1, &rectRotz, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

	//テキストの描画
	g_pFont->DrawText(NULL, &aStrPosx[0], -1, &rectPosx, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawText(NULL, &aStrPosy[0], -1, &rectPosy, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawText(NULL, &aStrPosz[0], -1, &rectPosz, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

}
////========================
////プレイヤーデバッグ表示
////========================
//void DebagDrawPlayer(void)
//{
//	Player* pPlayer = GetPlayer();
//
//	RECT rectPosx = { 0,15,SCREEN_WIDTH,SCREEN_HEIGHT };
//	RECT rectPosy = { 0,30,SCREEN_WIDTH,SCREEN_HEIGHT };
//
//	char aStrPosx[256];
//	char aStrPosy[256];
//
//	//文字に代入
//	sprintf(&aStrPosx[0], "PLAYER_POS_X:%.2f\n", pPlayer->pos.x);
//	sprintf(&aStrPosy[0], "PLAYER_POS_Y:%.2f\n", pPlayer->pos.y);
//
//	//テキストの描画
//	g_pFont->DrawText(NULL, &aStrPosx[0], -1, &rectPosx, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
//	g_pFont->DrawText(NULL, &aStrPosy[0], -1, &rectPosy, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
//}
//
//void DebagDrawMove(void)
//{
//	EDITINFO* pEdit = GetEdit();
//
//	RECT rectMovex = { 0,45,SCREEN_WIDTH,SCREEN_HEIGHT };
//	RECT rectMovey = { 0,60,SCREEN_WIDTH,SCREEN_HEIGHT };
//
//	char aStrMovex[256];
//	char aStrMovey[256];
//
//	//文字に代入
//	sprintf(&aStrMovex[0], "BLOCK_MOVE_X:%.2f[M][N]\n",pEdit->move.x);
//	sprintf(&aStrMovey[0], "BLOCK_MOVE_Y:%.2f[H][Y]\n", pEdit->move.y);
//
//	//テキストの描画
//	g_pFont->DrawText(NULL, &aStrMovex[0], -1, &rectMovex, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
//	g_pFont->DrawText(NULL, &aStrMovey[0], -1, &rectMovey, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
//}
//
//************************************************
// ウィンドウをフルスクリーンに変える処理
//************************************************
void ToggleFullscreen(HWND hWnd)
{
	// 現在のウィンドウスタイルを取得
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);
	if (g_isFullscreen)
	{
		// ウィンドウモードに切り替え
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, g_windowRect.left, g_windowRect.top,
			g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// フルスクリーンモードに切り替え
		GetWindowRect(hWnd, &g_windowRect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}
	g_isFullscreen = !g_isFullscreen;
}
//========================
//カメラの状態
//========================
void DrawCameraState(void)
{
	CAMERA* pCamera = GetCamera();

	RECT rectPos = { 0,100,SCREEN_WIDTH,SCREEN_HEIGHT };
	RECT rectPosBe = { 0,150,SCREEN_WIDTH,SCREEN_HEIGHT };

	char aStrPos[256];
	char aStrPosBe[256];

	if (pCamera->state == CAMERASTATE_PLAYER)
	{
		//文字に代入
		wsprintf(&aStrPos[0], "カメラ追従:[ON][F2]");
	}
	else if (pCamera->state == CAMERASTATE_NORMAL)
	{
		//文字に代入
		wsprintf(&aStrPos[0], "カメラ追従:[OFF][F2]");
	}

	if (pCamera->behind == true)
	{
		//文字に代入
		wsprintf(&aStrPosBe[0], "カメラ回り込み:[ON][F3]");
	}
	else if (pCamera->behind == false)
	{
		//文字に代入
		wsprintf(&aStrPosBe[0], "カメラ回り込み:[OFF][F3]");

	}
	//テキストの描画
	g_pFont->DrawText(NULL, &aStrPos[0], -1, &rectPos, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	g_pFont->DrawText(NULL, &aStrPosBe[0], -1, &rectPosBe, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

}
void onWireFrame() 
{
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}

void offWireFrame() 
{
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}



