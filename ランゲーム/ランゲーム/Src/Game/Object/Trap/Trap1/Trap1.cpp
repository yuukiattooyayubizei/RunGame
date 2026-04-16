#include"Trap1.h"
#include "../../../Data/Data.h"

static constexpr char TRAP_ANIM_HNDL[128] = "../Data/Image/Traps/Arrow/Idle (18x18).PNG";

CTrap1::CTrap1() {
	CData* Data = CData::GetInstance();
	m_TrapData = Data->GetTrapData();

	m_Pos.y = GetRand(720);
	m_Pos.x = 1080;
	m_Pos.z = 0;
	m_Kind = KIND_TRAP1;
	m_AnimNum = 0;
	m_AnimChengeWait = 0;
	m_AnimNumtMax = 0;
	m_AnimCount = 0;

	for (int i = 0;i < 128;i++)
		m_hndl[i] = -1;
	m_Size = 0;
	Load();
}

CTrap1::~CTrap1() {

}

void CTrap1::Init() {

}

void CTrap1::Load() {


		//画像の大きさを調べるため一旦普通に画像読み込み
		int tmp = LoadGraph(TRAP_ANIM_HNDL);

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
		m_AnimNumtMax = XNum;

		//計算した大きさを元に画像読み込み
		LoadDivGraph(TRAP_ANIM_HNDL, XNum, XNum, 1, Size, Size, m_hndl);

		//計算に使った画像を消す
		DeleteGraph(tmp);


	
}

void CTrap1::Step() {
	m_Pos.x -= m_TrapData.m_FallingSpd;

	//アニメーション関連
	m_AnimCount++;
	if (m_AnimCount >= m_AnimChengeWait)
	{
		m_AnimNum++;
		m_AnimCount = 0;

			if (m_AnimNum >= m_AnimNumtMax)
				m_AnimNum = 0;


	}
}

void CTrap1::Draw() {
	DrawBox(m_Pos.x + m_Size /2, m_Pos.y + m_Size / 2, m_Pos.x - m_Size / 2, m_Pos.y - m_Size / 2, GetColor(255, 0, 0), TRUE);
	DrawRotaGraph(m_Pos.x, m_Pos.y, 1.0f, 0.0f, m_hndl[m_AnimNum], TRUE);
}

void CTrap1::Exit() {

}