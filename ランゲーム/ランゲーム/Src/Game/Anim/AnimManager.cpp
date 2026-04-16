#include "Anim.h"
#include<DxLib.h>

//背景データを表示するために必要な構造体
typedef struct {
	int m_hndl[ANIM_NUM];		//画像ハンドル
	VECTOR m_pos;	//画像の表示位置
	float m_AnimCount;
	bool m_isActive;
} EXPLOSION_DATA;

//上記構造体を実際の変数で
static EXPLOSION_DATA g_Explosion[ENEMY_MAX];

//データを初期化
void InitExplosion()
{
	for (int j = 0; j < ENEMY_MAX; j++)
	{
		for (int i = 0; i < ANIM_NUM; i++)
		{
			g_Explosion[j].m_hndl[i] = -1;
		}
		g_Explosion[j].m_AnimCount = BACKGROUND_SIZE_X * 0.5f;
		g_Explosion[j].m_pos = {0.0f,0.0f,0.0f};
		g_Explosion[j].m_isActive = false;
	}
}
//画像データをロード
void LoadExplosion()
{
	int success[ENEMY_MAX] = { 0 };
	for (int i= 0;i<ENEMY_MAX;i++)
	success[i] = -1;
	for (int j = 0; j < ENEMY_MAX; j++)
	{
		if (g_Explosion[j].m_hndl[0] == -1)
		{

			success[j] = LoadDivGraph("data/graphics/game/effect_explosion00.png", ANIM_NUM, ANIM_NUM, 1, 180, 180, g_Explosion[j].m_hndl);
		}
	}
}
//毎フレーム処理を行う
	void StepExplosion()
	{
		for (int j = 0; j < ENEMY_MAX; j++)
		{
			//生存フラグがオフなら何もしない
			if (g_Explosion[j].m_isActive == false)continue;

			//アニメーションの時間をカウント
			g_Explosion[j].m_AnimCount += ANIM_SPEED;
			if (g_Explosion[j].m_AnimCount >= ANIM_NUM)
			{
				g_Explosion[j].m_isActive = false;
			}
		}
	}
//画像描画
void DrawExplosion()
{
	for (int j = 0; j < ENEMY_MAX; j++)
	{
		//フラグがオフなら終了
		if (g_Explosion[j].m_isActive == false)continue;
		
			//10枚の画像のうち、どれを表示するか
			int nowHndl = g_Explosion[j].m_hndl[(int)g_Explosion[j].m_AnimCount];
			//爆発画像表示
			DrawRotaGraph((int)g_Explosion[j].m_pos.x, (int)g_Explosion[j].m_pos.y, 1.0, 0.0, nowHndl, TRUE);
		


	}
}
//終了前に行う
void ExitExplosion()
{
	for (int j = 0; j < ENEMY_MAX; j++)
	{
		if (g_Explosion[j].m_hndl[0] != -1)
		{
			for (int i = 0; i < ANIM_NUM; i++)
			{
				DeleteGraph(g_Explosion[j].m_hndl[i]);
				g_Explosion[j].m_hndl[i] = -1;
			}
		}
	}
}

//エフェクトを呼び出すための関数
void RequestExplosion(VECTOR pos)
{
	for (int j = 0; j < ENEMY_MAX; j++)
	{
		if (g_Explosion[j].m_isActive == false)
		{
			//エフェクト表示に必要な情報を最初に1回セットする
			g_Explosion[j].m_isActive = true;
			g_Explosion[j].m_pos = pos;
			g_Explosion[j].m_AnimCount = 0.0f;
			return;
		}
	}
}

