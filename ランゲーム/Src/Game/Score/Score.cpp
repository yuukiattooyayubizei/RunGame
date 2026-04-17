#include "score.h"
#include <DxLib.h>
#include<stdlib.h>



//======================================



void CScore::Init()
{
	for (int i = 0; i < NUMBER; i++)
	{
		m_hndl[i] = -1;
	}

	m_score = 0;
}

void CScore::Load()
{
	int ret = 0;

		 ret = LoadDivGraph(SCORE_GRAPH_PATH, NUMBER, NUMBER, 1, NUMBER_SIZE_X, NUMBER_SIZE_Y, m_hndl);
}

void CScore::Update()
{

}

void CScore::Draw()
{
	int tempScore = m_score;


	for (int i = 0; i < DIGIT_NUMBER; i++)
	{
		int num = tempScore % 10;

		DrawRotaGraph(START_POS_X - NUMBER_SIZE_X * i * 2, START_POS_Y, 2.0, 0.0, m_hndl[num], true);

		tempScore /= 10;
	}
}

void CScore::Exit()
{
	for (int i = 0; i < NUMBER; i++)
	{
		DeleteGraph(m_hndl[i]);
		m_hndl[i] = -1;
	}
}


void CScore::SetScore(int score)
{
	m_score = score;
}

