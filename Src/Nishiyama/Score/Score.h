#pragma once

class Score
{
private:
	static int score;

public:
	static 	void Init() { score = 0; }

	static void AddScore(int Add_int) { score += Add_int; }

	static int GetScore() { return score; }

	static 	void ScoreInit();

	static 	void Draw();
};

//�X�R�A�֘A�\����
struct ScoreInfo
{
	int numberHundle[10];
};