#pragma once
#include<DxLib.h>


class CBackGround {
public:
	int m_hndl;		//画像ハンドル
	VECTOR m_pos;	//画像の表示位置

	CBackGround();
	//画像データをロード
	void Load();
	//毎フレーム処理を行う
	void Step();
	//画像描画
	void Draw();
	//終了前に行う
	~CBackGround();
};
