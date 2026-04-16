#pragma once
#include <DxLib.h>

enum ObjectKind {
    KIND_NON,
    KIND_PLAYER,
    KIND_TRAP1,
};

class CObject {
protected:
    ObjectKind m_Kind;
    VECTOR m_Pos;
public:
    CObject();
    virtual ~CObject() {}

    virtual void Init() = 0;
    virtual void Load() = 0;
    virtual void Step() = 0;
    virtual void Draw() = 0;
    virtual void Exit() = 0;

    VECTOR GetPos() const { return m_Pos; }
    ObjectKind GetKind() const { return m_Kind; }
};