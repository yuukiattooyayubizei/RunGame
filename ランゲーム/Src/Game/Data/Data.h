#pragma once
#include <DxLib.h>
#include "../Common.h"

typedef struct {
	float m_FallingSpd;//—‰º‘¬“x
	int m_Size;//‘å‚«‚³
	int m_SpownInterval;//oŒ»ŠÔŠu
}TrapData;

class CData {
private:
	static CData* m_Instance;
public:
	
public:
	CData();
	~CData();
	void Load();
public:
	static CData* GetInstance();

	static void DeleteInstance();

	TrapData m_TrapData;

	int GetTime() { return m_Time; }
	TrapData GetTrapData() { return m_TrapData; }

	void AddTime() { m_Time++; }
	void ResetTime() { m_Time = 0; }
private:
	int m_Time;//Œo‰ßŠÔ
};