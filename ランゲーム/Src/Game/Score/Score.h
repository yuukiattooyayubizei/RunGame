#pragma once

// 定義関連=============================
#define NUMBER (10)			// 読み込む画像「0」～「9」
#define NUMBER_SIZE_X (16)	// 数字画像のサイズ　横
#define NUMBER_SIZE_Y (32)	// 数字画像のサイズ　縦
#define DIGIT_NUMBER (9)	// 表示可能な桁数(今回は999999999がカンスト)
#define ADD_SCORE_SPD (10)	// 1フレームで加算されるスコア数

#define START_POS_X (500)	// スコア表示開始位置　横
#define START_POS_Y (300)	// スコア表示開始位置　縦

#define SCORE_NUM (300) //スコアを保存できる最大の値

// 画像のパス
#define SCORE_GRAPH_PATH ("../Data/Image/ScoreNumber/number16x32_01.png")
// 効果音
#define SCORE_SOUND_PATH ("data/sound/se2.mp3")

class CScore {
private:
	int m_hndl[NUMBER];	//画像ハンドル
	int m_score;
public:
	void Init();
	void Load();
	void Update();
	void Draw();
	void Exit();

	void SetScore(int score);
	int GetScore() { return m_score; }
};