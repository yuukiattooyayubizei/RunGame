#pragma once
#include"../Trap.h"
#include <DxLib.h>
#include "../../../Data/Data.h"

class CTrap1 : public CTrap {
public:
    CTrap1();
    ~CTrap1()override;

    void Init()override;
    void Load()override;
    void Step()override;
    void Draw()override;
    void Exit()override;
private:
    TrapData m_TrapData;
    int m_hndl[128];
    int m_Size;                 //罠の大きさ
    int m_AnimCount;                                //アニメの表示が切り替わるまでの時間
    int m_AnimNumtMax;                             //表示するアニメーションの種類の最大数
    int m_AnimNum;                                  //表示するアニメーションの種類
    int m_AnimChengeWait;       //アニメーション画像を次の画像に変えるまでの時間
public:
    VECTOR GetPos() { return m_Pos; }
    int GetSize() { return m_TrapData.m_Size; }
    int Getm_FallingSpd() { m_TrapData.m_FallingSpd; }
};