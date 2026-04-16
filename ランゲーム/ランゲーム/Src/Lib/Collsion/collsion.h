#pragma once
#include <DxLib.h>

//店と四角の当たり判定
//dotpos　点の座標
//squarePos 四角形の中心座標
//widht　四角形の横幅
//heght 四角形の立幅
//@heturn;


	bool ChackHitDotToSquere(VECTOR dotPos, VECTOR squaerPos, int width, int height);

	bool ChackHitCircleToCircle(int circlePos1x, int circlePos1y, int radius1, int circlePos2x, int circlePos2y, int radius2);

	bool ChackHitSquereToSquere(VECTOR squerePos1, VECTOR squerePos2, int width1, int height1, int width2, int height2);

	float ChackHitSquereToSquereX(float squerePos1, float squerePos2, int width1, int width2);

	float ChackHitSquereToSquereY(float squerePos1, float squerePos2, int height1, int wheight2);
