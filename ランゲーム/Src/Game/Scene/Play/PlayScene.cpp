#include"playScene.h"
#include"math.h"
#include <iostream>
#include <vector>
#include "../../Common.h"
#include "../../../Lib/Input/PadInput.h"
#include "../../Object/Trap/Trap1/Trap1.h"
#include "../../Data/Data.h"


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
	m_Player = new CPlayer();
	m_Object.push_back(m_Player);

	m_Time = 60;
}

void CPlayScene::Exit()
{
	for (auto obj : m_Object) {
		obj->Exit();
		delete obj;
	}
}

void CPlayScene::Load()
{
	CData* Data = CData::GetInstance();

	Data->Load();

	for (auto obj : m_Object) {
		obj->Load();
	}
	
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
		break;
	case CPlayScene::PLAY_SCENE_LOOP:
		//処理
		if (Step() != 0)m_tagPlayScene = PLAY_SCENE_END;
		break;
	case CPlayScene::PLAY_SCENE_END:
		//破棄
		Exit();
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
	//一定時間が経ったら罠を降らす
	if (Data->GetTime() >= Data->GetTrapData().m_SpownInterval)
	{
		m_Object.push_back(new CTrap1());
		Data->ResetTime();
	}

	



	for (auto obj : m_Object) {
		obj->Step();

		////下に通り過ぎた弾は消す
		//m_Object.erase(
		//	std::remove_if(m_Object.begin(), m_Object.end(),
		//		[](const CObject& e) { return e.GetPos().y >= 900; }),
		//	m_Object.end()
		//);
		
	}
	if (CheckHitKey(KEY_INPUT_L))
		return 1;
	return 0;
}

void CPlayScene::Draw()
{
	for (auto obj : m_Object) {
		obj->Draw();
	}
	//描画処理
	DrawFormatString(32, 96, GetColor(255, 255, 255), "プレイシーンLキーでリザルトに遷移");
}