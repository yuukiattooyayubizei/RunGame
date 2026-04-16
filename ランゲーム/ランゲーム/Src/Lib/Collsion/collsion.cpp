#include "collsion.h"

//=================================
//点と四角の当たり判定
//=================================
bool ChackHitDotToSquere(VECTOR dotPos, VECTOR squerePos, int width, int height)
{
	//四角の上下左右の位置を計算
	float up = squerePos.y - height * 0.5f;
	float doun = squerePos.y + height * 0.5f;
	float left = squerePos.x - width * 0.5f;
	float right = squerePos.x + width * 0.5f;

	//実際の当たり判定
	if (dotPos.x >= left && dotPos.x <= right && dotPos.y >= up && dotPos.y <= doun)
		return true;
	else
		return false;
}

bool ChackHitCircleToCircle(int circlePos1x, int circlePos1y, int radius1, int circlePos2x, int circlePos2y, int radius2)
{
	int side = circlePos1x - circlePos2x;//x座標の距離を計算
	int lenght = circlePos1y - circlePos2y;//y座標の距離を計算
	int hypotenuse = side * side + lenght * lenght;//斜辺を計算
	if (hypotenuse <= (radius1 + radius2) * (radius1 + radius2))//斜辺の2乗より半径の合計の2乗の方が大きければ衝突している
	{
		return true;
	}
	else
	{
		return false;
	}
}

//=================================
//四角と四角の当たり判定
//=================================
bool ChackHitSquereToSquere(VECTOR squerePos1, VECTOR squerePos2, int width1, int height1, int width2, int height2)
{
	//四角の上下左右の位置を計算
	float up1 = squerePos1.y - height1 * 0.5f;
	float doun1 = squerePos1.y + height1 * 0.5f;
	float left1 = squerePos1.x - width1 * 0.5f;
	float right1 = squerePos1.x + width1 * 0.5f;

	float up2 = squerePos2.y - height2 * 0.5f;
	float doun2 = squerePos2.y + height2 * 0.5f;
	float left2 = squerePos2.x - width2 * 0.5f;
	float right2 = squerePos2.x + width2 * 0.5f;

	//実際の当たり判定
	if (up1 >= doun2 || doun1 <= up2 || right1 <= left2 || left1 >= right2)
		return false;
	else
		return true;



}

float ChackHitSquereToSquereX(float squerePos1, float squerePos2, int width1, int width2)
{
	//2つの物体の中心の距離を計算
	float distance = squerePos1 - squerePos2;
	//距離はマイナスにならない
	if (distance < 0)
		distance *= -1;

	//2つの物体の大きさの合計の半分を計算
	int length = (width1 + width2) / 2;

	float embedded = distance - length;

	//2点間の距離が大きさより短い場合衝突している
	if (embedded >= 0)
		return 0;
	else
		return -embedded;
}

float ChackHitSquereToSquereY(float squerePos1, float squerePos2, int height1, int height2)
{
	//2つの物体の中心の距離を計算
	float distance = squerePos1 - squerePos2;
	//距離はマイナスにならない
	if (distance < 0)
		distance *= -1;

	//2つの物体の大きさの合計の半分を計算
	int length = (height1 + height2) / 2;

	float embedded = distance - length;

	//2点間の距離が大きさより短い場合衝突している
	if (embedded >= 0)
		return 0;
	else
		return -embedded;



}