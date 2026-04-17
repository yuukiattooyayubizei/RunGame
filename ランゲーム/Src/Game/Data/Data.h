#pragma once
#include <DxLib.h>
#include "../Common.h"

static constexpr float SPD_ADD_NUM = 0.0005f;

typedef struct {
	float m_FallingSpd;//落下速度
	int m_Size;//大きさ
	int m_SpownInterval;//出現間隔
}TrapData;

class CData {
private:
	static CData* m_Instance;
public:
	
public:
	CData();
	~CData();
	void Init();
	void Load();
public:
	static CData* GetInstance();

	static void DeleteInstance();

	TrapData m_TrapData;

	int GetTime() { return m_Time; }
	float GetScore() { return m_Score; }
	float GetSpd() { return m_Spd; }
	TrapData GetTrapData() { return m_TrapData; }

	void AddTime() {m_Time++;  m_Spd += SPD_ADD_NUM;}
	void AddScore(float spd) { m_Score += spd; }
	void ResetTime() { m_Time = 0; }
private:
	int m_Time;//経過時間
	float m_Score;//スコア
	float m_Spd;	//スピード
};