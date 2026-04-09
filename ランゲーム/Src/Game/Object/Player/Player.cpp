#include"Player.h"
#include "../../../lib/Input/input.h"

CPlayer::~CPlayer(){
}

void CPlayer::Init(){
	m_Pos.x = m_Pos.y = m_Pos.z = m_JumpPower = 0.0f;
	m_Kind = KIND_PLAYER;
}

void CPlayer::Load() {
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
	float f;


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

	//開いたファイルを閉じる
	fclose(fp);

	m_Pos.x = 100.0f;
	m_Pos.y = 715.0f;
}

void CPlayer::Step() {
	if (IsInputTrg(KEY_W) && m_IsJump == false) {
		m_NowJumpPower = m_JumpPower;
		m_IsJump = true;
	}

	m_Pos.y -= m_NowJumpPower;

	m_NowJumpPower -= m_Gravity;

	if (m_Pos.y >= 715)
	{
		m_Pos.y = 715;
		m_IsJump = false;
	}
}

void CPlayer::Draw() {
	DrawBox(m_Pos.x + 5, m_Pos.y + 5, m_Pos.x - 5, m_Pos.y - 5, GetColor(128, 128, 128), TRUE);
	DrawFormatString(32, 32, GetColor(255, 255, 255), "posx = %f",m_Pos.x);
	DrawFormatString(32, 64, GetColor(255, 255, 255), "posy = %f", m_Pos.y);
}

void CPlayer::Exit() {

}