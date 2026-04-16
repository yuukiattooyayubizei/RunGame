#pragma once
#include"../Object.h"
#include <DxLib.h>
#include "../../Common.h"

static constexpr int PLAYER_ANIM_NUM_MAX = 128;								//プレイヤーのアニメーションの枚数の最大値

//プレイヤーのアニメージョンを制御するもの
enum ANIM_CONTROL {
    ANIM_IDLE,  //無操作時
    ANIM_HIT,   //被弾時
    ANIM_RUN,   //移動時
    ANIM_JUMP,  //ジャンプ時

    ANIM_NUM,   //アニメーションの種類の数
};

class CPlayer : public CObject {
private:

    //背景データを表示するために必要な構造体
    typedef struct {
        int m_hndl[ANIM_NUM][PLAYER_ANIM_NUM_MAX];		//画像ハンドル
        int AnimNumMax[ANIM_NUM];                          //アニメーションが何枚あるか
        int m_AnimCount;                                //アニメの表示が切り替わるまでの時間
        int m_AnimNum;                                  //表示するアニメーションの種類
        ANIM_CONTROL m_AnimControl;
    } PLAYER_ANIM_DATA;

    PLAYER_ANIM_DATA m_Anim;    //プレイヤーアニメーション
    VECTOR m_Pos;               //位置
    float m_NowJumpPower;       //現在のジャンプの力
    float m_JumpPower;          //ジャンプの力
    float m_MoveSpd;            //プレイヤーの移動速度
    float m_Gravity;            //プレイヤーにかかる重力
    bool m_IsJump;              //ジャンプしたかどうか
    int m_AnimChengeWait;       //アニメーション画像を次の画像に変えるまでの時間
    int m_Size;                 //プレイヤーの大きさ
public:
    ~CPlayer()override;

    void Init()override;
    void Load()override;
    void Step()override;
    void Draw()override;
    void Exit()override;

public:
    VECTOR GetPos() { return m_Pos; }
    int GetSize() { return m_Size; }
};
