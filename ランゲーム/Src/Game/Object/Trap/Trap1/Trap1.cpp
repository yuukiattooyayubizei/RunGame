#include"Trap1.h"
#include "../../../Data/Data.h"

CTrap1::CTrap1() {
	m_Pos.y = GetRand(720);
	m_Pos.x = 1200;
	m_Pos.z = 0;
	m_Kind = KIND_TRAP1;

	CData* Data = CData::GetInstance();
	m_TrapData = Data->GetTrapData();
}

CTrap1::~CTrap1() {

}

void CTrap1::Init() {

}

void CTrap1::Load() {

}

void CTrap1::Step() {
	m_Pos.x -= m_TrapData.m_FallingSpd;
}

void CTrap1::Draw() {
	DrawBox(m_Pos.x + m_TrapData.m_Size/2, m_Pos.y + m_TrapData.m_Size / 2, m_Pos.x - m_TrapData.m_Size / 2, m_Pos.y - m_TrapData.m_Size / 2, GetColor(255, 0, 0), TRUE);
}

void CTrap1::Exit() {

}