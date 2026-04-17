#include"Player.h"
#include "../../../lib/Input/input.h"
#include "../../Common.h"

static constexpr char PLAYER_ANIM_HNDL[ANIM_NUM][128] = { "../Data/Image/MainCharacters/NinjaFrog/Idle.png",
														"../Data/Image/MainCharacters/NinjaFrog/Hit.png",
														"../Data/Image/MainCharacters/NinjaFrog/Run.png",
														"../Data/Image/MainCharacters/NinjaFrog/DoubleJump.png" };

static constexpr int PLAYER_ANIM_XNUM[ANIM_NUM] = { 11,7,12,6 };	//アニメーションの枚数

CPlayer::~CPlayer(){
}

void CPlayer::Init(){
	m_Pos = VGet(0,0,0);
	m_JumpPower = m_NowJumpPower = m_MoveSpd = m_Gravity = 0.0f;
	m_Kind = KIND_PLAYER;
	m_IsJump = true;

	for (int i = 0; i < ANIM_NUM; i++)
	{
		for (int k = 0; k < PLAYER_ANIM_XNUM[i]; k++)
		{
			m_Anim.m_hndl[i][k] = -1;
		}
	}
	m_Anim.m_AnimNum = 0;
	m_Anim.m_AnimControl = ANIM_IDLE;
	m_AnimChengeWait = 0;
	m_IsSteepDive = false;
}

void CPlayer::Load() {

	for (int i = 0; i < ANIM_NUM; i++) {

		//画像の大きさを調べるため一旦普通に画像読み込み
		int tmp = LoadGraph(PLAYER_ANIM_HNDL[i]);

		//※今回のプログラムでは、アニメーションが横一列かつ、アニメーション一枚あたりの画素数が縦と横で同じであることを前提に動いています。

		//画像の大きさを調べる
		int width, height;
		GetGraphSize(tmp, &width, &height);

		//画像の分割数がいくつか計算する
		int XNum = width / height;

		//画像の画質を分割数で割る
		int Size = width / XNum;

		//画像の大きさを保存
		m_Size = Size;


		//計算した大きさを元に画像読み込み
		LoadDivGraph(PLAYER_ANIM_HNDL[i], XNum, XNum, 1, Size, Size, m_Anim.m_hndl[i]);

		//計算に使った画像を消す
		DeleteGraph(tmp);
	}

	//CSVファイルからデータを読み込み
	FILE* fp;

	//ファイルを開く　失敗したら即終了
	if (fopen_s(&fp, "../Data/Data/PlayerData.csv", "r") != 0)return;

	// --- BOMチェック ---
	unsigned char bom[3];
	if (fread(bom, 1, 3, fp) == 3)
	{
		if (!(bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF))
		{
			// BOMじゃなければ先頭に戻す
			fseek(fp, 0, SEEK_SET);
		}
	}

	char line[256];
	float f = 0.0f;
	int i = 0;


	if (!fgets(line, sizeof(line), fp))return;
	if (sscanf_s(line, "%f", &f) == 1)
	{
		m_JumpPower = f;
	}

	if (!fgets(line, sizeof(line), fp))return;
	if (sscanf_s(line, "%f", &f) == 1)
	{
		m_MoveSpd = f;
	}

	if (!fgets(line, sizeof(line), fp))return;
	if (sscanf_s(line, "%f", &f) == 1)
	{
		m_Gravity = f;
	}
	if (!fgets(line, sizeof(line), fp))return;
	if (sscanf_s(line, "%d", &i) == 1)
	{
		m_AnimChengeWait = i;
	}
	

	//開いたファイルを閉じる
	fclose(fp);

	m_Pos.x = 100.0f;
	m_Pos.y = 715.0f;
}

void CPlayer::Step() {

	
	
		if (m_Anim.m_AnimControl != ANIM_RUN && m_IsJump == false)
		{
			m_Anim.m_AnimControl = ANIM_RUN;
			m_Anim.m_AnimNum = 0;
			m_Anim.m_AnimCount = 0;
		}
	
	if (IsInputTrg(KEY_W) /*&& m_IsJump == false*/) {
		m_NowJumpPower = m_JumpPower;
		m_IsJump = true;
		if (m_Anim.m_AnimControl != ANIM_JUMP)
		{
			m_Anim.m_AnimControl = ANIM_JUMP;
			m_Anim.m_AnimNum = 0;
			m_Anim.m_AnimCount = 0;
		}
	}
	if (IsInputRep(KEY_S))
	{
		m_IsSteepDive = true;
		//上昇中ならすぐに落下に切り替える
		if (m_NowJumpPower >= 0.0f)
			m_NowJumpPower = 0.0f;
	}
	else
		m_IsSteepDive = false;

	//重力の処理
	//急降下中は早く落ちる
	if(m_IsSteepDive == true)
		m_Pos.y -= m_NowJumpPower * 2;
	else
		m_Pos.y -= m_NowJumpPower;

	m_NowJumpPower -= m_Gravity;

	//高さの上限下限の処理
	if (m_Pos.y >= 720 - m_Size / 2)
	{
		m_Pos.y = 720 - m_Size / 2;
		m_IsJump = false;
	}
	if (m_Pos.y <= m_Size / 2)
	{
		m_Pos.y = m_Size / 2;
		m_NowJumpPower = -1.0f;
	}

	//アニメーション関連
	m_Anim.m_AnimCount++;
	if (m_Anim.m_AnimCount >= m_AnimChengeWait)
	{
		m_Anim.m_AnimNum++;
		m_Anim.m_AnimCount = 0;
		switch (m_Anim.m_AnimControl)
		{
		case ANIM_IDLE:
			if (m_Anim.m_AnimNum >= PLAYER_ANIM_XNUM[0])
				m_Anim.m_AnimNum = 0;
			break;
		case ANIM_HIT:
			if (m_Anim.m_AnimNum >= PLAYER_ANIM_XNUM[1])
				m_Anim.m_AnimNum = 0;
			break;
		case ANIM_RUN:
			if (m_Anim.m_AnimNum >= PLAYER_ANIM_XNUM[2])
				m_Anim.m_AnimNum = 0;
			break;
		case ANIM_JUMP:
			if (m_Anim.m_AnimNum >= PLAYER_ANIM_XNUM[3])
				m_Anim.m_AnimNum = 0;
			break;
		default:
			break;
		}

	}
}

void CPlayer::Draw() {


	//アニメーションのうちどれを表示するか
	int nowHndl = 0;
	switch (m_Anim.m_AnimControl)
	{
	case ANIM_IDLE:
		nowHndl = m_Anim.m_hndl[0][m_Anim.m_AnimNum];
		break;
	case ANIM_HIT:
		nowHndl = m_Anim.m_hndl[1][m_Anim.m_AnimNum];
		break;
	case ANIM_RUN:
		nowHndl = m_Anim.m_hndl[2][m_Anim.m_AnimNum];
		break;
	case ANIM_JUMP:
		nowHndl = m_Anim.m_hndl[3][m_Anim.m_AnimNum];
		break;
	default:
		break;
	}

	DrawFormatString(32, 32, GetColor(255, 255, 255), "posx = %f", m_Pos.x);
	DrawFormatString(32, 64, GetColor(255, 255, 255), "posy = %f", m_Pos.y);
	DrawFormatString(32, 128, GetColor(255, 255, 255), "nowHndl = %d", m_Anim.m_AnimNum);

	//アニメーション表示

	DrawRotaGraph((int)m_Pos.x, (int)m_Pos.y, 1.0, 0.0, nowHndl, TRUE);
}

void CPlayer::Exit() {

}