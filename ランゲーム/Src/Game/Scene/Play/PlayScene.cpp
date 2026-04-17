#include"playScene.h"
#include"math.h"
#include <iostream>
#include <vector>
#include<algorithm>
#include<list>
#include "../../Common.h"
#include "../../../Lib/Input/PadInput.h"
#include "../../Object/Trap/Trap1/Trap1.h"
#include "../../Data/Data.h"
#include "../../../Lib/Collsion/collsion.h"
#include "../../../Lib/Sound/sound.h"

using namespace std;


//コンストラクタ
CPlayScene::CPlayScene()
{
	m_tagPlayScene = PLAY_SCENE_INIT;
}

//デストラクタ
CPlayScene::~CPlayScene()
{
	Exit();
}

void CPlayScene::Init()
{
	CData* Data = CData::GetInstance();
	Data->Init();

	m_Player = new CPlayer();
	m_Object.push_back(m_Player);
}

void CPlayScene::Exit()
{
	for_each(m_Object.begin(), m_Object.end(), [](CObject* object) {object->Exit(); });

	for (auto obj : m_Object) {
		obj->Exit();
		delete obj;
	}
	m_Object.clear();

	m_Player = nullptr;
}

void CPlayScene::Load()
{
	CData* Data = CData::GetInstance();

	Data->Load();

	m_BackGround.Load();

	for_each(m_Object.begin(), m_Object.end(), [](CObject* object) {object->Load(); });
}

int CPlayScene::Loop()
{
	
	int m_ret = 0;

	//状態遷移に応じて挙動を変更
	switch (m_tagPlayScene)
	{
	case CPlayScene::PLAY_SCENE_INIT:
		//初期化
		Init();
		m_tagPlayScene = PLAY_SCENE_LOAD;
		break;
	case CPlayScene::PLAY_SCENE_LOAD:
		//ロード
		Load();
		m_tagPlayScene = PLAY_SCENE_LOOP;
		//BGMを鳴らす
		RequestSound(BGMID_GAME, DX_PLAYTYPE_BACK);
		break;
	case CPlayScene::PLAY_SCENE_LOOP:
		//処理
		if (Step() != 0)m_tagPlayScene = PLAY_SCENE_END;
		break;
	case CPlayScene::PLAY_SCENE_END:
		//破棄
		Exit();
		StopAllSound();
		m_tagPlayScene = PLAY_SCENE_INIT;
		m_ret = 1;
		break;
	default:
		break;
	}

	return m_ret;
}

int CPlayScene::Step()
{
	CData* Data = CData::GetInstance();

	//時間を進める
	Data->AddTime();
	Data->AddScore(Data->GetSpd());

	//一定時間が経ったら罠を降らす
	if (Data->GetTime() >= Data->GetTrapData().m_SpownInterval)
	{
		m_Object.push_back(new CTrap1());
		Data->ResetTime();
	}

	for_each(m_Object.begin(), m_Object.end(), [](CObject* object) {object->Step(); });
	
	//プレイヤーと罠のあたり判定
	for (auto obj : m_Object) {
		//プレイヤーとは判定しない
		//今回はプレイヤーと弾のみのはずなので、プレイヤー以外をすべて罠とみなす
		if (obj->GetKind() == KIND_PLAYER)continue;

		//値の決定
		VECTOR squerePos1 = m_Player->GetPos();
		VECTOR squerePos2 = obj->GetPos();

		//プレイヤーの当たり判定を本来より小さくしておく
		int width1 = m_Player->GetSize() * 0.6;
		int height1 = m_Player->GetSize() * 0.6;

		int width2 = Data->GetTrapData().m_Size;
		int height2 = width2;

		//背景を動かす
		m_BackGround.Step();

		//衝突しているかチェック
		if (ChackHitSquereToSquere(squerePos1, squerePos2, width1, height1, width2, height2) == true)
		{
			return 1;
		}
	}
	
	//罠が下までいったら消す
	for (auto it = m_Object.begin(); it != m_Object.end(); )
	{
		CObject* obj = *it;

		//今回はプレイヤーと罠のみのはずなので、プレイヤー以外をすべて罠とみなす
		if (obj->GetKind() == KIND_PLAYER)continue;

		VECTOR pos = obj->GetPos();

		if (pos.x <= -100)
		{
			obj->Exit();
			delete obj;

			//普通に消去すると、vectorが別物に変わってしまい、途中でエラーを起こしてしまう
			//m_Object.eraseの返り値が、消した後の次の有効な所に設定されているため、これを使ってエラーを回避
			it = m_Object.erase(it);
			DrawFormatString(32, 216, GetColor(255, 255, 255), "消去完了");
		}
		else
		{
			++it;
		}
	}

	if (CheckHitKey(KEY_INPUT_L))
		return 1;
	return 0;
}

void CPlayScene::Draw()
{
	CData* Data = CData::GetInstance();
	//背景の描画
	m_BackGround.Draw();

	for_each(m_Object.begin(), m_Object.end(), [](CObject* object) {object->Draw(); });



	//描画処理
	DrawFormatString(32, 96, GetColor(255, 255, 255), "プレイシーンLキーでリザルトに遷移");
	DrawFormatString(32, 160, GetColor(255, 255, 255), "移動距離 = %d cm", (int)Data->GetScore());

}