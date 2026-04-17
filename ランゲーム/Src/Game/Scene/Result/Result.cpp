#include"ResultScene.h"
#include"math.h"
#include "../../Common.h"
#include "../../../Lib/Input/PadInput.h"
#include "../../../Lib/Sound/sound.h"
#include "../../Data/Data.h"



//コンストラクタ
CResultScene::CResultScene()
{
	m_tagResultScene = RESULT_SCENE_INIT;
	for (int i = 0; i >= EVALUATION_NUM; i++)
	{
		m_Resulthndl[i] = -1;
	}

}

//デストラクタ
CResultScene::~CResultScene()
{
	Exit();
}

void CResultScene::Init()
{
	m_tagResultScene = RESULT_SCENE_INIT;
	m_Score.Init();
	for (int i = 0; i <= EVALUATION_NUM - 1; i++)
	{
		m_Resulthndl[i] = -1;
	}
}

void CResultScene::Exit()
{
	if (m_Resulthndl[0] != -1)
	{
		for (int i = 0; i <= EVALUATION_NUM-1; i++)
		{
			DeleteGraph(m_Resulthndl[i]);
			m_Resulthndl[i] = -1;
		}
	}
	m_Score.Exit();
}

void CResultScene::Load()
{
	CData* Data = CData::GetInstance();


	if (m_Resulthndl[0] == -1)
		for (int i = 0; i <= EVALUATION_NUM-1; i++)
		{
			m_Resulthndl[i] = LoadGraph("../Data/image/Result/Result.JPG");
		}
	m_Score.Load();

	m_Score.SetScore(Data->GetScore());
}

int CResultScene::Loop()
{

	int m_ret = 0;

	//状態遷移に応じて挙動を変更
	switch (m_tagResultScene)
	{
	case CResultScene::RESULT_SCENE_INIT:
		//初期化
		Init();
		m_tagResultScene = RESULT_SCENE_LOAD;
		break;
	case CResultScene::RESULT_SCENE_LOAD:
		//ロード
		Load();
		m_tagResultScene = RESULT_SCENE_LOOP;
		//BGMを鳴らす
		RequestSound(BGMID_RESULT, DX_PLAYTYPE_BACK);
		break;
	case CResultScene::RESULT_SCENE_LOOP:
		//処理
		if (Step() == 1)m_tagResultScene = RESULT_SCENE_END;
		break;
	case CResultScene::RESULT_SCENE_END:
		//破棄
		StopAllSound();
		Exit();
		m_tagResultScene = RESULT_SCENE_INIT;
		m_ret = 1;
		break;
	default:
		break;
	}

	return m_ret;
}

int CResultScene::Step()
{
	m_Score.Update();
	if(CheckHitKey(KEY_INPUT_K))
		return 1;

	return 0;
}

void CResultScene::Draw()
{
	//描画処理
	if (m_Score.GetScore() >= 3000)
	{
		DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 1.0f, 0.0f, m_Resulthndl[2], TRUE);
		DrawFormatString(500, 364, GetColor(255, 255, 255), "○○3に到達！");
	}
	else if (m_Score.GetScore() >= 1000)
	{
		DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 1.0f, 0.0f, m_Resulthndl[1], TRUE);
		DrawFormatString(500, 364, GetColor(255, 255, 255), "○○2に到達！");
	}
	else
	{
		DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 1.0f, 0.0f, m_Resulthndl[0], TRUE);
		DrawFormatString(500, 364, GetColor(255, 255, 255), "○○1に到達！");
	}

	DrawFormatString(32, 96, GetColor(255, 255, 255), "Kキーでタイトルに遷移");
	DrawFormatString(500, 332, GetColor(255, 255, 255), "あなたのカエルは");

	m_Score.Draw();
}