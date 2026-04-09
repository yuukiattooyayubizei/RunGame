#pragma once
#include"../Object.h"
#include <DxLib.h>

class CPlayer : public CObject {
private:
    VECTOR m_Pos;//位置
    int m_hndl;//画像ハンドル
    float m_NowJumpPower;//現在のジャンプの力
    float m_JumpPower;//ジャンプの力
    float m_MoveSpd;//プレイヤーの移動速度
    float m_Gravity;//プレイヤーにかかる重力
    bool m_IsJump;//ジャンプしたかどうか
public:
    ~CPlayer()override;

    void Init()override;
    void Load()override;
    void Step()override;
    void Draw()override;
    void Exit()override;

public:
    VECTOR GetPos() { return m_Pos; }
};