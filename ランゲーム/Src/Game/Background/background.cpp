#include "background.h"
#include<DxLib.h>

#define BACKGROUND_SIZE_X (960.0f)
#define BACKGROUND_SIZE_Y (720.0f)
#define MOVE_SPEED		  (1.0f)

CBackGround g_BG;

CBackGround::CBackGround() 
{
	m_hndl = -1;
	m_pos.x = BACKGROUND_SIZE_X * 0.5f;
	m_pos.y = BACKGROUND_SIZE_Y * 0.5f;
}

CBackGround::~CBackGround()
{
	//ƒf[ƒ^‚ª“ü‚Á‚Ä‚é‚È‚ç-1‚Å‚Í‚È‚¢
	if (m_hndl != -1)
	{
		//‰æ‘œ‚ğƒƒ‚ƒŠã‚©‚ç”jŠü‚·‚é
		DeleteGraph(m_hndl);
		m_hndl = -1;
	}
}

void CBackGround::Load()
{
	if (m_hndl == -1)
	{
		m_hndl = LoadGraph("../Data/Image/Background/Background.PNG");
	}
}

void CBackGround::Step()
{

}

void CBackGround::Draw()
{
	DrawRotaGraph((int)m_pos.x, (int)m_pos.y, 1.0, 0.0, m_hndl, true);
}

