#pragma once
#include<Dxlib.h>

#define BACKGROUND_SIZE_X (1261.0f)
#define BACKGROUND_SIZE_Y (480.0f)
#define MOVE_SPEED		  (1.0f)
#define ANIM_NUM (10)
#define ANIM_SPEED (0.25f)

//データを初期化
void InitExplosion();
//画像データをロード
void LoadExplosion();
//毎フレーム処理を行う
void StepExplosion();
//画像描画
void DrawExplosion();
//終了前に行う
void ExitExplosion();

//エフェクトを呼び出すための関数
//@pos;エフェクトの表示場所
void RequestExplosion(VECTOR pos);

class CAnim {
private:
	int m_hndl[ANIM_NUM];		//画像ハンドル
	VECTOR m_pos;	//画像の表示位置
	float m_AnimCount;
	bool m_isActive;
public:
	void Init();
	void Load();
	void Step();
	void Draw();
	void Exit();

	void Request(VECTOR pos);
};