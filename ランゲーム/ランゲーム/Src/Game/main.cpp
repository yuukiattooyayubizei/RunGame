#include <DxLib.h>			// DxLibを使用するために必須
#include "Scene/SceneManager.h"
#include "Common.h"
#include "../Lib/Input/input.h"

// ゲームプログラムは WinMain から始まります
int  WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);			// ウィンドウモードにするかどうか
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);		// ウィンドウの解像度を設定する

#ifndef _DEBUG
	// リリース版はログを出さない
	SetOutApplicationLogValidFlag( false );
#endif

	// ＤＸライブラリ初期化処理　基本的にはこれより後でDxLib関数を使う
	if (DxLib_Init() == -1) return -1;

	// 一番最初に１回だけやる処理
	SetDrawScreen(DX_SCREEN_BACK);	// 画面のちらつきを無くす

	SetTransColor(255, 0, 255);		// 透過色指定　今回は真紫色を透明

	SceneManager m_Scene;

	m_Scene.Load();
	InitInput();

	//ゲームメインループ
	while (ProcessMessage() != -1)	// 問題が発生したら終了
	{
		// 「escキー」が押されたら終了
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;

		
		// 画面を一度何もない状態へ
		ClearDrawScreen();

		// ゲーム本体の命令はこれより下に書く
		UpdateInput();
		m_Scene.Loop();

		m_Scene.Draw();

		// ゲーム本体の命令はこれより上に書く

		// 作成した画面をモニターへ転送
		ScreenFlip();

	}

	// 終了前処理==================
	DxLib_End();			// ＤＸライブラリ使用の終了処理
	m_Scene.Exit();
	//=============================

	return 0;				// プログラムの終了 
}
